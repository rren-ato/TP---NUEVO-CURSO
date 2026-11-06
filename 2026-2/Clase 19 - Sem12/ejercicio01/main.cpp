#include <iostream>
#include <iomanip>

#include "Bibliotecas/Alumno.h"
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    // struct Alumno* alumnos = new struct Alumno[TAM_ALUMNOS];
    struct Alumno alumnos[TAM_ALUMNOS];
    int num;

    cargarDatos("ArchivosDeDatos/alumnos.csv", alumnos, num);
    // ordebarPorPromedio(alumnos, num);
    ordenarPorNombre(alumnos, num);
    generarReporte("ArchivosDeReportes/reporte.txt", alumnos, num);
    // liberarMemoria(alumnos, num);
    // delete[] alumnos;

    // struct Alumno a {
    //     2024202020,
    //     "Juan Perez",
    //     19.0,
    //     4,
    //     true
    // };
    // struct Alumno a;
    // a.codigo = 2024202020;
    // a.ciclo = 4;
    // a.promedio = 19.0;
    // a.matriculado = true;
    // strcpy(a.nombre, "Juan Perez");
    //
    // imprimirEncabezado();
    // imprimirAlumno(a);

    return 0;
}
