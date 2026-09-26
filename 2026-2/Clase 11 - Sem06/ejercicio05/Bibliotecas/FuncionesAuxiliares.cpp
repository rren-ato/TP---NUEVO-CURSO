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
    char coma;
    while (archivo >> codigo) {
        archivo >> coma >> categoria >> coma >> precio >> coma >> stock >> coma >> importado;
        codigos[longitud] = codigo;
        categorias[longitud] = categoria;
        precios[longitud] = precio;
        stocks[longitud] = stock;
        importados[longitud] = importado;
        longitud++;
    }
}

void cargarVentas(const char* nombreArchivo, int* codigosVenta, int* cantidades,
    int& nVentas) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }

    nVentas = 0;
    int codigo;
    int cantidad;
    char coma;
    while (archivo >> codigo) {
        archivo >> coma >> cantidad;
        codigosVenta[nVentas] = codigo;
        cantidades[nVentas] = cantidad;
        nVentas++;
    }
}

int buscarCodigo(const int* codigos, int longitud, int codigo) {
    for (int i = 0; i < longitud; i++) {
        if (codigos[i] == codigo) {
            return i;
        }
    }
    return -1;
}

// Los arreglos que se modifican (stocks, unidadesVendidas, ingresos) no llevan const:
// la venta descuenta el stock y acumula en la MISMA posicion del producto.
char atenderVenta(int codigo, int cantidad, const int* codigos, const double* precios,
    int* stocks, int* unidadesVendidas, double* ingresos, int longitud) {
    int pos = buscarCodigo(codigos, longitud, codigo);
    if (pos == -1) {
        return NO_REGISTRADO;
    }
    if (stocks[pos] < cantidad) {
        return SIN_STOCK;
    }

    stocks[pos] -= cantidad;
    unidadesVendidas[pos] += cantidad;
    ingresos[pos] += cantidad * precios[pos];
    return ATENDIDA;
}

void procesarVentas(const int* codigosVenta, const int* cantidades, char* estados,
    int nVentas, const int* codigos, const double* precios, int* stocks,
    int* unidadesVendidas, double* ingresos, int longitud) {
    for (int i = 0; i < nVentas; i++) {
        estados[i] = atenderVenta(codigosVenta[i], cantidades[i], codigos, precios,
            stocks, unidadesVendidas, ingresos, longitud);
    }
}

int contarEstado(const char* estados, int nVentas, char estado) {
    int cantidad = 0;
    for (int i = 0; i < nVentas; i++) {
        if (estados[i] == estado) {
            cantidad++;
        }
    }
    return cantidad;
}

double sumarIngresos(const double* ingresos, int longitud) {
    double total = 0;
    for (int i = 0; i < longitud; i++) {
        total += ingresos[i];
    }
    return total;
}

int contarSinVentas(const int* unidadesVendidas, int longitud) {
    int cantidad = 0;
    for (int i = 0; i < longitud; i++) {
        if (unidadesVendidas[i] == 0) {
            cantidad++;
        }
    }
    return cantidad;
}

int buscarMasVendido(const int* unidadesVendidas, int longitud, int& unidades) {
    if (longitud == 0) {
        return -1;
    }

    int pos = 0;
    for (int i = 1; i < longitud; i++) {
        if (unidadesVendidas[i] > unidadesVendidas[pos]) {
            pos = i;
        }
    }
    unidades = unidadesVendidas[pos];
    return pos;
}

int buscarMayorIngreso(const double* ingresos, int longitud, double& ingreso) {
    if (longitud == 0) {
        return -1;
    }

    int pos = 0;
    for (int i = 1; i < longitud; i++) {
        if (ingresos[i] > ingresos[pos]) {
            pos = i;
        }
    }
    ingreso = ingresos[pos];
    return pos;
}

void imprimirLineaSeparadora(ofstream& reporte, int longitud, char caracter) {
    reporte << setfill(caracter) << setw(longitud) << "" << setfill(' ') << endl;
}

void imprimirTitulo(ofstream& reporte, const char* titulo) {
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE, '=');
    reporte << titulo << endl;
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE, '=');
}

void imprimirEstado(ofstream& reporte, char estado) {
    if (estado == ATENDIDA) {
        reporte << "Atendida" << endl;
    } else if (estado == SIN_STOCK) {
        reporte << "Stock insuficiente" << endl;
    } else {
        reporte << "Producto no registrado" << endl;
    }
}

void imprimirVentas(ofstream& reporte, const int* codigosVenta, const int* cantidades,
    const char* estados, int nVentas) {
    imprimirTitulo(reporte, "DETALLE DE VENTAS");
    reporte << right << setw(5) << "Nro" << setw(9) << "Codigo" << setw(10) << "Cantidad"
            << setw(2) << "" << left << "Estado" << endl;
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE);

    for (int i = 0; i < nVentas; i++) {
        reporte << right << setw(5) << i + 1
                << setw(9) << codigosVenta[i]
                << setw(10) << cantidades[i]
                << setw(2) << "";
        imprimirEstado(reporte, estados[i]);
    }
    reporte << endl;
}

void imprimirProductos(ofstream& reporte, const int* codigos, const double* precios,
    const int* stocks, const int* unidadesVendidas, const double* ingresos, int longitud) {
    imprimirTitulo(reporte, "VENTAS POR PRODUCTO");
    reporte << right << setw(8) << "Codigo" << setw(10) << "Precio" << setw(10) << "Vendidas"
            << setw(12) << "Ingreso" << setw(13) << "Stock final" << endl;
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE);

    for (int i = 0; i < longitud; i++) {
        reporte << right << setw(8) << codigos[i]
                << fixed << setprecision(2) << setw(10) << precios[i]
                << setw(10) << unidadesVendidas[i]
                << setw(12) << ingresos[i]
                << setw(13) << stocks[i] << endl;
    }
    reporte << endl;
}

void imprimirResumenEntero(ofstream& reporte, const char* etiqueta, int valor) {
    reporte << left << setw(30) << etiqueta << right << setw(25) << valor << endl;
}

void imprimirResumenReal(ofstream& reporte, const char* etiqueta, double valor) {
    reporte << left << setw(30) << etiqueta
            << right << setw(25) << fixed << setprecision(2) << valor << endl;
}

void imprimirResumen(ofstream& reporte, const char* estados, int nVentas,
    const int* codigos, const int* unidadesVendidas, const double* ingresos, int longitud) {
    int unidades = 0;
    double ingreso = 0;
    int posMasVendido = buscarMasVendido(unidadesVendidas, longitud, unidades);
    int posMayorIngreso = buscarMayorIngreso(ingresos, longitud, ingreso);

    imprimirTitulo(reporte, "RESUMEN");
    imprimirResumenEntero(reporte, "Ventas atendidas:", contarEstado(estados, nVentas, ATENDIDA));
    imprimirResumenEntero(reporte, "Ventas sin stock:", contarEstado(estados, nVentas, SIN_STOCK));
    imprimirResumenEntero(reporte, "Ventas no registradas:", contarEstado(estados, nVentas, NO_REGISTRADO));
    imprimirResumenReal(reporte, "Ingreso total:", sumarIngresos(ingresos, longitud));
    imprimirResumenEntero(reporte, "Productos sin ventas:", contarSinVentas(unidadesVendidas, longitud));
    imprimirResumenEntero(reporte, "Mas vendido (unidades):", unidades);
    reporte << setw(2) << "" << "producto " << codigos[posMasVendido] << endl;
    imprimirResumenReal(reporte, "Mayor ingreso:", ingreso);
    reporte << setw(2) << "" << "producto " << codigos[posMayorIngreso] << endl;
    imprimirLineaSeparadora(reporte, ANCHO_REPORTE, '=');
}

void generarReporte(const char* nombreArchivo, const int* codigosVenta, const int* cantidades,
    const char* estados, int nVentas, const int* codigos, const double* precios,
    const int* stocks, const int* unidadesVendidas, const double* ingresos, int longitud) {
    ofstream reporte(nombreArchivo);
    if (!reporte) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }

    imprimirVentas(reporte, codigosVenta, cantidades, estados, nVentas);
    imprimirProductos(reporte, codigos, precios, stocks, unidadesVendidas, ingresos, longitud);
    imprimirResumen(reporte, estados, nVentas, codigos, unidadesVendidas, ingresos, longitud);
}
