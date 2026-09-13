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

    int nM, sumaM, minM, maxM;
    int nT, sumaT, minT, maxT;

    analizarTurnos(entrada,
                   nM, sumaM, minM, maxM,
                   nT, sumaT, minT, maxT);

    generarReporte(reporte,
                   nM, sumaM, minM, maxM,
                   nT, sumaT, minT, maxT);

    cerrarArchivos(entrada, reporte);

    return 0;
}
