#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    char** dicOtros;
    char** dicPalabras;
    int* arrContOtros;
    int* arrContPalabras;
    char* dicDesc[MAX_DESC];
    int frecDesc[MAX_DESC] {};
    int tamOtros = 0, tamPalabras = 0, tamDesc = 0;
    int contOtros = 0, contContenido = 0, contDesc = 0;

    cargarDatos(dicOtros, arrContOtros, tamOtros, dicPalabras, arrContPalabras, tamPalabras);
    ordenarDiccionarios(dicOtros, tamOtros, dicPalabras, tamPalabras);
    procesarTexto(arrContPalabras, arrContOtros, dicDesc, frecDesc, tamDesc,
                  contOtros, contContenido, contDesc,
                  dicOtros, tamOtros, dicPalabras, tamPalabras);
    generarReportes(dicOtros, tamOtros, arrContOtros,
                    dicPalabras, tamPalabras, arrContPalabras,
                    dicDesc, frecDesc, tamDesc,
                    contOtros, contContenido, contDesc);
    liberarMemoria(dicOtros, arrContOtros, tamOtros,
                   dicPalabras, arrContPalabras, tamPalabras,
                   dicDesc, tamDesc);

    return 0;
}
