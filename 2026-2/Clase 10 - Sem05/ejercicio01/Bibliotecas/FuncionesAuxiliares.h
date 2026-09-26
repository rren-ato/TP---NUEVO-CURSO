//
// Created by Eric Huiza on 9/19/26.
//

#ifndef EJERCICIO01_FUNCIONESAUXILIARES_H
#define EJERCICIO01_FUNCIONESAUXILIARES_H

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

#define CAPACIDAD 20

void cargarNumeros(const char* nombreArchivo,
    int* numeros, int& longitud);

bool agregar(int* numeros, int capacidad, int& longitud, int numero);
bool insertar(int* numeros, int capacidad, int& longitud, int pos, int numero);
bool eliminar(int* numeros, int& longitud, int pos);
bool insertarOrdenado(int* numeros, int capacidad, int& longitud, int numero);

void imprimir(const int* numeros, int longitud);

#endif //EJERCICIO01_FUNCIONESAUXILIARES_H
