#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    int numeros[CAPACIDAD];
    int longitud;

    cargarNumeros("ArchivosDeDatos/numeros.txt",
        numeros, longitud);

    insertarOrdenado(numeros, CAPACIDAD, longitud, -1);
    insertarOrdenado(numeros, CAPACIDAD, longitud, -6);

    imprimir(numeros, longitud);

    // agregar(numeros, CAPACIDAD, longitud, 19);
    // agregar(numeros, CAPACIDAD, longitud, 12);
    // insertar(numeros, CAPACIDAD, longitud, 4, 15);
    //
    // imprimir(numeros, longitud);
    // cout << "Longitud del arreglo: " << longitud << endl;
    //
    // eliminar(numeros, longitud, 4);
    // agregar(numeros, CAPACIDAD, longitud, 17);
    // imprimir(numeros, longitud);
    // cout << "Longitud del arreglo: " << longitud << endl;

    return 0;
}
