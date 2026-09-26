//
// Created by Eric Huiza on 9/24/26.
//

#ifndef EJERCICIO05_FUNCIONESAUXILIARES_H
#define EJERCICIO05_FUNCIONESAUXILIARES_H

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

#define CAPACIDAD 50
#define ANCHO_REPORTE 55

// Estados posibles de una venta (arreglo de char paralelo a las ventas)
#define ATENDIDA 'A'
#define SIN_STOCK 'S'
#define NO_REGISTRADO 'N'

// Lectura de productos.csv: codigo,categoria,precio,stock,importado
void cargarProductos(const char* nombreArchivo, int* codigos, char* categorias,
    double* precios, int* stocks, bool* importados, int& longitud);

// Lectura de ventas.csv: codigo,cantidad
void cargarVentas(const char* nombreArchivo, int* codigosVenta, int* cantidades,
    int& nVentas);

int buscarCodigo(const int* codigos, int longitud, int codigo);

// Enlace: por cada venta busca el producto, valida el stock y acumula
char atenderVenta(int codigo, int cantidad, const int* codigos, const double* precios,
    int* stocks, int* unidadesVendidas, double* ingresos, int longitud);
void procesarVentas(const int* codigosVenta, const int* cantidades, char* estados,
    int nVentas, const int* codigos, const double* precios, int* stocks,
    int* unidadesVendidas, double* ingresos, int longitud);

// Resumenes
int contarEstado(const char* estados, int nVentas, char estado);
double sumarIngresos(const double* ingresos, int longitud);
int contarSinVentas(const int* unidadesVendidas, int longitud);
int buscarMasVendido(const int* unidadesVendidas, int longitud, int& unidades);
int buscarMayorIngreso(const double* ingresos, int longitud, double& ingreso);

// Reporte
void imprimirLineaSeparadora(ofstream& reporte, int longitud, char caracter = '-');
void imprimirTitulo(ofstream& reporte, const char* titulo);
void imprimirEstado(ofstream& reporte, char estado);
void imprimirVentas(ofstream& reporte, const int* codigosVenta, const int* cantidades,
    const char* estados, int nVentas);
void imprimirProductos(ofstream& reporte, const int* codigos, const double* precios,
    const int* stocks, const int* unidadesVendidas, const double* ingresos, int longitud);
void imprimirResumenEntero(ofstream& reporte, const char* etiqueta, int valor);
void imprimirResumenReal(ofstream& reporte, const char* etiqueta, double valor);
void imprimirResumen(ofstream& reporte, const char* estados, int nVentas,
    const int* codigos, const int* unidadesVendidas, const double* ingresos, int longitud);
void generarReporte(const char* nombreArchivo, const int* codigosVenta, const int* cantidades,
    const char* estados, int nVentas, const int* codigos, const double* precios,
    const int* stocks, const int* unidadesVendidas, const double* ingresos, int longitud);

#endif //EJERCICIO05_FUNCIONESAUXILIARES_H
