//
// Created by lhirsh on 27/10/2026.
//

#ifndef CALIFICADO7_FUNCIONESAUXILIARES_H
#define CALIFICADO7_FUNCIONESAUXILIARES_H

#include <fstream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <iomanip>

#define MAX_DESC 600   // el texto tiene como maximo 600 palabras
#define TAM_BUFFER 500

using namespace std;

// ============================================================
// 1. Cargar datos
// ============================================================
void cargarDatos(char**& dicOtros, int*& arrContOtros, int& tamOtros,
                 char**& dicPalabras, int*& arrContPalabras, int& tamPalabras);
void cargarDiccionario(const char* nombreArchivo, char**& dic, int*& arrCont, int& tamDicc);
void abrirArchivo(ifstream& archNombres, const char* nombreArchivo);
void abrirArchivo(ofstream& archNombres, const char* nombreArchivo);
int cuentaLineasArch(ifstream& arch);
void llenarDiccionario(ifstream& arch, char** dic, int& tamDicc);
char* leerCadenaExacta(ifstream& arch, char sep);

// ============================================================
// 2. Ordenar diccionarios
// ============================================================
void ordenarDiccionarios(char** dicOtros, int tamOtros, char** dicPalabras, int tamPalabras);
void mostrarReporteSimple(char** dic, int tam, ofstream& reporte, const char* titulo);
void ordenarNombres(char** listaNombre, int tamano);
void intercambiar(char*& a, char*& b);
void intercambiar(int& a, int& b);

// ============================================================
// 3. Procesar texto
// ============================================================
void procesarTexto(int* arrContPalabras, int* arrContOtros,
                   char** dicDesc, int* frecDesc, int& tamDesc,
                   int& contOtros, int& contContenido, int& contDesc,
                   char** dicOtros, int tamOtros, char** dicPalabras, int tamPalabras);
void procesarTokens(ifstream& archTexto, int* arrContPalabras, int* arrContOtros,
                    char** dicDesc, int* frecDesc, int& tamDesc,
                    int& contOtros, int& contContenido, int& contDesc,
                    char** dicOtros, int tamOtros, char** dicPalabras, int tamPalabras);
void pasaAMinusculas(char* cadena);
int busquedaBinaria(char** dic, int tamDicc, char* cadena);
void registrarDesconocida(char** dicDesc, int* frecDesc, int& tamDesc, const char* palabra);

// ============================================================
// 4. Generar reportes
// ============================================================
void generarReportes(char** dicOtros, int tamOtros, int* arrContOtros,
                     char** dicPalabras, int tamPalabras, int* arrContPalabras,
                     char** dicDesc, int* frecDesc, int tamDesc,
                     int contOtros, int contContenido, int contDesc);
void escribirDesconocidos(ofstream& archDesc, char** desc, int* frec, int n);
void creaResumenGeneral(int contOtros, int contContenido, int contDesc, int distDesc,
                        ofstream& resumen, int tamOtros, int tamPalabras,
                        int* arrContOtros, int* arrContPalabras);
int cuentaDistintas(int* arrCont, int tam);
void creaHistograma(ofstream& histograma, char** dicPalabras, int tamPalabras, int* arrContPalabras);
void ordenarFrecuencias(char** dic, int tam, int* frec);
bool vaAntes(const char* palabra1, int frec1, const char* palabra2, int frec2);
void imprime(ofstream& histograma, char car, int n);
void creaRankingGeneral(ofstream& ranking, char** dicPalabras, int tamPalabras, int* arrContPalabras,
                        char** dicOtros, int tamOtros, int* arrContOtros);
void imprimirFilaRanking(ofstream& ranking, int pos, const char* palabra, const char* categoria, int frec);

// ============================================================
// 5. Liberar memoria
// ============================================================
void liberarMemoria(char** dicOtros, int* arrContOtros, int tamOtros,
                    char** dicPalabras, int* arrContPalabras, int tamPalabras,
                    char** dicDesc, int tamDesc);

#endif //CALIFICADO7_FUNCIONESAUXILIARES_H
