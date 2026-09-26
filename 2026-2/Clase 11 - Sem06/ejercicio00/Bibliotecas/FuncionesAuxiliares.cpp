//
// Created by Eric Huiza on 9/24/26.
//

#include "FuncionesAuxiliares.h"

void cargarAlumnos(const char* nombreArchivo,
    int* codigos, char* categoriaCodigos, int& numAlumnos) {

    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    int codigo;
    char c;
    numAlumnos = 0;
    while (archivo >> codigo) {
        codigos[numAlumnos] = codigo;
        archivo >> c >> categoriaCodigos[numAlumnos++];
    }
}

void cargarCategorias(const char* nombreArchivo, char* categorias, int& numCategorias) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }
    numCategorias = 0;
    char categoria;
    while (archivo >> categoria) {
        categorias[numCategorias] = categoria;
        numCategorias++;
    };
}

int buscarCategoria(const char* categorias,
    char categoria, int numCategorias) {

    for (int i = 0; i < numCategorias; i++) {
        if (categorias[i] == categoria) {
            return i;
        }
    }
    return -1;
}

void generarReporte(const char* nombreArchivo,
    const int* codigos, const char* codigoCategorias,
    const char* categorias, int numAlumnos, int numCategorias) {

    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    archivo << "REPORTE DE CAT. (ALUMNO)" << endl;
    for (int i = 0; i < numAlumnos; i++) {
        int codigo = codigos[i];
        char categoria = codigoCategorias[i];

        int pos = buscarCategoria(categorias, categoria, numCategorias);
        if (pos >= 0) {
            archivo << "Código: " << codigo << ", categoría: " << categoria << endl;
        }
        else {
            archivo << "Código: " << codigo << ", categoría: " << "INVÁLIDA" << endl;
        }
    }
}