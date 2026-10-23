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

void pasaAMayusculas(char* cadena) {
    for (int i = 0; cadena[i]; i++) {
        if (cadena[i] >= 'a' and cadena[i] <= 'z') {
            cadena[i] -= 'a' - 'A';   // resta 32
        }
    }
}

// ============================================================
// Funciones de memoria dinamica
// ============================================================

char* leeCadenaExacta(ifstream& arch) {
    char buff[500];
    char* cad;
    arch.getline(buff, 500);   // 1. leer en un buffer grande
    if (arch.eof()) {
        return nullptr;
    }
    cad = new char[mi_strlen(buff) + 1];   // 2. reservar la medida exacta (+1: '\0')
    mi_strcpy(cad, buff);   // 3. copiar y devolver
    return cad;
}

int contarLineas(const char* nombreArchivo) {
    ifstream archivo;
    abrirArchivoDeLectura(nombreArchivo, archivo);

    char buff[500];
    int numLineas = 0;
    while (archivo.getline(buff, 500)) {
        numLineas++;
    }
    return numLineas;
}

// ============================================================
// Funciones del arreglo de cadenas (ejercicio integrador 1)
// ============================================================

void leeNombres(char** persona, int& numPer, const char* nombArch) {
    ifstream arch;
    abrirArchivoDeLectura(nombArch, arch);

    char* nombre;
    numPer = 0;
    while (true) {
        nombre = leeCadenaExacta(arch);
        if (nombre == nullptr) {
            break;
        }
        persona[numPer] = nombre;   // se guarda la direccion
        numPer++;
    }
}

void pasaAMayusculasTodo(char** persona, int numPer) {
    for (int i = 0; i < numPer; i++) {
        pasaAMayusculas(persona[i]);
    }
}

void ordenaNombres(char** persona, int numPer) {
    for (int i = 0; i < numPer - 1; i++) {
        for (int k = i + 1; k < numPer; k++) {
            if (mi_strcmp(persona[i], persona[k]) > 0) {
                cambiar(persona[i], persona[k]);
            }
        }
    }
}

void cambiar(char*& nombreI, char*& nombreK) {
    char* aux = nombreI;   // solo se intercambian direcciones
    nombreI = nombreK;
    nombreK = aux;
}

void imprimeNombres(char** persona, int numPer, const char* nombArch) {
    ofstream arch;
    abrirArchivoDeEscritura(nombArch, arch);

    arch << left << setw(5) << "NRO" << "NOMBRE" << endl;
    for (int i = 0; i < numPer; i++) {
        arch << left << setw(5) << i + 1 << persona[i] << endl;
    }
}

void liberaNombres(char** persona, int numPer) {
    for (int i = 0; i < numPer; i++) {
        delete[] persona[i];   // un delete[] por cada cadena leida
    }
}

// ============================================================
// Funciones del archivo CSV (ejercicio integrador 2)
// ============================================================

void leeDatosDelArchivo(int* dni, char** empleado, double* sueldo,
    int& numEmp, const char* nombArch) {

    ifstream arch;
    abrirArchivoDeLectura(nombArch, arch);

    int dniArch;
    char* empleadoArch;
    double sueldoArch;
    numEmp = 0;
    while (true) {
        leerLinea(arch, dniArch, empleadoArch, sueldoArch);
        if (arch.eof()) {
            break;
        }
        dni[numEmp] = dniArch;   // los tres datos van en la misma posicion
        empleado[numEmp] = empleadoArch;
        sueldo[numEmp] = sueldoArch;
        numEmp++;
    }
}

void leerLinea(ifstream& arch, int& dni, char*& empleado, double& sueldo) {
    char nombre[100];
    arch >> dni;   // se detiene en la coma
    if (arch.eof()) {
        return;
    }
    arch.get();   // extrae la coma
    arch.getline(nombre, 100, ',');   // nombre hasta la coma
    empleado = new char[mi_strlen(nombre) + 1];
    mi_strcpy(empleado, nombre);
    arch >> sueldo;
}

void ordenarEmpleados(int* dni, char** empleado, double* sueldo, int numEmp) {
    for (int i = 0; i < numEmp - 1; i++) {
        for (int k = i + 1; k < numEmp; k++) {
            if (sueldo[i] < sueldo[k]) {
                cambiarDni(dni[i], dni[k]);
                cambiar(empleado[i], empleado[k]);
                cambiarSueldo(sueldo[i], sueldo[k]);
            }
        }
    }
}

void cambiarDni(int& dniI, int& dniK) {
    int aux = dniI;
    dniI = dniK;
    dniK = aux;
}

void cambiarSueldo(double& sI, double& sK) {
    double aux = sI;
    sI = sK;
    sK = aux;
}

void imprimirEmpleados(int* dni, char** empleado, double* sueldo,
    int numEmp, const char* nombArch) {

    ofstream arch;
    abrirArchivoDeEscritura(nombArch, arch);

    arch.precision(2);
    arch << fixed;
    arch << left << setw(10) << "DNI" << setw(35) << "NOMBRE"
         << right << setw(10) << "SUELDO" << endl;
    for (int i = 0; i < numEmp; i++) {
        arch << left << setw(10) << dni[i] << setw(35) << empleado[i]
             << right << setw(10) << sueldo[i] << endl;
    }
}

// ============================================================
// Funciones de prueba: memoria dinamica y arreglos de cadenas
// ============================================================

void probarPunteroConMemoria() {
    char* cadena;
    imprimirTitulo("Un puntero necesita memoria antes de escribir");

    // mi_strcpy(cadena, "Hola amigos");   // ERROR: cadena no apunta a memoria valida
    cadena = new char[100];
    mi_strcpy(cadena, "Hola amigos");
    cout << "cadena: " << cadena << endl;
    delete[] cadena;   // cada new[] requiere su delete[]
}

void probarArregloDeNombres(const char* nombArchDatos, const char* nombArchReporte) {
    char* persona[CAPACIDAD];   // arreglo estatico de punteros
    int numPer;
    imprimirTitulo("Arreglo de punteros a cadenas: ordenar nombres");

    leeNombres(persona, numPer, nombArchDatos);
    pasaAMayusculasTodo(persona, numPer);
    ordenaNombres(persona, numPer);
    imprimeNombres(persona, numPer, nombArchReporte);
    imprimirNombresEnPantalla(persona, numPer);
    liberaNombres(persona, numPer);   // persona no se libera: no se creo con new
    cout << "Reporte generado en " << nombArchReporte << endl;
}

void probarArregloDinamicoDeNombres(const char* nombArchDatos) {
    int numPer = contarLineas(nombArchDatos);
    char** persona = new char*[numPer];   // arreglo dinamico de punteros
    imprimirTitulo("Arreglo dinamico de cadenas: char**");

    ifstream arch;
    abrirArchivoDeLectura(nombArchDatos, arch);
    for (int i = 0; i < numPer; i++) {
        persona[i] = leeCadenaExacta(arch);
    }
    imprimirNombresEnPantalla(persona, numPer);
    cout << "persona[2][1] = " << persona[2][1] << endl;   // caracter 1 de la cadena 2

    liberaNombres(persona, numPer);   // 1. cadenas
    delete[] persona;   // 2. arreglo
}

void probarArchivoCsv(const char* nombArchDatos, const char* nombArchReporte) {
    int dni[CAPACIDAD];
    char* empleado[CAPACIDAD];
    double sueldo[CAPACIDAD];
    int numEmp;
    imprimirTitulo("Archivo CSV con arreglos paralelos");

    leeDatosDelArchivo(dni, empleado, sueldo, numEmp, nombArchDatos);
    ordenarEmpleados(dni, empleado, sueldo, numEmp);
    imprimirEmpleados(dni, empleado, sueldo, numEmp, nombArchReporte);
    liberaNombres(empleado, numEmp);   // se reutiliza del ejercicio integrador 1
    cout << "Empleados leidos: " << numEmp << endl;
    cout << "Reporte generado en " << nombArchReporte << endl;
}

// ============================================================
// Funciones de prueba: biblioteca <cstring>
// ============================================================

void probarBibliotecaCstring() {
    imprimirTitulo("La biblioteca <cstring>");
    probarCopiaYConcatenacionConCstring();
    probarComparacionConCstring();
    probarBusquedaConCstring();
}

void probarCopiaYConcatenacionConCstring() {
    char nombre[30];
    char prefijo[10];

    strcpy(nombre, "Juana");   // equivale a mi_strcpy
    strcat(nombre, " Perez");   // equivale a mi_strcat
    strncpy(prefijo, "Montes", 3);   // copia como maximo 3 caracteres
    prefijo[3] = '\0';   // strncpy no agrega el '\0' si la fuente es mas larga

    cout << left << setw(30) << "strcpy + strcat:" << nombre << endl;
    cout << left << setw(30) << "strlen:" << strlen(nombre) << endl;
    cout << left << setw(30) << "strncpy(\"Montes\", 3):" << prefijo << endl;
}

void probarComparacionConCstring() {
    int cmp1 = strcmp("Ana", "Beto");
    int cmp2 = strcmp("Hola", "Hola");
    int cmp3 = strncmp("Juana", "Juan", 4);   // compara solo 4 caracteres

    // strcmp solo garantiza el signo: se compara con 0, nunca con 1 o -1
    cout << left << setw(30) << "strcmp(\"Ana\", \"Beto\") < 0:";
    cout << (cmp1 < 0) << endl;
    cout << left << setw(30) << "strcmp(\"Hola\", \"Hola\") == 0:";
    cout << (cmp2 == 0) << endl;
    cout << left << setw(30) << "strncmp(\"Juana\", \"Juan\", 4):";
    cout << cmp3 << endl;
}

void probarBusquedaConCstring() {
    char texto[] = "La mamadera del bebe";
    char* ptrSubcadena = strstr(texto, "madera");   // igual que mi_strstr
    char* ptrCaracter = strchr(texto, 'd');   // primer caracter 'd'

    cout << left << setw(30) << "strstr(texto, \"madera\"):" << ptrSubcadena << endl;
    cout << left << setw(30) << "strchr(texto, 'd'):" << ptrCaracter << endl;
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

void abrirArchivoDeEscritura(const char* nombreArchivo, ofstream& archivo) {
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

void imprimirNombresEnPantalla(char** persona, int numPer) {
    cout << left << setw(5) << "NRO" << setw(25) << "NOMBRE"
         << right << setw(8) << "BYTES" << endl;
    for (int i = 0; i < numPer; i++) {
        cout << left << setw(5) << i + 1 << setw(25) << persona[i]
             << right << setw(8) << mi_strlen(persona[i]) + 1 << endl;
    }
}
