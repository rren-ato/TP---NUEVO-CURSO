#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    char texto[MAX_TEXTO];
    char equivalencias[MAX_LISTA];
    char stopWords[MAX_LISTA];
    char terminos[MAX_LISTA];
    int frecuencias[MAX_TERMINOS];
    int caracteresAntes;
    int numEquivalencias;
    int numSignos;
    int numStopWords;

    // 1. Carga: cada archivo se lee una sola vez
    cargarArchivo("ArchivosDeDatos/RetornoDelJedi.txt", texto);
    cargarArchivo("ArchivosDeDatos/Equivalencias.txt", equivalencias);
    cargarStopWords("ArchivosDeDatos/StopWords.txt", stopWords);
    cargarArchivo("ArchivosDeDatos/Terminos.txt", terminos);

    // 2. Procesamiento: todo en memoria
    normalizarTexto(texto, equivalencias, stopWords, caracteresAntes,
                    numEquivalencias, numSignos, numStopWords);
    contarTerminos(texto, terminos, frecuencias);

    // 3. Reportes
    escribirTexto("ArchivosDeReportes/RetornoDelJediNormalizado.txt", texto);
    imprimirReporte("ArchivosDeReportes/ReporteNormalizacion.txt", texto, terminos,
                    frecuencias, caracteresAntes, numEquivalencias, numSignos, numStopWords);

    return 0;
}
