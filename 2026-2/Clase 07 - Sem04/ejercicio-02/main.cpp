#include <iostream>
#include <fstream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    ifstream entrada;
    ofstream reporte;

    if (!abrirArchivos(entrada, reporte)) {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    int nA, nB, ignoradas;
    double sumaA, minA, maxA;
    double sumaB, minB, maxB;

    analizarSensores(entrada,
                     nA, sumaA, minA, maxA,
                     nB, sumaB, minB, maxB,
                     ignoradas);

    generarReporte(reporte, nA, sumaA, minA, maxA, nB, sumaB, minB, maxB, ignoradas);

    cerrarArchivos(entrada, reporte);

    return 0;
}
