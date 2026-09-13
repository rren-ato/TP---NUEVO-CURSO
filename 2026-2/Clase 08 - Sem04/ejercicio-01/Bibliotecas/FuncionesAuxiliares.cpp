#include "FuncionesAuxiliares.h"
#include <iomanip>

bool abrirArchivos(ifstream& archivoProductos, ifstream& archivoMovimientos, ofstream& archivoReporte) {
    archivoProductos.open("ArchivosDeDatos/productos.csv", ios::in);
    archivoMovimientos.open("ArchivosDeDatos/movimientos.csv", ios::in);
    archivoReporte.open("ArchivosDeReportes/reporte.txt", ios::out);
    return archivoProductos.is_open() and archivoMovimientos.is_open() and archivoReporte.is_open();
}

void cerrarArchivos(ifstream& archivoProductos, ifstream& archivoMovimientos, ofstream& archivoReporte) {
    archivoProductos.close();
    archivoMovimientos.close();
    archivoReporte.close();
}

void imprimirLineaSeparadora(ofstream& archivoReporte, int longitud, char caracter) {
    archivoReporte << setfill(caracter)
           << setw(longitud)
           << ""
           << setfill(' ') << endl;
}

void imprimirEncabezado(ofstream& archivoReporte) {
    imprimirLineaSeparadora(archivoReporte, 52);
    archivoReporte << "REPORTE DE STOCK POR PRODUCTO" << endl;
    imprimirLineaSeparadora(archivoReporte, 52);
}

int acumularMovimientosDeProducto(ifstream& archivoMovimientos, int idProducto,
    int& entradas, int& salidas) {

    int idMovimiento, cantidad;
    char sep, tipo;
    int nMovimientos = 0;

    entradas = 0;
    salidas = 0;

    // El archivo secundario se relee completo desde el inicio por cada producto.
    archivoMovimientos.clear();
    archivoMovimientos.seekg(0);

    while (true) {
        archivoMovimientos >> idMovimiento;

        if (archivoMovimientos.eof()) {
            break;
        }

        archivoMovimientos >> sep >> tipo >> sep >> cantidad;

        if (idMovimiento != idProducto) {
            continue;
        }
        if (tipo == 'E') {
            entradas += cantidad;
        } else {
            salidas += cantidad;
        }
        nMovimientos++;
    }

    return nMovimientos;
}

void imprimirResumenProducto(ofstream& archivoReporte, int entradas, int salidas, int stock) {
    archivoReporte << setw(2) << "" << left << setw(18) << "Entradas:"
           << right << setw(10) << entradas << endl;
    archivoReporte << setw(2) << "" << left << setw(18) << "Salidas:"
           << right << setw(10) << salidas << endl;
    archivoReporte << setw(2) << "" << left << setw(18) << "Stock resultante:"
           << right << setw(10) << stock << endl;
}

void imprimirProducto(ifstream& archivoEntrada, ofstream& archivoReporte, int id, char categoria,
    int& entradas, int& salidas, int& stock, int& nMovimientos) {

    archivoReporte << "Producto " << id
           << " (categoria " << categoria << ")" << endl;

    nMovimientos = acumularMovimientosDeProducto(archivoEntrada, id, entradas, salidas);
    stock = entradas - salidas;

    if (nMovimientos == 0) {
        archivoReporte << setw(4) << "" << "sin movimientos registrados" << endl;
    }

    imprimirResumenProducto(archivoReporte, entradas, salidas, stock);
    imprimirLineaSeparadora(archivoReporte, 52);
}

void actualizarGlobales(int entradas, int salidas, int stock, int nMovimientos, int id,
    int& totalEntradas, int& totalSalidas, int& nProductos,
    int& productosSinMovimiento, int& idMayorStock, int& mayorStock) {

    totalEntradas += entradas;
    totalSalidas += salidas;
    nProductos++;

    if (nMovimientos == 0) {
        productosSinMovimiento++;
    }
    if (nProductos == 1 or stock > mayorStock) {
        mayorStock = stock;
        idMayorStock = id;
    }
}

void imprimirTotales(ofstream& salida, int totalEntradas, int totalSalidas, int nProductos,
                     int productosSinMovimiento, int idMayorStock, int mayorStock) {
    salida << left << setw(30) << "Productos procesados:"
           << right << setw(12) << nProductos << endl;
    salida << left << setw(30) << "Productos sin movimiento:"
           << right << setw(12) << productosSinMovimiento << endl;
    salida << left << setw(30) << "Total de entradas:"
           << right << setw(12) << totalEntradas << endl;
    salida << left << setw(30) << "Total de salidas:"
           << right << setw(12) << totalSalidas << endl;
    salida << left << setw(30) << "Producto con mayor stock:"
           << right << setw(12) << idMayorStock << endl;
    salida << setw(2) << "" << left << setw(28) << "stock de ese producto:"
           << right << setw(12) << mayorStock << endl;
    imprimirLineaSeparadora(salida, 52);
}

void generarReporte(ifstream& archivoProductos, ifstream& archivoMovimientos, ofstream& salida) {
    int id;
    char sep, categoria;

    int totalEntradas = 0, totalSalidas = 0;
    int nProductos = 0, productosSinMovimiento = 0;
    int idMayorStock = 0, mayorStock = 0;

    imprimirEncabezado(salida);

    while (true) {
        archivoProductos >> id;

        if (archivoProductos.eof()) {
            break;
        }

        archivoProductos >> sep >> categoria;

        int entradas, salidas, stock, nMovimientos;
        imprimirProducto(archivoMovimientos, salida, id, categoria,
                         entradas, salidas, stock, nMovimientos);
        actualizarGlobales(entradas, salidas, stock, nMovimientos, id,
                           totalEntradas, totalSalidas, nProductos,
                           productosSinMovimiento, idMayorStock, mayorStock);
    }

    imprimirTotales(salida, totalEntradas, totalSalidas, nProductos,
                    productosSinMovimiento, idMayorStock, mayorStock);
}
