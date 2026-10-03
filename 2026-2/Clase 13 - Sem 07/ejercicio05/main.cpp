#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    int* codigos;
    int* ciclos;
    double* notas;
    double* promedios;
    int* codigoNotas;

    int numAlumnos;
    int numNotas;

    cargarAlumnos("ArchivosDeDatos/alumnos.csv", codigos, ciclos, numAlumnos);
    cargarNotas("ArchivosDeDatos/notas.csv", codigoNotas, notas, numNotas);

    calcularPromedios(codigos, codigoNotas, notas, promedios, numAlumnos, numNotas);
    // ordenarPromediosBurbuja(promedios, numAlumnos);
    // ordenarAlumnosPorPromedio(codigos, ciclos, promedios, numAlumnos);
    ordenarAlumnosPorCiclos(codigos, ciclos, promedios, numAlumnos);
    imprimirRanking(codigos, ciclos, promedios, numAlumnos);

    delete[] codigos;
    delete[] ciclos;
    delete[] notas;
    delete[] promedios;
    delete[] codigoNotas;

    return 0;
}
