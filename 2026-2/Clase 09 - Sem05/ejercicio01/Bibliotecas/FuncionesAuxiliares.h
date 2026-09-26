//
// Created by Eric Huiza on 9/17/26.
//

#ifndef EJERCICIO01_FUNCIONESAUXILIARES_H
#define EJERCICIO01_FUNCIONESAUXILIARES_H

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

#define CAPACIDAD 10

void cargarNumeros(const char* nombreArchivo, int* numeros);
void imprimirNumeros(int* numeros);
void calcularPromedio(int* numeros, double& promedio);

#endif //EJERCICIO01_FUNCIONESAUXILIARES_H
