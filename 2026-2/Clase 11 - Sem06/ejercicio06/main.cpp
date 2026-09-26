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

    // resultado de cada insercion de nuevos.csv: codigo y posicion (-1 = sin capacidad)
    int codigosNuevos[CAPACIDAD];
    int posicionesNuevos[CAPACIDAD];
    int nNuevos;

    // productos.csv viene desordenado: se inserta en orden al cargar
    cargarProductos("ArchivosDeDatos/productos.csv",
        codigos, categorias, precios, stocks, importados, longitud);

    procesarNuevos("ArchivosDeDatos/nuevos.csv", codigos, categorias, precios, stocks,
        importados, longitud, codigosNuevos, posicionesNuevos, nNuevos);

    generarReporte("ArchivosDeReportes/reporte.txt", codigosNuevos, posicionesNuevos, nNuevos,
        codigos, categorias, precios, stocks, importados, longitud);

    return 0;
}
