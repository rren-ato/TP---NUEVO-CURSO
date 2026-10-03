#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.h"

using namespace std;

int main() {
    int* s;
    sumar(3, 5, s);
    cout << *s << endl;

    delete s; // libera la memoria dinámica

    return 0;
}
