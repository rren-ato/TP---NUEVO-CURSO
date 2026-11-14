//
// Proyecto: CatalogoProductos
// Archivo:  Nodo.h
// Autor:    Eric Huiza
//
// Creado el domingo 8 de noviembre del 2026
//
#ifndef CATALOGOPRODUCTOS_NODO_H
#define CATALOGOPRODUCTOS_NODO_H
#include "Producto.h"

struct Nodo {
    struct Producto producto;
    struct Nodo* siguiente;
};

#endif //CATALOGOPRODUCTOS_NODO_H
