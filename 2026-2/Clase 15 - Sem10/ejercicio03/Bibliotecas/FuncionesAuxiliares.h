//
// Created by Eric Huiza on 10/22/26.
//

#ifndef EJERCICIO03_FUNCIONESAUXILIARES_H
#define EJERCICIO03_FUNCIONESAUXILIARES_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

using namespace std;

#define CAPACIDAD 200

// ============================================================
// Funciones de manejo de cadenas
// ============================================================
int mi_strlen(const char*);
void mi_strcpy(char*, const char*);
int mi_strcmp(const char*, const char*);
void pasaAMayusculas(char*);

// ============================================================
// Funciones de memoria dinamica
// ============================================================
char* leeCadenaExacta(ifstream&);
int contarLineas(const char*);

// ============================================================
// Funciones del arreglo de cadenas (ejercicio integrador 1)
// ============================================================
void leeNombres(char**, int&, const char*);
void pasaAMayusculasTodo(char**, int);
void ordenaNombres(char**, int);
void cambiar(char*&, char*&);
void imprimeNombres(char**, int, const char*);
void liberaNombres(char**, int);

// ============================================================
// Funciones del archivo CSV (ejercicio integrador 2)
// ============================================================
void leeDatosDelArchivo(int*, char**, double*, int&, const char*);
void leerLinea(ifstream&, int&, char*&, double&);
void ordenarEmpleados(int*, char**, double*, int);
void cambiarDni(int&, int&);
void cambiarSueldo(double&, double&);
void imprimirEmpleados(int*, char**, double*, int, const char*);

// ============================================================
// Funciones de prueba: memoria dinamica y arreglos de cadenas
// ============================================================
void probarPunteroConMemoria();
void probarArregloDeNombres(const char*, const char*);
void probarArregloDinamicoDeNombres(const char*);
void probarArchivoCsv(const char*, const char*);

// ============================================================
// Funciones de prueba: biblioteca <cstring>
// ============================================================
void probarBibliotecaCstring();
void probarCopiaYConcatenacionConCstring();
void probarComparacionConCstring();
void probarBusquedaConCstring();

// ============================================================
// Funciones de apertura e impresion
// ============================================================
void abrirArchivoDeLectura(const char*, ifstream&);
void abrirArchivoDeEscritura(const char*, ofstream&);
void imprimirTitulo(const char*);
void imprimirLinea(char, int);
void imprimirNombresEnPantalla(char**, int);

#endif //EJERCICIO03_FUNCIONESAUXILIARES_H
