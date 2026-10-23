//
// Created by Eric Huiza on 10/22/26.
//

#include "FuncionesAuxiliares.h"

// ============================================================
// Funciones de manejo de cadenas
// ============================================================

int mi_strlen(const char* cadena) {
    int nCar;
    for (nCar = 0; cadena[nCar]; nCar++) {}
    return nCar;
}

void mi_strcpy(char* destino, const char* fuente) {
    int i = 0;
    while (true) {
        destino[i] = fuente[i];
        if (fuente[i] == 0) {
            break;   // ya copio el '\0'
        }
        i++;
    }
}

int mi_strcmp(const char* cad1, const char* cad2) {
    int i = 0;
    while (cad1[i] == cad2[i]) {
        if (cad1[i] == 0) {
            return 0;   // iguales
        }
        i++;
    }
    return cad1[i] - cad2[i];   // diferencia ASCII
}

void mi_strcat(char* cadena1, const char* cadena2) {
    int pos = mi_strlen(cadena1);   // posicion del '\0'
    mi_strcpy(&cadena1[pos], cadena2);
}

void pasaAMayusculas(char* cadena) {
    for (int i = 0; cadena[i]; i++) {
        if (cadena[i] >= 'a' and cadena[i] <= 'z') {
            cadena[i] -= 'a' - 'A';   // resta 32
        }
    }
}

void invertirCadena(char* cadena) {
    char aux[200];
    int lon = mi_strlen(cadena);
    for (int i = 0, j = lon - 1; cadena[i]; i++, j--) {
        aux[i] = cadena[j];
    }
    aux[lon] = 0;   // cierra la cadena auxiliar
    mi_strcpy(cadena, aux);
}

// ============================================================
// Funciones de prueba: concepto de cadena
// ============================================================

void probarCaracterNulo() {
    char arr[20] = "Juana Robles";
    imprimirTitulo("Una cadena es un arreglo de caracteres terminado en '\\0'");
    cout << left << setw(10) << "INDICE" << setw(10) << "CARACTER"
         << right << setw(6) << "ASCII" << endl;

    int i;
    for (i = 0; arr[i]; i++) {   // '\0' vale 0 (falso) y detiene el ciclo
        imprimirCelda(i, arr[i]);
    }
    imprimirCelda(i, arr[i]);   // el terminador

    cout << "Caracteres validos: " << i << endl;
    cout << "Capacidad de char arr[20]: " << 20 - 1 << " caracteres" << endl;
    cout << "ASCII de '0' : " << (int)'0' << endl;
    cout << "ASCII de '\\0': " << (int)'\0' << endl;
}

void probarInicializacionYAsignacion() {
    char nombre[20] = "Maria";   // correcto: inicializacion
    char apellido[20];
    char iniciales[3];
    imprimirTitulo("Inicializacion frente a asignacion");

    // apellido = "Gonzales";   // ERROR: apellido es la direccion constante del arreglo
    mi_strcpy(apellido, "Gonzales");   // correcto: copia caracter a caracter

    iniciales[0] = 'M';   // asignacion elemento por elemento
    iniciales[1] = 'G';
    iniciales[2] = '\0';

    cout << left << setw(12) << "nombre:" << nombre << endl;
    cout << left << setw(12) << "apellido:" << apellido << endl;
    cout << left << setw(12) << "iniciales:" << iniciales << endl;
    cout << "ASCII de nombre[5] a nombre[7]: " << (int)nombre[5] << " "
         << (int)nombre[6] << " " << (int)nombre[7] << endl;
}

// ============================================================
// Funciones de prueba: funciones propias de cadenas
// ============================================================

void probarMiStrlen() {
    imprimirTitulo("mi_strlen: cantidad de caracteres validos");
    imprimirLongitud("Hola");
    imprimirLongitud("Juana Robles");
    imprimirLongitud("");
}

void probarMiStrcpy() {
    char cad1[30];
    char cad2[30];
    imprimirTitulo("mi_strcpy: copiar una cadena");

    mi_strcpy(cad1, "Juana");   // reemplazo de cad1 = "Juana", que no compila
    mi_strcpy(cad2, cad1);

    // if (mi_strcmp(cad1, cad2) == 0) {
    //     cout << "Son iguales" << endl;
    // }

    cout << left << setw(8) << "cad1:" << cad1 << endl;
    cout << left << setw(8) << "cad2:" << cad2 << endl;
}

void probarMiStrcmp() {
    imprimirTitulo("mi_strcmp: comparar dos cadenas");
    imprimirComparacion("Hola", "Hola");
    imprimirComparacion("Juana", "Juan");
    imprimirComparacion("Ana", "Beto");
    imprimirComparacion("ana", "Beto");   // orden ASCII, no alfabetico
}

void probarMiStrcat() {
    char nombre[20] = "Juana";
    imprimirTitulo("mi_strcat: concatenar cadenas");

    cout << left << setw(10) << "Antes:" << nombre << endl;
    mi_strcat(nombre, " Perez");
    cout << left << setw(10) << "Despues:" << nombre << endl;
    cout << "Nueva longitud: " << mi_strlen(nombre) << endl;
}

void probarPasaAMayusculas() {
    char cadena[30] = "Rosa maria 12";
    imprimirTitulo("pasaAMayusculas: conversion con aritmetica ASCII");

    cout << left << setw(10) << "Antes:" << cadena << endl;
    pasaAMayusculas(cadena);
    cout << left << setw(10) << "Despues:" << cadena << endl;
    cout << "Distancia 'a' - 'A' = " << 'a' - 'A' << endl;
}

void probarInvertirCadena() {
    char cadena1[30] = "ABCDEFG";
    char cadena2[30] = "Hola amigos";
    imprimirTitulo("invertirCadena: recorrido con dos indices");

    invertirCadena(cadena1);
    invertirCadena(cadena2);

    cout << left << setw(15) << "ABCDEFG" << cadena1 << endl;
    cout << left << setw(15) << "Hola amigos" << cadena2 << endl;
}

// ============================================================
// Funciones de impresion
// ============================================================

void imprimirTitulo(const char* titulo) {
    cout << endl;
    cout << titulo << endl;
    imprimirLinea('=', mi_strlen(titulo));
}

void imprimirLinea(char c, int n) {
    for (int i = 0; i < n; i++) {
        cout << c;
    }
    cout << endl;
}

void imprimirCelda(int indice, char c) {
    cout << left << setw(10) << indice;
    if (c == '\0') {
        cout << setw(10) << "\\0";
    } else {
        cout << setw(10) << c;
    }
    cout << right << setw(6) << (int)c << endl;
}

void imprimirLongitud(const char* cadena) {
    cout << left << setw(20) << cadena
         << right << setw(4) << mi_strlen(cadena) << endl;
}

void imprimirComparacion(const char* cad1, const char* cad2) {
    int cmp = mi_strcmp(cad1, cad2);   // se guarda para no llamar tres veces
    cout << left << setw(8) << cad1;
    if (cmp == 0) {
        cout << setw(18) << "es igual a";
    } else if (cmp > 0) {
        cout << setw(18) << "es mayor que";
    } else {
        cout << setw(18) << "es menor que";
    }
    cout << setw(8) << cad2 << "(" << cmp << ")" << endl;
}
