#include <iostream>
#include <fstream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    ifstream clientes;
    ifstream pedidos;
    ofstream reporte;

    if (!abrirArchivos(clientes, pedidos, reporte)) {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    generarReporte(clientes, pedidos, reporte);

    cerrarArchivos(clientes, pedidos, reporte);

    return 0;
}
