//
// Created by Eric Huiza on 9/24/26.
//

#ifndef EJERCICIO04_FUNCIONESAUXILIARES_H
#define EJERCICIO04_FUNCIONESAUXILIARES_H

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

#define CAPACIDAD 50
#define ANCHO_REPORTE 55

// Lectura: cada linea de productos.csv es codigo,categoria,precio,stock,importado
void cargarProductos(const char* nombreArchivo, int* codigos, char* categorias,
    double* precios, int* stocks, bool* importados, int& longitud);

// Busquedas: todas devuelven la posicion encontrada o -1 si no hay ninguna
int buscarCodigo(const int* codigos, int longitud, int codigo);
int buscarMasBaratoDisponible(const char* categorias, const double* precios,
    const int* stocks, int longitud, char categoria, double& precio);
int buscarMayorStock(const int* stocks, int longitud, int& mayorStock);
int buscarAgotado(const int* stocks, int longitud, int desde);
int contarPorCategoria(const char* categorias, int longitud, char categoria);

// Procesamiento: no imprime nada, los resultados quedan en arreglos paralelos
// (una posicion por consulta; -1 significa "no encontrado")
void procesarConsultasCodigo(const char* nombreArchivo, const int* codigos, int longitud,
    int* codigosConsulta, int* posicionesConsulta, int& nConsultas);
void procesarConsultasCategoria(const char* nombreArchivo, const char* categorias,
    const double* precios, const int* stocks, int longitud,
    char* categoriasConsulta, int* cantidadesCategoria, int* posicionesBarato,
    double* preciosBarato, int& nCategorias);

// Reporte: solo imprime
void imprimirLineaSeparadora(ofstream& reporte, int longitud, char caracter = '-');
void imprimirTitulo(ofstream& reporte, const char* titulo);
void imprimirConsultaCodigo(ofstream& reporte, int codigo, int pos, const char* categorias,
    const double* precios, const int* stocks);
void imprimirConsultasCodigo(ofstream& reporte, const int* codigosConsulta,
    const int* posicionesConsulta, int nConsultas, const char* categorias,
    const double* precios, const int* stocks);
void imprimirConsultaCategoria(ofstream& reporte, char categoria, int cantidad,
    int pos, double precio, const int* codigos);
void imprimirConsultasCategoria(ofstream& reporte, const char* categoriasConsulta,
    const int* cantidadesCategoria, const int* posicionesBarato,
    const double* preciosBarato, int nCategorias, const int* codigos);
void imprimirMayorStock(ofstream& reporte, const int* codigos, const int* stocks, int longitud);
void imprimirAgotados(ofstream& reporte, const int* codigos, const int* stocks, int longitud);
void generarReporte(const char* nombreArchivo, const int* codigos, const char* categorias,
    const double* precios, const int* stocks, int longitud,
    const int* codigosConsulta, const int* posicionesConsulta, int nConsultas,
    const char* categoriasConsulta, const int* cantidadesCategoria,
    const int* posicionesBarato, const double* preciosBarato, int nCategorias);

// Procesa las consultas de codigo y de categoria y genera el reporte
void gererarReporte(const char* archivoConsultas, const char* archivoCategorias,
    const char* archivoReporte, const int* codigos, const char* categorias,
    const double* precios, const int* stocks, int longitud);

#endif //EJERCICIO04_FUNCIONESAUXILIARES_H
