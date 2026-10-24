//
// Created by Eric Huiza on 10/24/26.
//

#ifndef EJERCICIO02_FUNCIONESAUXILIARES_H
#define EJERCICIO02_FUNCIONESAUXILIARES_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

#define MAX_TEXTO 12000
#define MAX_LISTA 2000
#define MAX_LINEA 300
#define TAM_PALABRA 50
#define MAX_TERMINOS 50

// ============================================================
// Funciones de manejo de cadenas
// ============================================================
int mi_strlen(const char*);
void mi_strcpy(char*, const char*);
void mi_strcat(char*, const char*);
bool corresponde(const char*, const char*);
char* mi_strstr(char*, const char*);
void reemplazarEnTexto(char*, const char*, const char*);
int reemplazarTodas(char*, const char*, const char*);
void pasaAMinusculas(char*);
bool extraerCadena(char*&, const char*, char*);

// ============================================================
// Funciones de clasificacion de caracteres
// ============================================================
bool esMinuscula(char);
bool esDigito(char);
bool esCaracterValido(char);
bool esLimite(char);

// ============================================================
// Funciones de carga
// ============================================================
void cargarArchivo(const char*, char*);
void cargarStopWords(const char*, char*);

// ============================================================
// Funciones de normalizacion
// ============================================================
void normalizarTexto(char*, char*, char*, int&, int&, int&, int&);
int aplicarEquivalencias(char*, char*);
int aplicarEquivalencia(char*, char*);
int removerSignos(char*);
int removerStopWords(char*, char*);
int filtrarLinea(char*, char*, char*);
bool esStopWord(const char*, char*);
void agregarPalabra(char*, const char*);

// ============================================================
// Funciones de busqueda de terminos
// ============================================================
int contarTerminos(char*, char*, int*);
int contarApariciones(char*, const char*);
bool esPalabraCompleta(char*, char*, int);
int contarLineas(char*);

// ============================================================
// Funciones de apertura e impresion
// ============================================================
void abrirArchivoDeLectura(const char*, ifstream&);
void abrirArchivoDeEscritura(const char*, ofstream&);
void escribirTexto(const char*, const char*);
void imprimirReporte(const char*, char*, char*, int*, int, int, int, int);
void imprimirFrecuencias(ofstream&, char*, int*);
void imprimirDato(ofstream&, const char*, int);
void imprimirTitulo(ofstream&, const char*);
void imprimirLinea(ofstream&, char, int);

#endif //EJERCICIO02_FUNCIONESAUXILIARES_H
