//
// Created by Eric Huiza on 9/24/26.
//

#ifndef EJERCICIO06_FUNCIONESAUXILIARES_H
#define EJERCICIO06_FUNCIONESAUXILIARES_H

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

#define CAPACIDAD 50
#define NUM_CATEGORIAS 4   // categorias 'A', 'B', 'C' y 'D'
#define ANCHO_REPORTE 62

// Lectura de una linea codigo,categoria,precio,stock,importado.
// Devuelve false al llegar al fin de archivo.
bool leerProducto(ifstream& archivo, int& codigo, char& categoria,
    double& precio, int& stock, bool& importado);

// Insercion ordenada por codigo en los CINCO arreglos paralelos
int insertarOrdenado(int* codigos, char* categorias, double* precios, int* stocks,
    bool* importados, int capacidad, int& longitud,
    int codigo, char categoria, double precio, int stock, bool importado);
void cargarProductos(const char* nombreArchivo, int* codigos, char* categorias,
    double* precios, int* stocks, bool* importados, int& longitud);

void procesarNuevos(const char* nombreArchivo, int* codigos, char* categorias,
    double* precios, int* stocks, bool* importados, int& longitud,
    int* codigosNuevos, int* posicionesNuevos, int& nNuevos);

// Resumen por categoria: arreglos de NUM_CATEGORIAS posiciones,
// el indice de la categoria c es c - 'A'
void inicializarResumen(int* cantidades, int* unidades, double* valores,
    double* sumaPrecios, int* posMasCaro);
void acumularProducto(int pos, const char* categorias, const double* precios,
    const int* stocks, int* cantidades, int* unidades, double* valores,
    double* sumaPrecios, int* posMasCaro);
void calcularResumen(const char* categorias, const double* precios, const int* stocks,
    int longitud, int* cantidades, int* unidades, double* valores,
    double* sumaPrecios, int* posMasCaro);
int buscarCategoriaMayorValor(const double* valores, double& mayorValor);

// Reporte
void imprimirLineaSeparadora(ofstream& reporte, int longitud, char caracter = '-');
void imprimirTitulo(ofstream& reporte, const char* titulo);
void imprimirNuevos(ofstream& reporte, const int* codigosNuevos,
    const int* posicionesNuevos, int nNuevos);
void imprimirListado(ofstream& reporte, const int* codigos, const char* categorias,
    const double* precios, const int* stocks, const bool* importados, int longitud);
void imprimirFilaCategoria(ofstream& reporte, int indice, const int* cantidades,
    const int* unidades, const double* valores, const double* sumaPrecios,
    const int* posMasCaro, const int* codigos);
void imprimirResumen(ofstream& reporte, const int* codigos, const char* categorias,
    const double* precios, const int* stocks, int longitud);
void generarReporte(const char* nombreArchivo, const int* codigosNuevos,
    const int* posicionesNuevos, int nNuevos, const int* codigos, const char* categorias,
    const double* precios, const int* stocks, const bool* importados, int longitud);

#endif //EJERCICIO06_FUNCIONESAUXILIARES_H
