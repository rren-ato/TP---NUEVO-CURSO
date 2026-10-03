//
// Created by Eric Huiza on 10/3/26.
//

#include "FuncionesAuxiliares.h"

void cargarNumeros(const char* nombreArchivo, int*& numeros, int& num) {
    int buffer[200];

    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    int numero;
    num = 0;
    while (archivo >> numero) {
        buffer[num] = numero;
        num++;
    }

    numeros = new int[num];
    for (int i = 0; i < num; i++) {
        numeros[i] = buffer[i];
    }
}