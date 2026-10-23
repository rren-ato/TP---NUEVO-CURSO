//
// Created by Eric Huiza on 10/22/26.
//

#ifndef EJERCICIO02_FUNCIONESAUXILIARES_H
#define EJERCICIO02_FUNCIONESAUXILIARES_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// ============================================================
// Funciones de manejo de cadenas
// ============================================================
int mi_strlen(const char*);
void mi_strcpy(char*, const char*);
void mi_strcat(char*, const char*);
bool corresponde(const char*, const char*);
char* mi_strstr(char*, const char*);
void reemplazar(char*, const char*, const char*);

// ============================================================
// Funciones de conversion de texto a numero
// ============================================================
bool esEspacio(char);
bool esDigito(char);
int mi_atoi(const char*);
double mi_atof(const char*);

// ============================================================
// Funciones de prueba: lectura con >> y formato de salida
// ============================================================
void probarLecturaPorPalabras(const char*);
void probarLecturaDeCampos(const char*);

// ============================================================
// Funciones de prueba: lectura con getline y get
// ============================================================
void probarGetline(const char*);
void probarGet(const char*);
void probarGetlineConArregloPequenio(const char*);
void probarGetConArregloPequenio(const char*);

// ============================================================
// Funciones de prueba: limpieza del buffer de entrada
// ============================================================
void probarLecturaMixtaSinLimpiar(const char*);
void probarLecturaMixtaLimpiando(const char*);

// ============================================================
// Funciones de prueba: busqueda y reemplazo
// ============================================================
void probarMiStrstr();
void probarReemplazar();

// ============================================================
// Funciones de prueba: conversion de texto a numero
// ============================================================
void probarMiAtoi(const char*);
void probarMiAtof(const char*);

// ============================================================
// Funciones de apertura e impresion
// ============================================================
void abrirArchivoDeLectura(const char*, ifstream&);
void imprimirTitulo(const char*);
void imprimirLinea(char, int);
void imprimirEstadoFailbit(ifstream&);
void imprimirNumeroYCadena(int, const char*);
void imprimirBusqueda(char*, const char*);

#endif //EJERCICIO02_FUNCIONESAUXILIARES_H
