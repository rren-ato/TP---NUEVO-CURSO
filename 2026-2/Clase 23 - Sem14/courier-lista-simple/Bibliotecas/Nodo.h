#ifndef COURIERLISTASIMPLE_NODO_H
#define COURIERLISTASIMPLE_NODO_H
#include "Envio.h"

struct Nodo {
    struct Envio envio;
    struct Nodo* siguiente;
};

#endif //COURIERLISTASIMPLE_NODO_H
