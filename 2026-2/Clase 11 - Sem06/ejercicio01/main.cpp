#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    int codigos[CAP_ALU];
    int ciclos[CAP_ALU];
    int notasCodigos[CAP_ALU];
    double notas[CAP_NOT];
    int numAlumnos, numNotas;

    cargarAlumnos("ArchivosDeDatos/alumnos.csv", codigos, ciclos, numAlumnos);
    cargarNotas("ArchivosDeDatos/notas.csv", notasCodigos, notas, numNotas);

    generarReporte("ArchivosDeReportes/reporte.txt", codigos, ciclos,
        notasCodigos, notas, numAlumnos, numNotas);

    return 0;
}
