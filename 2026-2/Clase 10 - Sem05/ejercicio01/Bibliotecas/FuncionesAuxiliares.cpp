//
// Created by Eric Huiza on 9/19/26.
//

#include "FuncionesAuxiliares.h"

void cargarNumeros(const char* nombreArchivo, int* numeros, int& longitud) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }

    longitud = 0;
    int numero;
    while (archivo >> numero) {
        insertarOrdenado(numeros, CAPACIDAD, longitud, numero);

        // numeros[longitud] = numero;
        // longitud++;
    }
}

bool agregar(int* numeros, int capacidad, int& longitud, int numero) {
    if (longitud >= capacidad) {
        return false;
    }

    numeros[longitud] = numero;
    longitud++;

    return true;
}

bool insertar(int* numeros, int capacidad, int& longitud, int pos, int numero) {
    if (longitud >= capacidad || pos < 0 || pos > longitud) {
        return false;
    }

    for (int i = longitud; i > pos; i--) {
        numeros[i] = numeros[i - 1];
    }
    numeros[pos] = numero;
    longitud++;

    return true;
}

bool eliminar(int* numeros, int& longitud, int pos) {
    if (pos < 0 || pos >= longitud) {
        return false;
    }

    for (int i = pos; i < longitud -1; i++) {
        numeros[i] = numeros[i + 1];
    }
    longitud--;

    return true;
}

bool insertarOrdenado(int* numeros, int capacidad, int& longitud, int numero) {
    if (longitud >= capacidad) {
        return false;
    }

    int i = longitud - 1;
    while (i >= 0 && numeros[i] > numero) {
        numeros[i + 1] = numeros[i]; // desplazamos a la derecha
        i--;
    }

    numeros[i + 1] = numero; // insertamos el nuevo número
    longitud++;

    return true;
}

void imprimir(const int* numeros, int longitud) {
    for (int i = 0; i < longitud; i++) {
        cout << setw(3) << numeros[i];
    }
    cout << endl;
}