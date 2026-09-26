//
// Created by Eric Huiza on 9/17/26.
//

#include "FuncionesAuxiliares.h"

void cargarNumeros(const char* nombreArchivo, int* numeros) {
    ifstream archivo(nombreArchivo);
    int numero;
    int index = 0;
    while (archivo >> numero) {
        numeros[index++] = numero;
    }
    archivo.close();
}

void imprimirNumeros(int* numeros) {
    for (int i = 0; i < CAPACIDAD; i++) {
        cout << setw(2) << numeros[i] << endl;
    }
}

void calcularPromedio(int* numeros, double& promedio) {
    int suma = 0;
    for (int i = 0; i < CAPACIDAD; i++) {
        suma += numeros[i];
    }
    promedio = suma / CAPACIDAD;
}