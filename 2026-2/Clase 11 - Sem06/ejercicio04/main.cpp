#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    int codigos[CAPACIDAD];
    char categorias[CAPACIDAD];
    double precios[CAPACIDAD];
    int stocks[CAPACIDAD];
    bool importados[CAPACIDAD];
    int longitud;

    cargarProductos("ArchivosDeDatos/productos.csv",
        codigos, categorias, precios, stocks, importados, longitud);

    gererarReporte("ArchivosDeDatos/consultas.txt", "ArchivosDeDatos/categorias.txt",
        "ArchivosDeReportes/reporte.txt", codigos, categorias, precios, stocks, longitud);

    return 0;
}
