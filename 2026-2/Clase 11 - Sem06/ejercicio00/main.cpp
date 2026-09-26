#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    int codigos[CAP_ALU];
    char categoriaCodigos[CAP_ALU];
    char categorias[CAP_CAT];
    int numAlumnos, numCategorias;

    cargarAlumnos("ArchivosDeDatos/alumnos.csv", codigos,
        categoriaCodigos, numAlumnos);
    cargarCategorias("ArchivosDeDatos/categorias.csv", categorias,
        numCategorias);

    generarReporte("ArchivosDeReportes/reporte.txt", codigos,
        categoriaCodigos, categorias, numAlumnos, numCategorias);

    // cout << "Se cargaron: " << numAlumnos << ", alumnos" << endl;
    // cout << "Se cargaron: " << numCategorias << ", categorias" << endl;

    return 0;
}
