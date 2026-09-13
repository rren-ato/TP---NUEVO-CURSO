#include <iostream>
#include <fstream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    ifstream archivoEntrada;
    ofstream archivoSalida;

    if (!abrirArchivos(archivoEntrada, archivoSalida)) {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    generarReporteFactura(archivoEntrada, archivoSalida);

    cerrarArchivos(archivoEntrada, archivoSalida);

    return 0;
}
