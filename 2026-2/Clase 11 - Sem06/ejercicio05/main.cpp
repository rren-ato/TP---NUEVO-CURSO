#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    // arreglos paralelos de productos
    int codigos[CAPACIDAD];
    char categorias[CAPACIDAD];
    double precios[CAPACIDAD];
    int stocks[CAPACIDAD];
    bool importados[CAPACIDAD];
    int unidadesVendidas[CAPACIDAD] {};
    double ingresos[CAPACIDAD] {};
    int longitud;

    // arreglos paralelos de ventas
    int codigosVenta[CAPACIDAD];
    int cantidades[CAPACIDAD];
    char estados[CAPACIDAD];
    int nVentas;

    cargarProductos("ArchivosDeDatos/productos.csv",
        codigos, categorias, precios, stocks, importados, longitud);
    cargarVentas("ArchivosDeDatos/ventas.csv", codigosVenta, cantidades, nVentas);

    procesarVentas(codigosVenta, cantidades, estados, nVentas,
        codigos, precios, stocks, unidadesVendidas, ingresos, longitud);

    generarReporte("ArchivosDeReportes/reporte.txt", codigosVenta, cantidades, estados, nVentas,
        codigos, precios, stocks, unidadesVendidas, ingresos, longitud);

    return 0;
}
