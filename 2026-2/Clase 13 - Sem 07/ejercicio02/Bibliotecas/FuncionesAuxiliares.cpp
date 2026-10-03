//
// Created by Eric Huiza on 10/3/26.
//

#include "FuncionesAuxiliares.h"

void sumar(int a, int b, int*& s) {
    int* c = new int; // asigna memoria dinámica en el heap
    *c = a + b;
    s = c;
}
