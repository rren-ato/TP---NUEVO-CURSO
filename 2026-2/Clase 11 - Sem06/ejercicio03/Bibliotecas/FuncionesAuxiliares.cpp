//
// Created by Eric Huiza on 9/24/26.
//

#include "FuncionesAuxiliares.h"

void cargarProductos(const char* nombreArchivo, int* codigos, char* categorias,
    double* precios, int* stocks, bool* importados, int& longitud) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }

    longitud = 0;
    int codigo;
    char categoria;
    double precio;
    int stock;
    bool importado;
    char c;
    while (archivo >> codigo) {
        archivo
            >> c >> categoria >> c >> precio >> c
            >> stock >> c >> importado;

        codigos[longitud] = codigo;
        categorias[longitud] = categoria;
        precios[longitud] = precio;
        stocks[longitud] = stock;
        importados[longitud] = importado;
        longitud++;
    }
}

int sumarStock(const int* stocks, int longitud) {
    int suma = 0;
    for (int i = 0; i < longitud; i++) {
        suma += stocks[i];
    }
    return suma;
}

int contarAgotados(const int* stocks, int longitud) {
    int cantidad = 0;
    for (int i = 0; i < longitud; i++) {
        if (stocks[i] == 0) {
            cantidad++;
        }
    }
    return cantidad;
}

int contarImportados(const bool* importados, int longitud) {
    int cantidad = 0;
    for (int i = 0; i < longitud; i++) {
        if (importados[i]) {
            cantidad++;
        }
    }
    return cantidad;
}

double calcularValorInventario(const double* precios, const int* stocks, int longitud) {
    double total = 0;
    for (int i = 0; i < longitud; i++) {
        total += precios[i] * stocks[i];
    }
    return total;
}

double calcularPrecioPromedio(const double* precios, int longitud) {
    if (longitud == 0) {
        return 0;
    }

    double suma = 0;
    for (int i = 0; i < longitud; i++) {
        suma += precios[i];
    }
    return suma / longitud;
}

int buscarPosicionMayor(const double* valores, int longitud) {
    if (longitud == 0) {
        return -1;
    }

    int posMayor = 0;
    for (int i = 1; i < longitud; i++) {
        if (valores[i] > valores[posMayor]) {
            posMayor = i;
        }
    }
    return posMayor;
}

int buscarPosicionMenor(const double* valores, int longitud) {
    if (longitud == 0) {
        return -1;
    }

    int posMenor = 0;
    for (int i = 1; i < longitud; i++) {
        if (valores[i] < valores[posMenor]) {
            posMenor = i;
        }
    }
    return posMenor;
}

void imprimirLineaSeparadora(ofstream& reporte, int longitud, char caracter) {
    reporte << setfill(caracter) << setw(longitud) << "" << setfill(' ') << endl;
}

void imprimirEncabezado(ofstream& reporte) {
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE, '=');
    reporte << "REPORTE DE INVENTARIO" << endl;
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE, '=');
    reporte << right << setw(8) << "Codigo"
            << setw(5) << "Cat"
            << setw(10) << "Precio"
            << setw(8) << "Stock"
            << setw(12) << "Valor"
            << setw(2) << "" << left << "Origen" << endl;
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE);
}

void imprimirProducto(ofstream& reporte, int codigo, char categoria,
    double precio, int stock, bool importado) {
    reporte << right << setw(8) << codigo
            << setw(5) << categoria
            << fixed << setprecision(2) << setw(10) << precio
            << setw(8) << stock
            << setw(12) << precio * stock
            << setw(2) << "";
    if (importado) {
        reporte << "Importado" << endl;
    } else {
        reporte << "Nacional" << endl;
    }
}

void imprimirListado(ofstream& reporte, const int* codigos, const char* categorias,
    const double* precios, const int* stocks, const bool* importados, int longitud) {
    imprimirEncabezado(reporte);
    for (int i = 0; i < longitud; i++) {
        imprimirProducto(reporte, codigos[i], categorias[i], precios[i], stocks[i], importados[i]);
    }
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE);
}

void imprimirResumenEntero(ofstream& reporte, const char* etiqueta, int valor) {
    reporte << left << setw(30) << etiqueta << right << setw(25) << valor << endl;
}

void imprimirResumenReal(ofstream& reporte, const char* etiqueta, double valor) {
    reporte << left << setw(30) << etiqueta
            << right << setw(25) << fixed << setprecision(2) << valor << endl;
}

void imprimirExtremo(ofstream& reporte, const char* etiqueta, int pos,
    const int* codigos, const double* precios) {
    imprimirResumenReal(reporte, etiqueta, precios[pos]);
    reporte << setw(2) << "" << "producto " << codigos[pos]
            << " (posicion " << pos << ")" << endl;
}

void imprimirResumen(ofstream& reporte, const int* codigos, const double* precios,
    const int* stocks, const bool* importados, int longitud) {
    imprimirResumenEntero(reporte, "Cantidad de productos:", longitud);
    imprimirResumenEntero(reporte, "Unidades en stock:", sumarStock(stocks, longitud));
    imprimirResumenReal(reporte, "Valor del inventario:",
        calcularValorInventario(precios, stocks, longitud));
    imprimirResumenReal(reporte, "Precio promedio:", calcularPrecioPromedio(precios, longitud));
    imprimirResumenEntero(reporte, "Productos agotados:", contarAgotados(stocks, longitud));
    imprimirResumenEntero(reporte, "Productos importados:", contarImportados(importados, longitud));

    int posMayor = buscarPosicionMayor(precios, longitud);
    int posMenor = buscarPosicionMenor(precios, longitud);
    if (posMayor != -1) {
        imprimirExtremo(reporte, "Precio mas alto:", posMayor, codigos, precios);
        imprimirExtremo(reporte, "Precio mas bajo:", posMenor, codigos, precios);
    }
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE, '=');
}

void generarReporte(const char* nombreArchivo, const int* codigos, const char* categorias,
    const double* precios, const int* stocks, const bool* importados, int longitud) {
    ofstream reporte(nombreArchivo);
    if (!reporte) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }

    imprimirListado(reporte, codigos, categorias, precios, stocks, importados, longitud);
    imprimirResumen(reporte, codigos, precios, stocks, importados, longitud);
}
