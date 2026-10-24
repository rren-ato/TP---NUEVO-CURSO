//
// Created by Eric Huiza on 10/24/26.
//

#ifndef EJERCICIO01_FUNCIONESAUXILIARES_H
#define EJERCICIO01_FUNCIONESAUXILIARES_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

#define TAM_VALOR 50
#define TAM_TIPO 20
#define TAM_MOTIVO 60

// Codigos de motivo: MOTIVO_OK significa que el valor es valido
#define MOTIVO_OK 0
#define MOTIVO_LONGITUD 1
#define MOTIVO_NO_NUMERICO 2
#define MOTIVO_FORMATO_PLACA 3
#define MOTIVO_FORMATO_FECHA 4
#define MOTIVO_MES 5
#define MOTIVO_DIA 6
#define MOTIVO_TIPO 7

// Indices de tipo para el resumen
#define NUM_TIPOS 4
#define TIPO_DNI 0
#define TIPO_PLACA 1
#define TIPO_FECHA 2
#define TIPO_DESCONOCIDO 3

// ============================================================
// Funciones de manejo de cadenas
// ============================================================
int mi_strlen(const char*);
void mi_strcpy(char*, const char*);
int mi_strcmp(const char*, const char*);
void pasaAMayusculas(char*);

// ============================================================
// Funciones de conversion y clasificacion
// ============================================================
bool esEspacio(char);
bool esDigito(char);
bool esMayuscula(char);
int mi_atoi(const char*);
bool sonDigitos(const char*, int, int);
bool sonMayusculas(const char*, int, int);

// ============================================================
// Funciones de calendario
// ============================================================
bool esBisiesto(int);
int diasDelMes(int, int);

// ============================================================
// Funciones de lectura y validacion
// ============================================================
void validarYReportar(const char*, const char*, int*, int*, int&);
bool leerRegistro(ifstream&, char*, char*);
int validarRegistro(const char*, const char*);
int validarDni(const char*);
int validarPlaca(const char*);
int validarFecha(const char*);
bool tieneFormatoDeFecha(const char*);

// ============================================================
// Funciones de apertura e impresion
// ============================================================
void abrirArchivoDeLectura(const char*, ifstream&);
void abrirArchivoDeEscritura(const char*, ofstream&);
void imprimirEncabezado(ofstream&);
void imprimirRegistro(ofstream&, int, const char*, const char*, int);
void imprimirResumen(const char*, int*, int*, int);
void acumularResultado(int*, int*, const char*, int);
int obtenerIndiceTipo(const char*);
void obtenerNombreTipo(int, char*);
void obtenerMotivo(int, char*);
void imprimirTitulo(ofstream&, const char*);
void imprimirLinea(ofstream&, char, int);

#endif //EJERCICIO01_FUNCIONESAUXILIARES_H
