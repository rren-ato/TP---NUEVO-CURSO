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

void reemplazarEnTexto(char* texto, const char* cadBus, const char* cadReem) {
    char aux[MAX_TEXTO];   // reemplazar de la sesion 15 usa aux[500]: no alcanza
    char* pt;
    pt = mi_strstr(texto, cadBus);             // 1. ubicar
    if (pt == nullptr) {
        return;
    }
    *pt = 0;                                   // 2. cortar
    mi_strcpy(aux, texto);                     // 3. parte izquierda
    mi_strcat(aux, cadReem);                   // 4. reemplazo
    mi_strcat(aux, &pt[mi_strlen(cadBus)]);    // 5. parte derecha
    mi_strcpy(texto, aux);                     // 6. devolver
}

int reemplazarTodas(char* texto, const char* cadBus,
    const char* cadReem) {

    int cantidad = 0;
    char* pt = mi_strstr(texto, cadBus);
    while (pt != nullptr) {
        reemplazarEnTexto(pt, cadBus, cadReem);   // pt ya apunta a la coincidencia
        pt = mi_strstr(&pt[mi_strlen(cadReem)], cadBus);   // sigue despues del reemplazo
        cantidad++;
    }
    return cantidad;
}

void pasaAMinusculas(char* cadena) {
    for (int i = 0; cadena[i]; i++) {
        if (cadena[i] >= 'A' and cadena[i] <= 'Z') {
            cadena[i] += 'a' - 'A';   // suma 32
        }
    }
}

bool extraerCadena(char*& cursor, const char* delimitador, char* cadena) {
    char* pt;
    char guardado;
    cadena[0] = 0;
    if (*cursor == 0) {
        return false;   // ya no quedan datos
    }
    pt = mi_strstr(cursor, delimitador);
    if (pt == nullptr) {
        mi_strcpy(cadena, cursor);   // ultimo tramo, sin delimitador
        cursor = &cursor[mi_strlen(cursor)];
        return true;
    }
    guardado = *pt;   // 1. guarda el primer caracter del delimitador
    *pt = 0;          // 2. corta la cadena ahi
    mi_strcpy(cadena, cursor);   // 3. copia el tramo
    *pt = guardado;   // 4. restaura: la cadena original queda intacta
    cursor = &pt[mi_strlen(delimitador)];   // salta el delimitador
    return true;
}

// ============================================================
// Funciones de clasificacion de caracteres
// ============================================================

bool esMinuscula(char c) {
    return c >= 'a' and c <= 'z';
}

bool esDigito(char c) {
    return c >= '0' and c <= '9';
}

bool esCaracterValido(char c) {
    return esMinuscula(c) or esDigito(c) or c == ' ' or c == '\n';
}

bool esLimite(char c) {
    return c == ' ' or c == '\n' or c == 0;
}

// ============================================================
// Funciones de carga
// ============================================================

void cargarArchivo(const char* nombArch, char* contenido) {
    ifstream arch;
    abrirArchivoDeLectura(nombArch, arch);

    char linea[MAX_LINEA];
    contenido[0] = 0;   // empieza como cadena vacia
    while (arch.getline(linea, MAX_LINEA)) {
        mi_strcat(contenido, linea);
        mi_strcat(contenido, "\n");   // getline descarta el '\n': se repone
    }
}

void cargarStopWords(const char* nombArch, char* stopWords) {
    ifstream arch;
    abrirArchivoDeLectura(nombArch, arch);

    char palabra[TAM_PALABRA];
    mi_strcpy(stopWords, " ");   // la lista empieza con un espacio
    while (arch >> palabra) {
        mi_strcat(stopWords, palabra);
        mi_strcat(stopWords, " ");   // cada palabra queda entre espacios
    }
}

// ============================================================
// Funciones de normalizacion
// ============================================================

void normalizarTexto(char* texto, char* equivalencias, char* stopWords, int& caracteresAntes,
    int& numEquivalencias, int& numSignos, int& numStopWords) {

    caracteresAntes = mi_strlen(texto);
    numEquivalencias = aplicarEquivalencias(texto, equivalencias);   // 1. antes de quitar signos
    pasaAMinusculas(texto);                                          // 2. todo en minuscula
    numSignos = removerSignos(texto);                                // 3. solo a-z, digitos y espacios
    numStopWords = removerStopWords(texto, stopWords);               // 4. palabras vacias
}

int aplicarEquivalencias(char* texto, char* equivalencias) {
    char equivalencia[MAX_LINEA];
    char* cursor = equivalencias;
    int cantidad = 0;
    while (extraerCadena(cursor, "\n", equivalencia)) {
        cantidad += aplicarEquivalencia(texto, equivalencia);
    }
    return cantidad;
}

int aplicarEquivalencia(char* texto, char* equivalencia) {
    char buscada[TAM_PALABRA];
    char reemplazo[TAM_PALABRA];
    char* cursor = equivalencia;
    extraerCadena(cursor, "|", buscada);   // linea con formato buscada|reemplazo
    extraerCadena(cursor, "|", reemplazo);
    return reemplazarTodas(texto, buscada, reemplazo);
}

int removerSignos(char* texto) {
    int cantidad = 0;
    for (int i = 0; texto[i]; i++) {
        if (!esCaracterValido(texto[i])) {
            texto[i] = ' ';
            cantidad++;
        }
    }
    return cantidad;
}

int removerStopWords(char* texto, char* stopWords) {
    char resultado[MAX_TEXTO];   // el texto limpio se arma aparte
    char linea[MAX_LINEA];
    char* cursor = texto;
    int cantidad = 0;
    resultado[0] = 0;
    while (extraerCadena(cursor, "\n", linea)) {
        cantidad += filtrarLinea(linea, stopWords, resultado);
        mi_strcat(resultado, "\n");   // se conservan los saltos de linea
    }
    mi_strcpy(texto, resultado);
    return cantidad;
}

int filtrarLinea(char* linea, char* stopWords, char* resultado) {
    char palabra[TAM_PALABRA];
    char* cursor = linea;
    int cantidad = 0;
    while (extraerCadena(cursor, " ", palabra)) {
        if (esStopWord(palabra, stopWords)) {
            cantidad++;
        } else if (palabra[0] != 0) {   // los espacios repetidos dan palabras vacias
            agregarPalabra(resultado, palabra);
        }
    }
    return cantidad;
}

bool esStopWord(const char* palabra, char* stopWords) {
    char patron[TAM_PALABRA];
    mi_strcpy(patron, " ");   // " de " no se confunde con "desde"
    mi_strcat(patron, palabra);
    mi_strcat(patron, " ");
    return mi_strstr(stopWords, patron) != nullptr;
}

void agregarPalabra(char* resultado, const char* palabra) {
    int lon = mi_strlen(resultado);
    if (lon > 0 and resultado[lon - 1] != '\n') {
        mi_strcat(resultado, " ");   // separa de la palabra anterior
    }
    mi_strcat(resultado, palabra);
}

// ============================================================
// Funciones de busqueda de terminos
// ============================================================

int contarTerminos(char* texto, char* terminos, int* frecuencias) {
    char termino[TAM_PALABRA];
    char* cursor = terminos;
    int numTerminos = 0;
    while (extraerCadena(cursor, "\n", termino)) {
        frecuencias[numTerminos] = contarApariciones(texto, termino);
        numTerminos++;
    }
    return numTerminos;
}

int contarApariciones(char* texto, const char* termino) {
    int cantidad = 0;
    int lon = mi_strlen(termino);
    char* pt = mi_strstr(texto, termino);
    while (pt != nullptr) {
        if (esPalabraCompleta(texto, pt, lon)) {   // "jedi" no cuenta dentro de "jedis"
            cantidad++;
        }
        pt = mi_strstr(&pt[1], termino);   // sigue buscando desde el siguiente caracter
    }
    return cantidad;
}

bool esPalabraCompleta(char* texto, char* pt, int lon) {
    bool inicioValido = pt == texto or esLimite(*(pt - 1));   // caracter anterior
    bool finValido = esLimite(pt[lon]);   // caracter siguiente
    return inicioValido and finValido;
}

int contarLineas(char* texto) {
    int numLineas = 0;
    char* pt = mi_strstr(texto, "\n");
    while (pt != nullptr) {
        numLineas++;
        pt = mi_strstr(&pt[1], "\n");
    }
    return numLineas;
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

void escribirTexto(const char* nombArch, const char* texto) {
    ofstream arch;
    abrirArchivoDeEscritura(nombArch, arch);
    arch << texto;   // el texto ya contiene sus '\n'
}

void imprimirReporte(const char* nombArch, char* texto, char* terminos, int* frecuencias,
    int caracteresAntes, int numEquivalencias, int numSignos, int numStopWords) {

    ofstream arch;
    abrirArchivoDeEscritura(nombArch, arch);

    imprimirTitulo(arch, "REPORTE DE NORMALIZACION: EL RETORNO DEL JEDI");
    imprimirDato(arch, "Lineas procesadas:", contarLineas(texto));
    imprimirDato(arch, "Caracteres originales:", caracteresAntes);
    imprimirDato(arch, "Equivalencias aplicadas:", numEquivalencias);
    imprimirDato(arch, "Caracteres extranos removidos:", numSignos);
    imprimirDato(arch, "Stop words removidas:", numStopWords);
    imprimirDato(arch, "Caracteres finales:", mi_strlen(texto));
    imprimirFrecuencias(arch, terminos, frecuencias);
}

void imprimirFrecuencias(ofstream& arch, char* terminos, int* frecuencias) {
    char termino[TAM_PALABRA];
    char* cursor = terminos;   // la lista de terminos ya esta en memoria
    int i = 0;
    arch << endl;
    imprimirTitulo(arch, "FRECUENCIA DE TERMINOS");
    arch << left << setw(5) << "NRO" << setw(20) << "TERMINO"
         << right << setw(12) << "FRECUENCIA" << endl;
    while (extraerCadena(cursor, "\n", termino)) {
        arch << left << setw(5) << i + 1 << setw(20) << termino
             << right << setw(12) << frecuencias[i] << endl;
        i++;
    }
}

void imprimirDato(ofstream& arch, const char* etiqueta, int valor) {
    arch << left << setw(35) << etiqueta << right << setw(8) << valor << endl;
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
