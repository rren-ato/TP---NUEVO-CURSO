//
// Created by Eric Huiza on 10/29/26.
//

#include "FuncionesAuxiliates.h"

void cargarDatos(const char* nombreArchivo,
    char** nombres, char** apellidos, int* edades) {

    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No pudo abrir el archivo." << endl;
        exit(1);
    }

    int num = 0;
    while (true) {
        char* nombre = leerCadena(archivo);
        if (nombre == nullptr || archivo.eof()) {
            break;
        }

        char* apellido = leerCadena(archivo);

        nombres[num] = nombre;
        apellidos[num] = apellido;
        archivo >> edades[num];
        archivo.ignore();

        num++;
    }
}

int numPersonas(char** nombres) {
    int i = 0;
    for (;nombres[i];i++);
    return i;
}

void ordenar(char** nombres, char** apellidos, int* edades) {
    int n = numPersonas(nombres);

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(nombres[i], nombres[j]) > 0 ||

                (strcmp(nombres[i], nombres[j]) == 0 &&
                strcmp(apellidos[i], apellidos[j]) > 0) ||

                (strcmp(nombres[i], nombres[j]) == 0 &&
                strcmp(apellidos[i], apellidos[j]) == 0 &&
                edades[i] > edades[j])) {

                intercambio(nombres[i], nombres[j]);
                intercambio(apellidos[i], apellidos[j]);
                intercambio(edades[i], edades[j]);
            }
        }
    }
}

void intercambio(char*& a, char*& b) {
    char* aux = a;
    a = b;
    b = aux;
}

void intercambio(int& a, int& b) {
    int aux = a;
    a = b;
    b = aux;
}

void generarReporte(const char* nombreArchivo,
    char** nombres, char** apellidos, int* edades) {

    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    archivo
        << left << setw(30) << "NOMBRES"
        << setw(30) << "APELLIDOS"
        << setw(20) << "EDAD"
        << endl;

    for (int i = 0; nombres[i]; i++) {
        archivo
            << left << setw(30) << nombres[i]
            << setw(30) << apellidos[i]
            << setw(20) << edades[i] << endl;
    }
}

// Mecanismo de lectura de cadenas exactas.
char* leerCadena(ifstream& archivo, char delim) {
    char buffer[TAM_BUFFER];
    archivo.getline(buffer, TAM_BUFFER, delim);

    if (archivo.eof()) {
        return nullptr;
    }

    char* cadena = new char[strlen(buffer) + 1];
    strcpy(cadena, buffer);
    return cadena;
}

void liberarMemoria(char** nombres, char** apellidos) {
    for (int i = 0; nombres[i]; i++) {
        delete[] nombres[i];
    }

    for (int i = 0; apellidos[i]; i++) {
        delete[] apellidos[i];
    }
}