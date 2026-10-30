#include "Bibliotecas/FuncionesAuxiliates.h"

using namespace std;

int main() {
    char* nombres[TAM_ARREGLO] {};
    char* apellidos[TAM_ARREGLO] {};
    int edades[TAM_ARREGLO] {};

    cargarDatos("ArchivosDeDatos/personas.csv", nombres, apellidos, edades);

    ordenar(nombres, apellidos, edades);

    generarReporte("ArchivosDeReportes/reporte.txt",
        nombres, apellidos, edades);

    liberarMemoria(nombres, apellidos);
    return 0;
}
