//
// Created by Eric Huiza on 10/22/26.
//

#ifndef EJERCICIO01_FUNCIONESAUXILIARES_H
#define EJERCICIO01_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>

using namespace std;

// ============================================================
// Funciones de manejo de cadenas
// ============================================================
int mi_strlen(const char*);
void mi_strcpy(char*, const char*);
int mi_strcmp(const char*, const char*);
void mi_strcat(char*, const char*);
void pasaAMayusculas(char*);
void invertirCadena(char*);

// ============================================================
// Funciones de prueba: concepto de cadena
// ============================================================
void probarCaracterNulo();
void probarInicializacionYAsignacion();

// ============================================================
// Funciones de prueba: funciones propias de cadenas
// ============================================================
void probarMiStrlen();
void probarMiStrcpy();
void probarMiStrcmp();
void probarMiStrcat();
void probarPasaAMayusculas();
void probarInvertirCadena();

// ============================================================
// Funciones de impresion
// ============================================================
void imprimirTitulo(const char*);
void imprimirLinea(char, int);
void imprimirCelda(int, char);
void imprimirLongitud(const char*);
void imprimirComparacion(const char*, const char*);

#endif //EJERCICIO01_FUNCIONESAUXILIARES_H
