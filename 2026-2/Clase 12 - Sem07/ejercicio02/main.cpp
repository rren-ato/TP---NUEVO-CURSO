#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    int codigos[CAPACIDAD];
    int ciclos[CAPACIDAD];
    double notas[CAPACIDAD];
    double promedios[CAPACIDAD];
    int codigoNotas[CAPACIDAD];
    int numAlumnos;
    int numNotas;

    cargarAlumnos("ArchivosDeDatos/alumnos.csv", codigos, ciclos, numAlumnos);
    cargarNotas("ArchivosDeDatos/notas.csv", codigoNotas, notas, numNotas);

    calcularPromedios(codigos, codigoNotas, notas, promedios, numAlumnos, numNotas);
    // ordenarPromediosBurbuja(promedios, numAlumnos);
    // ordenarAlumnosPorPromedio(codigos, ciclos, promedios, numAlumnos);
    ordenarAlumnosPorCiclos(codigos, ciclos, promedios, numAlumnos);
    imprimirRanking(codigos, ciclos, promedios, numAlumnos);

    return 0;
}
