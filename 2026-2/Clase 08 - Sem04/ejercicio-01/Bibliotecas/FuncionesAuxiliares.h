#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>

using namespace std;

bool abrirArchivos(ifstream& archivoProductos, ifstream& archivoMovimientos, ofstream& archivoReporte);
void cerrarArchivos(ifstream& archivoProductos, ifstream& archivoMovimientos, ofstream& archivoReporte);

void imprimirLineaSeparadora(ofstream& archivoReporte, int longitud, char caracter = '-');
void imprimirEncabezado(ofstream& archivoReporte);

int acumularMovimientosDeProducto(ifstream& archivoMovimientos, int idProducto,
    int& entradas, int& salidas);

void imprimirResumenProducto(ofstream& archivoReporte, int entradas, int salidas, int stock);
void imprimirProducto(ifstream& archivoMovimientos, ofstream& archivoReporte, int id, char categoria,
    int& entradas, int& salidas, int& stock, int& nMovimientos);

void actualizarGlobales(int entradas, int salidas, int stock, int nMovimientos, int id,
    int& totalEntradas, int& totalSalidas, int& nProductos, int& productosSinMovimiento,
    int& idMayorStock, int& mayorStock);

void imprimirTotales(ofstream& archivoReporte, int totalEntradas, int totalSalidas, int nProductos,
    int productosSinMovimiento, int idMayorStock, int mayorStock);

void generarReporte(ifstream& archivoProductos, ifstream& archivoMovimientos, ofstream& archivoReporte);

#endif
