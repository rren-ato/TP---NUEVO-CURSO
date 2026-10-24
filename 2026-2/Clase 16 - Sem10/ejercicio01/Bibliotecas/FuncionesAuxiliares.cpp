//
// Created by Eric Huiza on 10/24/26.
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
// Funciones de conversion y clasificacion
// ============================================================

bool esEspacio(char c) {
    return c == ' ' or c == '\t' or c == '\n';
}

bool esDigito(char c) {
    return c >= '0' and c <= '9';
}

bool esMayuscula(char c) {
    return c >= 'A' and c <= 'Z';
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

bool sonDigitos(const char* cadena, int inicio, int cantidad) {
    for (int i = inicio; i < inicio + cantidad; i++) {
        if (!esDigito(cadena[i])) {
            return false;
        }
    }
    return true;
}

bool sonMayusculas(const char* cadena, int inicio, int cantidad) {
    for (int i = inicio; i < inicio + cantidad; i++) {
        if (!esMayuscula(cadena[i])) {
            return false;
        }
    }
    return true;
}

// ============================================================
// Funciones de calendario
// ============================================================

bool esBisiesto(int anio) {
    return (anio % 4 == 0 and anio % 100 != 0) or anio % 400 == 0;
}

int diasDelMes(int mes, int anio) {
    if (mes == 2) {
        if (esBisiesto(anio)) {
            return 29;
        }
        return 28;
    }
    if (mes == 4 or mes == 6 or mes == 9 or mes == 11) {
        return 30;
    }
    return 31;
}

// ============================================================
// Funciones de lectura y validacion
// ============================================================

void validarYReportar(const char* nombArchDatos, const char* nombArchReporte,
    int* validos, int* invalidos, int& numReg) {

    ifstream archDatos;
    ofstream archReporte;
    abrirArchivoDeLectura(nombArchDatos, archDatos);
    abrirArchivoDeEscritura(nombArchReporte, archReporte);

    char valor[TAM_VALOR];
    char tipo[TAM_TIPO];
    int motivo;
    numReg = 0;
    imprimirEncabezado(archReporte);
    while (leerRegistro(archDatos, valor, tipo)) {   // se valida y reporta fila por fila
        numReg++;
        motivo = validarRegistro(valor, tipo);
        imprimirRegistro(archReporte, numReg, valor, tipo, motivo);
        acumularResultado(validos, invalidos, tipo, motivo);
    }
}

bool leerRegistro(ifstream& arch, char* valor, char* tipo) {
    arch.getline(valor, TAM_VALOR, ',');   // el valor llega hasta la coma
    if (arch.eof()) {
        return false;   // ya no hay mas filas
    }
    arch.getline(tipo, TAM_TIPO);   // el tipo llega hasta el fin de linea
    pasaAMayusculas(tipo);   // "dni", "Dni" y "DNI" son el mismo tipo
    return true;
}

int validarRegistro(const char* valor, const char* tipo) {
    if (mi_strcmp(tipo, "DNI") == 0) {
        return validarDni(valor);
    }
    if (mi_strcmp(tipo, "PLACA") == 0) {
        return validarPlaca(valor);
    }
    if (mi_strcmp(tipo, "FECHA") == 0) {
        return validarFecha(valor);
    }
    return MOTIVO_TIPO;
}

int validarDni(const char* dni) {
    if (mi_strlen(dni) != 8) {
        return MOTIVO_LONGITUD;
    }
    if (!sonDigitos(dni, 0, 8)) {
        return MOTIVO_NO_NUMERICO;
    }
    return MOTIVO_OK;
}

int validarPlaca(const char* placa) {
    if (mi_strlen(placa) != 7) {
        return MOTIVO_LONGITUD;
    }
    if (!sonMayusculas(placa, 0, 3) or placa[3] != '-' or
        !sonDigitos(placa, 4, 3)) {

        return MOTIVO_FORMATO_PLACA;   // formato XYZ-123
    }
    return MOTIVO_OK;
}

int validarFecha(const char* fecha) {
    int dia;
    int mes;
    int anio;
    if (mi_strlen(fecha) != 10) {
        return MOTIVO_LONGITUD;
    }
    if (!tieneFormatoDeFecha(fecha)) {
        return MOTIVO_FORMATO_FECHA;
    }
    dia = mi_atoi(&fecha[0]);   // mi_atoi se detiene en el '-'
    mes = mi_atoi(&fecha[3]);
    anio = mi_atoi(&fecha[6]);
    if (mes < 1 or mes > 12) {
        return MOTIVO_MES;
    }
    if (dia < 1 or dia > diasDelMes(mes, anio)) {
        return MOTIVO_DIA;
    }
    return MOTIVO_OK;
}

bool tieneFormatoDeFecha(const char* fecha) {
    bool diaOk = sonDigitos(fecha, 0, 2) and fecha[2] == '-';
    bool mesOk = sonDigitos(fecha, 3, 2) and fecha[5] == '-';
    bool anioOk = sonDigitos(fecha, 6, 4);
    return diaOk and mesOk and anioOk;   // formato dd-mm-aaaa
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

void imprimirEncabezado(ofstream& arch) {
    imprimirTitulo(arch, "REPORTE DE VALIDACION DE REGISTROS");
    arch << left << setw(5) << "NRO" << setw(15) << "VALOR" << setw(10) << "TIPO"
         << setw(11) << "ESTADO" << "MOTIVO" << endl;
}

void imprimirRegistro(ofstream& arch, int nro, const char* valor, const char* tipo, int codigo) {
    char motivo[TAM_MOTIVO];
    obtenerMotivo(codigo, motivo);
    arch << left << setw(5) << nro << setw(15) << valor << setw(10) << tipo;
    if (codigo == MOTIVO_OK) {
        arch << setw(11) << "VALIDO";
    } else {
        arch << setw(11) << "INVALIDO";
    }
    arch << motivo << endl;
}

void imprimirResumen(const char* nombArch, int* validos, int* invalidos, int numReg) {
    ofstream arch;
    abrirArchivoDeEscritura(nombArch, arch);

    char nombre[TAM_TIPO];
    imprimirTitulo(arch, "RESUMEN POR TIPO");
    arch << left << setw(10) << "TIPO" << right << setw(10) << "VALIDOS"
         << setw(12) << "INVALIDOS" << setw(8) << "TOTAL" << endl;
    for (int i = 0; i < NUM_TIPOS; i++) {
        obtenerNombreTipo(i, nombre);
        arch << left << setw(10) << nombre << right << setw(10) << validos[i]
             << setw(12) << invalidos[i] << setw(8) << validos[i] + invalidos[i] << endl;
    }
    imprimirLinea(arch, '-', 40);
    arch << left << setw(32) << "Registros procesados:" << right << setw(8) << numReg << endl;
}

void acumularResultado(int* validos, int* invalidos, const char* tipo, int motivo) {
    int indice = obtenerIndiceTipo(tipo);
    if (motivo == MOTIVO_OK) {
        validos[indice]++;
    } else {
        invalidos[indice]++;
    }
}

int obtenerIndiceTipo(const char* tipo) {
    if (mi_strcmp(tipo, "DNI") == 0) {
        return TIPO_DNI;
    }
    if (mi_strcmp(tipo, "PLACA") == 0) {
        return TIPO_PLACA;
    }
    if (mi_strcmp(tipo, "FECHA") == 0) {
        return TIPO_FECHA;
    }
    return TIPO_DESCONOCIDO;
}

void obtenerNombreTipo(int indice, char* nombre) {
    if (indice == TIPO_DNI) {
        mi_strcpy(nombre, "DNI");
    } else if (indice == TIPO_PLACA) {
        mi_strcpy(nombre, "PLACA");
    } else if (indice == TIPO_FECHA) {
        mi_strcpy(nombre, "FECHA");
    } else {
        mi_strcpy(nombre, "OTRO");
    }
}

void obtenerMotivo(int codigo, char* motivo) {
    if (codigo == MOTIVO_OK) {
        mi_strcpy(motivo, "-");
    } else if (codigo == MOTIVO_LONGITUD) {
        mi_strcpy(motivo, "Longitud incorrecta");
    } else if (codigo == MOTIVO_NO_NUMERICO) {
        mi_strcpy(motivo, "Contiene caracteres no numericos");
    } else if (codigo == MOTIVO_FORMATO_PLACA) {
        mi_strcpy(motivo, "No cumple el formato XYZ-123");
    } else if (codigo == MOTIVO_FORMATO_FECHA) {
        mi_strcpy(motivo, "No cumple el formato dd-mm-aaaa");
    } else if (codigo == MOTIVO_MES) {
        mi_strcpy(motivo, "Mes fuera de rango (01-12)");
    } else if (codigo == MOTIVO_DIA) {
        mi_strcpy(motivo, "El dia no existe en ese mes");
    } else {
        mi_strcpy(motivo, "Tipo de dato desconocido");
    }
}

void imprimirTitulo(ofstream& arch, const char* titulo) {
    arch << titulo << endl;
    imprimirLinea(arch, '=', mi_strlen(titulo));
}

void imprimirLinea(ofstream& arch, char c, int n) {
    for (int i = 0; i < n; i++) {
        arch << c;
    }
    arch << endl;
}
