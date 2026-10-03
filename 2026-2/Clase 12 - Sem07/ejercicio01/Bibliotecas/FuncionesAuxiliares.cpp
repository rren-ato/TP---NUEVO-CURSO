//
// Created by Eric Huiza on 10/1/26.
//

#include "FuncionesAuxiliares.h"

#include <iostream>

void ordenarIntercambio(int* numeros, int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = i + 1; j < num; j++) {
            if (numeros[i] > numeros[j]) {
                intercambiar(numeros[i], numeros[j]);
            }
        }
        // imprimirNumeros(numeros, num);
    }
}

void ordenarSeleccion(int* numeros, int num) {
    for (int i = 0; i < num - 1; i++) {
        int m = i;
        for (int j = i + 1; j < num; j++) {
            if (numeros[j] < numeros[m]) {
                m = j;
            }
        }

        if (m != i) {
            intercambiar(numeros[i], numeros[m]);
        }

        // imprimirNumeros(numeros, num);
    }
}

void ordenamientoBurbuja(int* numeros, int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - 1 - i; j++) {
            if (numeros[j] > numeros[j + 1]) {
                intercambiar(numeros[j], numeros[j + 1]);
            }
        }
        // imprimirNumeros(numeros, num);
    }
}

int busquedaBinaria(int* numeros, int num, int llave) {
    int izq = 0;
    int der = num - 1;
    while (izq <= der) {
        int medio = izq + (der - izq) / 2;
        if (numeros[medio] == llave) {
            return medio;
        }
        else if (numeros[medio] < llave) {
            izq = medio + 1;
        }
        else {
            der = medio - 1;
        }
    }
    return -1;
}

void intercambiar(int& n1, int& n2) {
    int aux = n1;
    n1 = n2;
    n2 = aux;
}

void imprimirNumeros(const int* numeros, int num) {
    for (int i = 0; i < num; i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;
}