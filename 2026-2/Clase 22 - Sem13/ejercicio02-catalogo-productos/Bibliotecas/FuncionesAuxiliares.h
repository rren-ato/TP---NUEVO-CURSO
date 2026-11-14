//
// Proyecto: CatalogoProductos
// Archivo:  FuncionesAuxiliares.h
// Autor:    Eric Huiza
//
// Creado el domingo 8 de noviembre del 2026
//
#ifndef CATALOGOPRODUCTOS_FUNCIONESAUXILIARES_H
#define CATALOGOPRODUCTOS_FUNCIONESAUXILIARES_H


#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "Nodo.h"
#include "Producto.h"

using namespace std;

#define STOCK_MINIMO 5

// Creación y actualización del catálogo
void crearLista(const char* nombArch, struct Nodo*& lista);
void agregarProductos(const char* nombArch, struct Nodo*& lista);
void retirarProductos(const char* nombArch, struct Nodo*& lista);
void leerProducto(ifstream& arch, struct Producto& producto);
void leerDatosProducto(ifstream& arch, struct Producto& producto);
char* leerCadenaExacta(ifstream& arch, char delimitador);
void insertarOrdenada(struct Nodo*& lista, struct Producto& producto);
struct Nodo* buscarProducto(int codProd, struct Nodo* lista);
void eliminarDeLaLista(int codProd, struct Nodo*& lista);

// Ventas
void cargarVentas(const char* nombArch, struct Nodo* lista);
void modificarProducto(ifstream& arch, struct Producto& producto);
void calcularTotales(struct Nodo* lista);
void calculaTotalesDeProducto(struct Producto& producto);
void eliminarSinVentas(struct Nodo*& lista);

// Reportes
void mostrarLista(const char* nombArch, const char* titulo, struct Nodo* lista);
void imprimeEncabezado(ofstream& arch, const char* titulo);
void imprimeResumen(ofstream& arch, int cantidad, int unidades, double monto);
void imprimeProducto(ofstream& arch, const struct Producto& producto);
void imprimeFecha(ofstream& arch, int fecha);
void imprimeLinea(ofstream& arch, char car, int n);

// Liberación de memoria
void eliminarLista(struct Nodo*& lista);

#endif //CATALOGOPRODUCTOS_FUNCIONESAUXILIARES_H
