//
// Created by Eric Huiza on 10/29/26.
//

#ifndef EJERCICIO02_FUNCIONESAUXILIATES_H
#define EJERCICIO02_FUNCIONESAUXILIATES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#define TAM_ARREGLO 50
#define TAM_BUFFER 100

void cargarDatos(const char* nombreArchivo,
    char** nombres, char** apellidos, int* edades);

char* leerCadena(ifstream& archivo, char delim = ',');
int numPersonas(char** nombres);

void ordenar(char** nombres, char** apellidos, int* edades);
void intercambio(char*& a, char*& b);
void intercambio(int& a, int& b);

void generarReporte(const char* nombreArchivo,
    char** nombres, char** apellidos, int* edades);

void liberarMemoria(char** nombres, char** apellidos);

#endif //EJERCICIO02_FUNCIONESAUXILIATES_H
