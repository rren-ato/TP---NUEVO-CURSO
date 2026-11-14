//
// Proyecto: CatalogoProductos
// Archivo:  Producto.h
// Autor:    Eric Huiza
//
// Creado el domingo 8 de noviembre del 2026
//
#ifndef CATALOGOPRODUCTOS_PRODUCTO_H
#define CATALOGOPRODUCTOS_PRODUCTO_H
#include "Venta.h"

#define MAX_VENTAS 20

struct Producto {
    int codigo;
    char* descripcion;
    double precio;
    int stock;                          // stock al inicio del período
    struct Venta ventas[MAX_VENTAS];
    int numVen;
    int unidadesVendidas;
    double montoVendido;
    int stockFinal;
};

#endif //CATALOGOPRODUCTOS_PRODUCTO_H
