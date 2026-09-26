//
// Created by Eric Huiza on 9/24/26.
//

#ifndef EJERCICIO03_FUNCIONESAUXILIARES_H
#define EJERCICIO03_FUNCIONESAUXILIARES_H

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

#define CAPACIDAD 50
#define ANCHO_REPORTE 55

// Lectura: cada linea de productos.csv es codigo,categoria,precio,stock,importado
void cargarProductos(const char* nombreArchivo, int* codigos, char* categorias,
    double* precios, int* stocks, bool* importados, int& longitud);

bool agregarProducto(int* codigos, char* categorias, double* precios, int* stocks,
    bool* importados, int capacidad, int& longitud,
    int codigo, char categoria, double precio, int stock, bool importado);

// Resumenes: recorren los arreglos y devuelven un solo valor
int sumarStock(const int* stocks, int longitud);
int contarAgotados(const int* stocks, int longitud);
int contarImportados(const bool* importados, int longitud);
double calcularValorInventario(const double* precios, const int* stocks, int longitud);
double calcularPrecioPromedio(const double* precios, int longitud);

// Extremos: devuelven la POSICION; con ella se leen los demas arreglos
int buscarPosicionMayor(const double* valores, int longitud);
int buscarPosicionMenor(const double* valores, int longitud);

// Reporte
void imprimirLineaSeparadora(ofstream& reporte, int longitud, char caracter = '-');
void imprimirEncabezado(ofstream& reporte);
void imprimirProducto(ofstream& reporte, int codigo, char categoria,
    double precio, int stock, bool importado);
void imprimirListado(ofstream& reporte, const int* codigos, const char* categorias,
    const double* precios, const int* stocks, const bool* importados, int longitud);
void imprimirResumenEntero(ofstream& reporte, const char* etiqueta, int valor);
void imprimirResumenReal(ofstream& reporte, const char* etiqueta, double valor);
void imprimirExtremo(ofstream& reporte, const char* etiqueta, int pos,
    const int* codigos, const double* precios);
void imprimirResumen(ofstream& reporte, const int* codigos, const double* precios,
    const int* stocks, const bool* importados, int longitud);
void generarReporte(const char* nombreArchivo, const int* codigos, const char* categorias,
    const double* precios, const int* stocks, const bool* importados, int longitud);

#endif //EJERCICIO03_FUNCIONESAUXILIARES_H
