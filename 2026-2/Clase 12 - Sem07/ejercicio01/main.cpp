#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    int numeros[CAPACIDAD] { 84, 16, 56, 30, 26, 96, 63, 42, 12, 71 };
    int num = 10; // longitud del arreglo

    // ordenarIntercambio(numeros, num);
    // ordenarSeleccion(numeros, num);
    ordenamientoBurbuja(numeros, num);
    imprimirNumeros(numeros, num);
    int pos = busquedaBinaria(numeros, num, 30);
    cout << pos << endl;

    // imprimirNumeros(numeros, num);

    return 0;
}
