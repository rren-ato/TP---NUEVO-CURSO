//
// Created by Eric Huiza on 9/24/26.
//

#include "FuncionesAuxiliares.h"

#include <iosfwd>

void cargarAlumnos(const char* nombreArchivo, int* codigos,
                   int* ciclos, int& numAlumnos) {

    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    int codigo;
    char c;
    numAlumnos = 0;
    while (archivo >> codigo) {
        codigos[numAlumnos] = codigo;
        archivo >> c;
        archivo >> ciclos[numAlumnos];
        numAlumnos++;
    }
}

void cargarNotas(const char* nombreArchivo, int* codigoNotas, double* notas, int& numNotas) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    int codigo;
    char c;
    numNotas = 0;
    while (archivo >> codigo) {
        codigoNotas[numNotas] = codigo;
        archivo >> c;
        archivo >> notas[numNotas];
        numNotas++;
    }
}

int buscarCodigo(const int* codigos, int codigo, int numAlumnos) {
    for (int i = 0; i < numAlumnos; i++) {
        if (codigos[i] == codigo) {
            return i;
        }
    }
    return -1;
}

// int buscarNota(const int* notasCodigos, const double* notas, int codigo, int numNotas, double& nota) {
//     for (int i = 0; i < numNotas; i++) {
//         if (notasCodigos[i] == codigo) {
//             nota = notas[i];
//             return i;
//         }
//     }
//     return -1;
// }

int buscarNota(const int* notasCodigos, int codigo, int numNotas) {
    for (int i = 0; i < numNotas; i++) {
        if (notasCodigos[i] == codigo) {
            return i;
        }
    }
    return -1;
}

void generarReporte(const char* nombreArchivo, int* codigos,
    int* ciclos, int* codigoNotas, double* notas,
    int numAlumnos, int numNotas) {

    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    archivo << "REPORTE DE NOTAS" << endl;
    for (int i = 0; i < numAlumnos; i++) {
        int codigo = codigos[i];
        int ciclo = ciclos[i];
        int pos = buscarNota(codigoNotas, codigo, numNotas);
        archivo << "Código: " << codigo << ", Ciclo" << ciclo;
        if (pos >= 0) {
            double nota = notas[pos];
            archivo << ", Nota: " << fixed << setprecision(2) << nota << endl;
        }
        else {
            archivo << ", Nota: F" << endl;
        }
    }
}