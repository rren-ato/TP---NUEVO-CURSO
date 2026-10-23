#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    // Parte 4: memoria dinamica y arreglos de cadenas
    probarPunteroConMemoria();
    probarArregloDinamicoDeNombres("ArchivosDeDatos/Personas.txt");

    // Parte 5: ejercicios integradores
    probarArregloDeNombres("ArchivosDeDatos/Personas.txt",
                           "ArchivosDeReportes/ReporteNombres.txt");
    probarArchivoCsv("ArchivosDeDatos/personal.csv",
                     "ArchivosDeReportes/ReportePersonal.txt");

    // Parte 6: biblioteca <cstring>
    probarBibliotecaCstring();

    return 0;
}
