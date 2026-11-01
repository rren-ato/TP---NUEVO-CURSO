#include "FuncionesAuxiliares.h"

using namespace std;

void cargarDatos(char**& dicOtros, int*& arrContOtros, int& tamOtros,
                 char**& dicPalabras, int*& arrContPalabras, int& tamPalabras) {
    cargarDiccionario("ArchivosDeDatos/otros.txt",
        dicOtros, arrContOtros, tamOtros);
    cargarDiccionario("ArchivosDeDatos/palabras.txt",
        dicPalabras, arrContPalabras, tamPalabras);
}

void cargarDiccionario(const char* nombreArchivo, char**& dic, int*& arrCont, int& tamDicc) {
    ifstream arch;
    abrirArchivo(arch, nombreArchivo);

    int cant = cuentaLineasArch(arch);   // 1ra lectura: contar las palabras
    dic = new char*[cant];               // memoria exacta
    arrCont = new int[cant] {};          // arreglo paralelo de apariciones

    arch.clear();                        // volver al inicio del archivo
    arch.seekg(0, ios::beg);
    llenarDiccionario(arch, dic, tamDicc);   // 2da lectura: guardar las palabras
}

void abrirArchivo(ifstream& archNombres, const char* nombreArchivo) {
    archNombres.open(nombreArchivo);
    if (not archNombres.is_open()) {
        cout << "No se pudo abrir " << nombreArchivo << endl;
        exit(1);
    }
}

void abrirArchivo(ofstream& archNombres, const char* nombreArchivo) {
    archNombres.open(nombreArchivo);
    if (not archNombres.is_open()) {
        cout << "No se pudo abrir " << nombreArchivo << endl;
        exit(1);
    }
}

int cuentaLineasArch(ifstream& arch) {
    int n = 0;
    while (arch.ignore(TAM_BUFFER, '\n')) {
        n++;
    }
    return n;
}

void llenarDiccionario(ifstream& arch, char** dic, int& tamDicc) {
    tamDicc = 0;
    char* cad;
    while ((cad = leerCadenaExacta(arch, '\n')) != nullptr) {
        dic[tamDicc++] = cad;
    }
}

char* leerCadenaExacta(ifstream& arch, char sep) {
    char buffer[TAM_BUFFER];
    arch.getline(buffer, TAM_BUFFER, sep);
    if (arch.eof()) {
        return nullptr;
    }
    char* cadena = new char[strlen(buffer) + 1];
    strcpy(cadena, buffer);
    return cadena;
}

void ordenarDiccionarios(char** dicOtros, int tamOtros, char** dicPalabras, int tamPalabras) {
    ofstream reporteOtros, reportePalabra;
    abrirArchivo(reporteOtros, "ArchivosDeReportes/reporteOtros.txt");
    abrirArchivo(reportePalabra, "ArchivosDeReportes/reportePalabra.txt");

    mostrarReporteSimple(dicOtros, tamOtros, reporteOtros, "--- ANTES DE ORDENAR ---");
    mostrarReporteSimple(dicPalabras, tamPalabras, reportePalabra, "--- ANTES DE ORDENAR ---");
    ordenarNombres(dicOtros, tamOtros);         // la busqueda binaria necesita
    ordenarNombres(dicPalabras, tamPalabras);   // los diccionarios ordenados
    mostrarReporteSimple(dicOtros, tamOtros, reporteOtros, "--- DESPUES DE ORDENAR ---");
    mostrarReporteSimple(dicPalabras, tamPalabras, reportePalabra, "--- DESPUES DE ORDENAR ---");
}

void mostrarReporteSimple(char** dic, int tam, ofstream& reporte, const char* titulo) {
    reporte << titulo << endl;
    for (int i = 0; i < tam; i++) {
        reporte << dic[i] << endl;
    }
    reporte << endl;
}

void ordenarNombres(char** listaNombre, int tamano) {
    for (int i = 0; i < tamano - 1; i++) {
        for (int j = i + 1; j < tamano; j++) {
            if (strcmp(listaNombre[i], listaNombre[j]) > 0) {
                intercambiar(listaNombre[i], listaNombre[j]);
            }
        }
    }
}

void intercambiar(char*& a, char*& b) {
    char* aux = a;
    a = b;
    b = aux;
}

void intercambiar(int& a, int& b) {
    int aux = a;
    a = b;
    b = aux;
}

void procesarTexto(int* arrContPalabras, int* arrContOtros,
                   char** dicDesc, int* frecDesc, int& tamDesc,
                   int& contOtros, int& contContenido, int& contDesc,
                   char** dicOtros, int tamOtros, char** dicPalabras, int tamPalabras) {
    ifstream archTexto;
    abrirArchivo(archTexto, "ArchivosDeDatos/texto.txt");

    procesarTokens(archTexto, arrContPalabras, arrContOtros, dicDesc, frecDesc, tamDesc,
                   contOtros, contContenido, contDesc,
                   dicOtros, tamOtros, dicPalabras, tamPalabras);
}

void procesarTokens(ifstream& archTexto, int* arrContPalabras, int* arrContOtros,
                    char** dicDesc, int* frecDesc, int& tamDesc,
                    int& contOtros, int& contContenido, int& contDesc,
                    char** dicOtros, int tamOtros, char** dicPalabras, int tamPalabras) {
    char cadena[TAM_BUFFER];
    tamDesc = 0;
    while (archTexto >> cadena) {   // separa por espacios y saltos de linea
        pasaAMinusculas(cadena);
        int tam = strlen(cadena);
        if (tam > 0 && strchr(".:,!", cadena[tam - 1])) {
            cadena[tam - 1] = '\0';
        }
        if (cadena[0] == '\0') {
            continue;   // token vacio (solo era un signo)
        }
        int posO = busquedaBinaria(dicOtros, tamOtros, cadena);
        if (posO != -1) {   // es OTROS
            arrContOtros[posO]++;
            contOtros++;
            continue;
        }
        int posP = busquedaBinaria(dicPalabras, tamPalabras, cadena);
        if (posP != -1) {   // es CONTENIDO
            arrContPalabras[posP]++;
            contContenido++;
            continue;
        }
        registrarDesconocida(dicDesc, frecDesc, tamDesc, cadena);   // es DESCONOCIDA
        contDesc++;
    }
}

void pasaAMinusculas(char* cadena) {
    for (int i = 0; cadena[i]; i++) {
        cadena[i] = tolower(cadena[i]);   // 'A' -> 'a', el resto no cambia
    }
}

int busquedaBinaria(char** dic, int tamDicc, char* cadena) {
    int inicio = 0;
    int fin = tamDicc - 1;
    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        int cmp = strcmp(cadena, dic[medio]);
        if (cmp == 0) {
            return medio;
        }
        if (cmp < 0) {
            fin = medio - 1;
        } else {
            inicio = medio + 1;
        }
    }
    return -1;
}

// Inserción ordenada: mantiene dicDesc ordenado alfabéticamente y sin repetidos
void registrarDesconocida(char** dicDesc, int* frecDesc, int& tamDesc, const char* palabra) {
    int pos = 0;
    while (pos < tamDesc && strcmp(dicDesc[pos], palabra) < 0) {   // buscar su lugar
        pos++;
    }
    if (pos < tamDesc && strcmp(dicDesc[pos], palabra) == 0) {     // ya estaba
        frecDesc[pos]++;
        return;
    }
    for (int j = tamDesc; j > pos; j--) {                          // abrir espacio
        dicDesc[j] = dicDesc[j - 1];
        frecDesc[j] = frecDesc[j - 1];
    }
    dicDesc[pos] = new char[strlen(palabra) + 1];                  // insertar
    strcpy(dicDesc[pos], palabra);
    frecDesc[pos] = 1;
    tamDesc++;
}

void generarReportes(char** dicOtros, int tamOtros, int* arrContOtros,
                     char** dicPalabras, int tamPalabras, int* arrContPalabras,
                     char** dicDesc, int* frecDesc, int tamDesc,
                     int contOtros, int contContenido, int contDesc) {
    ofstream archDesc, resumen, histograma, rankingGeneral;
    abrirArchivo(archDesc, "ArchivosDeReportes/desconocidos.txt");
    abrirArchivo(resumen, "ArchivosDeReportes/resumen.txt");
    abrirArchivo(histograma, "ArchivosDeReportes/histograma.txt");
    abrirArchivo(rankingGeneral, "ArchivosDeReportes/rankingGeneral.txt");

    escribirDesconocidos(archDesc, dicDesc, frecDesc, tamDesc);
    creaResumenGeneral(contOtros, contContenido, contDesc, tamDesc, resumen,
                       tamOtros, tamPalabras, arrContOtros, arrContPalabras);
    creaHistograma(histograma, dicPalabras, tamPalabras, arrContPalabras);
    creaRankingGeneral(rankingGeneral, dicPalabras, tamPalabras, arrContPalabras,
                       dicOtros, tamOtros, arrContOtros);
}

void escribirDesconocidos(ofstream& archDesc, char** desc, int* frec, int n) {
    archDesc << left << setw(15) << "Palabra" << "Frecuencia" << endl;
    for (int i = 0; i < n; i++) {
        archDesc << left << setw(15) << desc[i] << frec[i] << endl;
    }
}

void creaResumenGeneral(int contOtros, int contContenido, int contDesc, int distDesc,
                        ofstream& resumen, int tamOtros, int tamPalabras,
                        int* arrContOtros, int* arrContPalabras) {

    int total = contOtros + contContenido + contDesc;
    int distCont = cuentaDistintas(arrContPalabras, tamPalabras);
    int distOtro = cuentaDistintas(arrContOtros, tamOtros);
    int vocab = distOtro + distCont + distDesc;

    resumen << "============================================================" << endl;
    resumen << "REPORTE 1: RESUMEN GENERAL" << endl;
    resumen << "============================================================" << endl;
    resumen << fixed << setprecision(2) << left;
    resumen << setw(15) << "Categoria" << right << setw(10) << "Tokens" << setw(10) << "%"
            << setw(12) << "Distintas" << endl;
    resumen << left << setw(15) << "CONTENIDO" << right << setw(10) << contContenido
            << setw(10) << 100.0 * contContenido / total << setw(12) << distCont << endl;
    resumen << left << setw(15) << "OTROS" << right << setw(10) << contOtros
            << setw(10) << 100.0 * contOtros / total << setw(12) << distOtro << endl;
    resumen << left << setw(15) << "DESCONOCIDA" << right << setw(10) << contDesc
            << setw(10) << 100.0 * contDesc / total << setw(12) << distDesc << endl;
    resumen << endl;
    resumen << left;
    resumen << "Total de palabras (tokens) .........." << total << endl;
    resumen << "Vocabulario (palabras distintas) ....." << vocab << endl;
    resumen << "Riqueza lexica (TTR) ................." << (double)vocab / total << endl;
}

// Palabras del diccionario que aparecieron al menos una vez en el texto
int cuentaDistintas(int* arrCont, int tam) {
    int dist = 0;
    for (int i = 0; i < tam; i++) {
        if (arrCont[i] > 0) {
            dist++;
        }
    }
    return dist;
}

void creaHistograma(ofstream& histograma, char** dicPalabras, int tamPalabras, int* arrContPalabras) {
    ordenarFrecuencias(dicPalabras, tamPalabras, arrContPalabras);
    histograma << "REPORTE 2: HISTOGRAMA (cada # = 1 aparicion)" << endl;
    for (int i = 0; i < tamPalabras && arrContPalabras[i] > 0; i++) {
        histograma << left << setw(12) << dicPalabras[i] << "| ";
        imprime(histograma, '#', arrContPalabras[i]);
    }
}

void ordenarFrecuencias(char** dic, int tam, int* frec) {
    for (int i = 0; i < tam - 1; i++) {
        for (int j = i + 1; j < tam; j++) {
            if (vaAntes(dic[j], frec[j], dic[i], frec[i])) {
                intercambiar(dic[i], dic[j]);
                intercambiar(frec[i], frec[j]);
            }
        }
    }
}

// Criterio multiple: mayor frecuencia primero; si empatan, orden alfabetico
bool vaAntes(const char* palabra1, int frec1, const char* palabra2, int frec2) {
    return frec1 > frec2 or
        (frec1 == frec2 and strcmp(palabra1, palabra2) < 0);
}

void imprime(ofstream& histograma, char car, int n) {
    for (int j = 0; j < n; j++) {
        histograma << car;
    }
    histograma << " (" << n << ")" << endl;
}

// Mezcla las dos listas ordenadas por frecuencia (solo palabras que aparecieron)
void creaRankingGeneral(ofstream& ranking, char** dicPalabras, int tamPalabras, int* arrContPalabras,
                        char** dicOtros, int tamOtros, int* arrContOtros) {
    ordenarFrecuencias(dicPalabras, tamPalabras, arrContPalabras);
    ordenarFrecuencias(dicOtros, tamOtros, arrContOtros);
    ranking << "REPORTE 3: RANKING GENERAL" << endl;
    ranking << left << setw(6) << "Pos" << setw(15) << "Palabra" << setw(12) << "Categoria" << "Frec" << endl;

    int iPalabras = 0, iOtros = 0, pos = 1;
    while (true) {
        bool quedanPalabras = iPalabras < tamPalabras and arrContPalabras[iPalabras] > 0;
        bool quedanOtros = iOtros < tamOtros and arrContOtros[iOtros] > 0;
        if (!quedanPalabras and !quedanOtros) {
            break;
        }
        if (quedanPalabras and (!quedanOtros or vaAntes(dicPalabras[iPalabras], arrContPalabras[iPalabras],
                                                         dicOtros[iOtros], arrContOtros[iOtros]))) {
            imprimirFilaRanking(ranking, pos, dicPalabras[iPalabras], "CONTENIDO", arrContPalabras[iPalabras]);
            iPalabras++;
        } else {
            imprimirFilaRanking(ranking, pos, dicOtros[iOtros], "OTROS", arrContOtros[iOtros]);
            iOtros++;
        }
        pos++;
    }
}

void imprimirFilaRanking(ofstream& ranking, int pos, const char* palabra, const char* categoria, int frec) {
    ranking << left << setw(6) << pos << setw(15) << palabra << setw(12) << categoria << frec << endl;
}

void liberarMemoria(char** dicOtros, int* arrContOtros, int tamOtros,
                    char** dicPalabras, int* arrContPalabras, int tamPalabras,
                    char** dicDesc, int tamDesc) {
    for (int i = 0; i < tamOtros; i++) {
        delete[] dicOtros[i];
    }
    for (int i = 0; i < tamPalabras; i++) {
        delete[] dicPalabras[i];
    }
    for (int i = 0; i < tamDesc; i++) {
        delete[] dicDesc[i];
    }
    delete[] dicOtros;
    delete[] arrContOtros;
    delete[] dicPalabras;
    delete[] arrContPalabras;
}
