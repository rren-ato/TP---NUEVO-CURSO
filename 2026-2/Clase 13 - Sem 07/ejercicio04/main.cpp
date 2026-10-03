#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    int* numeros;
    int num;
    cargarNumeros("ArchivosDeDatos/numeros.csv", numeros, num);

    for (int i = 0; i < num; i++) {
        cout << numeros[i] << endl;
    }

    delete[] numeros;

    return 0;
}
