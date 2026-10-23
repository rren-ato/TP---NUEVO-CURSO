//
// Created by Eric Huiza on 10/22/26.
//

#include "FuncionesAuxiliares.h"

// ============================================================
// Funciones de manejo de cadenas
// ============================================================

int mi_strlen(const char* cadena) {
    int nCar;
    for (nCar = 0; cadena[nCar]; nCar++);   // el ciclo no tiene cuerpo
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

void mi_strcat(char* cadena1, const char* cadena2) {
    int pos = mi_strlen(cadena1);   // posicion del '\0'
    mi_strcpy(&cadena1[pos], cadena2);
}

bool corresponde(const char* cad1, const char* cad2) {
    for (int i = 0; cad2[i]; i++) {
        if (cad1[i] != cad2[i]) {
            return false;
        }
    }
    return true;
}

char* mi_strstr(char* cad1, const char* cad2) {
    for (int i = 0; cad1[i]; i++) {
        if (cad1[i] == cad2[0]) {
            if (corresponde(&cad1[i], cad2)) {
                return &cad1[i];   // direccion, no indice
            }
        }
    }
    return nullptr;
}

void reemplazar(char* texto, const char* cadBus, const char* cadReem) {
    char aux[500];
    char* pt;
    pt = mi_strstr(texto, cadBus);   // 1. ubicar
    if (pt == nullptr) {
        return;
    }
    *pt = 0;                                   // 2. cortar
    mi_strcpy(aux, texto);                     // 3. parte izquierda
    mi_strcat(aux, cadReem);                   // 4. reemplazo
    mi_strcat(aux, &pt[mi_strlen(cadBus)]);    // 5. parte derecha
    mi_strcpy(texto, aux);                     // 6. devolver
}

// ============================================================
// Funciones de conversion de texto a numero
// ============================================================

bool esEspacio(char c) {
    return c == ' ' or c == '\t' or c == '\n';
}

bool esDigito(char c) {
    return c >= '0' and c <= '9';
}

int mi_atoi(const char* cadena) {
    int valor = 0;
    int i = 0;
    int digito;
    while (esEspacio(cadena[i])) {
        i++;
    }
    while (esDigito(cadena[i])) {
        digito = cadena[i] - '0';   // '3' - '0' = 51 - 48 = 3
        valor = valor * 10 + digito;
        i++;
    }
    return valor;
}

double mi_atof(const char* cadena) {
    double valor = 0;
    double factor = 0.1;
    int i = 0;
    int digito;
    while (esEspacio(cadena[i])) {
        i++;
    }
    while (esDigito(cadena[i])) {   // parte entera
        digito = cadena[i] - '0';
        valor = valor * 10 + digito;
        i++;
    }
    if (cadena[i] == '.') {   // parte decimal
        i++;
        while (esDigito(cadena[i])) {
            digito = cadena[i] - '0';
            valor += digito * factor;
            factor *= 0.1;
            i++;
        }
    }
    return valor;
}

// ============================================================
// Funciones de prueba: lectura con >> y formato de salida
// ============================================================

void probarLecturaPorPalabras(const char* nombreArchivo) {
    ifstream archivo;
    abrirArchivoDeLectura(nombreArchivo, archivo);
    imprimirTitulo(">> lee una sola palabra");

    char palabra[50];
    int numPalabra = 0;
    while (archivo >> palabra) {   // descarta espacios y se detiene en el siguiente
        numPalabra++;
        cout << "Palabra" << setw(3) << numPalabra << ": " << palabra << endl;
    }
}

void probarLecturaDeCampos(const char* nombreArchivo) {
    ifstream archivo;
    abrirArchivoDeLectura(nombreArchivo, archivo);
    imprimirTitulo("Lectura de datos de distinto tipo y salida con setw");

    int codigo;
    char apellidoPat[50];
    double cuota;
    char especialidad[60];
    cout.precision(2);
    cout << fixed;
    cout << left << setw(12) << "CODIGO" << setw(15) << "APELLIDO"
         << setw(15) << "ESPECIALIDAD" << right << setw(10) << "CUOTA" << endl;
    while (archivo >> codigo) {
        archivo >> apellidoPat >> cuota >> especialidad;
        cout << left << setw(12) << codigo << setw(15) << apellidoPat
             << setw(15) << especialidad << right << setw(10) << cuota << endl;
    }
}

// ============================================================
// Funciones de prueba: lectura con getline y get
// ============================================================

void probarGetline(const char* nombreArchivo) {
    ifstream archivo;
    abrirArchivoDeLectura(nombreArchivo, archivo);
    imprimirTitulo("getline consume el delimitador");

    char cadena1[50];
    char cadena2[50];
    archivo.getline(cadena1, 50);   // hasta '\n'
    cout << "Cadena leida: " << cadena1 << endl;
    archivo.getline(cadena1, 50, '/');   // hasta '/'
    cout << "Cadena leida: " << cadena1 << endl;
    archivo.getline(cadena2, 50);   // resto de la linea
    cout << "Cadena restante: " << cadena2 << endl;
}

void probarGet(const char* nombreArchivo) {
    ifstream archivo;
    abrirArchivoDeLectura(nombreArchivo, archivo);
    imprimirTitulo("get deja el delimitador en el buffer");

    char cadena1[50];
    char cadena2[50];
    archivo.get(cadena1, 50);   // hasta '\n', que queda en el buffer
    cout << "Cadena leida: " << cadena1 << endl;
    archivo.get();   // saca el '\n'
    archivo.get(cadena1, 50, '/');   // hasta '/', que queda en el buffer
    cout << "Cadena leida: " << cadena1 << endl;
    archivo.get(cadena2, 50);   // empieza con el '/' que no se extrajo
    cout << "Cadena restante: " << cadena2 << endl;
}

void probarGetlineConArregloPequenio(const char* nombreArchivo) {
    ifstream archivo;
    abrirArchivoDeLectura(nombreArchivo, archivo);
    imprimirTitulo("Arreglo pequenio: getline activa failbit");

    char cadena1[10];
    char cadena2[50];
    archivo.getline(cadena1, 10);   // copia 9 caracteres y el '\0'
    imprimirEstadoFailbit(archivo);
    archivo.clear();   // obligatorio
    archivo.getline(cadena2, 50);
    cout << "cadena1 = " << cadena1 << endl;
    cout << "cadena2 = " << cadena2 << endl;
}

void probarGetConArregloPequenio(const char* nombreArchivo) {
    ifstream archivo;
    abrirArchivoDeLectura(nombreArchivo, archivo);
    imprimirTitulo("Arreglo pequenio: get no activa failbit");

    char cadena1[10];
    char cadena2[50];
    archivo.get(cadena1, 10);   // copia 9 caracteres y el '\0'
    imprimirEstadoFailbit(archivo);
    archivo.getline(cadena2, 50);   // no requiere clear()
    cout << "cadena1 = " << cadena1 << endl;
    cout << "cadena2 = " << cadena2 << endl;
}

// ============================================================
// Funciones de prueba: limpieza del buffer de entrada
// ============================================================

void probarLecturaMixtaSinLimpiar(const char* nombreArchivo) {
    ifstream archivo;
    abrirArchivoDeLectura(nombreArchivo, archivo);
    imprimirTitulo("Lectura mixta sin limpiar el buffer");

    int numero;
    char cadena[200];
    archivo >> numero;   // lee el numero y deja el '\n'
    archivo.getline(cadena, 200);   // encuentra el '\n' y termina: cadena vacia
    imprimirNumeroYCadena(numero, cadena);
}

void probarLecturaMixtaLimpiando(const char* nombreArchivo) {
    ifstream archivo;
    abrirArchivoDeLectura(nombreArchivo, archivo);
    imprimirTitulo("Lectura mixta limpiando el buffer");

    int numero;
    char cadena[200];
    archivo >> numero;
    while (archivo.get() != '\n');   // vacia el buffer hasta '\n'
    archivo.getline(cadena, 200);
    imprimirNumeroYCadena(numero, cadena);
}

// ============================================================
// Funciones de prueba: busqueda y reemplazo
// ============================================================

void probarMiStrstr() {
    char texto[] = "La mamadera del bebe";
    imprimirTitulo("mi_strstr: localizar una subcadena");
    cout << "Texto: " << texto << endl;

    imprimirBusqueda(texto, "madera");
    imprimirBusqueda(texto, "bebe");
    imprimirBusqueda(texto, "perro");
}

void probarReemplazar() {
    char texto[100] = "El perro come carne";
    imprimirTitulo("reemplazar: buscar y sustituir una subcadena");

    cout << left << setw(10) << "Antes:" << texto << endl;
    reemplazar(texto, "perro", "gato gordo");
    cout << left << setw(10) << "Despues:" << texto << endl;
    reemplazar(texto, "pez", "pollo");   // no la encuentra: no cambia
    cout << left << setw(10) << "Sin pez:" << texto << endl;
}

// ============================================================
// Funciones de prueba: conversion de texto a numero
// ============================================================

void probarMiAtoi(const char* nombreArchivo) {
    ifstream archivo;
    abrirArchivoDeLectura(nombreArchivo, archivo);
    imprimirTitulo("mi_atoi: de texto a entero");

    char linea[50];
    int suma = 0;
    while (archivo.getline(linea, 50)) {   // cada linea se lee como texto
        int valor = mi_atoi(linea);
        suma += valor;
        cout << left << setw(10) << linea << right << setw(10) << valor << endl;
    }
    cout << left << setw(10) << "Suma" << right << setw(10) << suma << endl;
    cout << "571 + mi_atoi(\"2387\") = " << 571 + mi_atoi("2387") << endl;
}

void probarMiAtof(const char* nombreArchivo) {
    ifstream archivo;
    abrirArchivoDeLectura(nombreArchivo, archivo);
    imprimirTitulo("mi_atof: de texto a real");

    char linea[50];
    double suma = 0;
    cout.precision(2);
    cout << fixed;
    while (archivo.getline(linea, 50)) {
        double valor = mi_atof(linea);
        suma += valor;
        cout << left << setw(10) << linea << right << setw(10) << valor << endl;
    }
    cout << left << setw(10) << "Suma" << right << setw(10) << suma << endl;
}

// ============================================================
// Funciones de apertura e impresion
// ============================================================

void abrirArchivoDeLectura(const char* nombreArchivo, ifstream& archivo) {
    archivo.open(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        exit(1);
    }
}

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

void imprimirEstadoFailbit(ifstream& archivo) {
    cout << "failbit: ";
    if (archivo.fail()) {
        cout << "activado" << endl;
    } else {
        cout << "no activado" << endl;
    }
}

void imprimirNumeroYCadena(int numero, const char* cadena) {
    cout << left << setw(10) << "Numero ="
         << right << setw(8) << numero << endl;
    cout << left << setw(10) << "Cadena =" << cadena << endl;
}

void imprimirBusqueda(char* texto, const char* buscada) {
    char* ptr = mi_strstr(texto, buscada);
    cout << left << setw(10) << buscada;
    if (ptr == nullptr) {
        cout << "no se encontro (nullptr)" << endl;
    } else {
        cout << "indice " << setw(4) << ptr - texto << "-> " << ptr << endl;
    }
}
