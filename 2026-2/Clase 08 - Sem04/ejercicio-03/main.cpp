#include <iostream>
#include <fstream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    ifstream csv;
    ofstream jsonSalida;

    if (!abrirArchivos(csv, jsonSalida)) {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    generarJSON(csv, jsonSalida);
    cerrarArchivos(csv, jsonSalida);

    ifstream jsonEntrada;
    ofstream reporte;

    if (!abrirArchivos2(jsonEntrada, reporte)) {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    generarReporte(jsonEntrada, reporte);
    cerrarArchivos2(jsonEntrada, reporte);

    return 0;
}
