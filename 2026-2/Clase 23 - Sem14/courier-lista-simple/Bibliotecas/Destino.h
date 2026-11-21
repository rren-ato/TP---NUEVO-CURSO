#ifndef COURIERLISTASIMPLE_DESTINO_H
#define COURIERLISTASIMPLE_DESTINO_H
#include "Tarifa.h"

struct Destino {
    int codigo;
    char* distrito;     // nullptr si el distrito no tiene cobertura
    char zona;
    struct Tarifa tarifa;
};

#endif //COURIERLISTASIMPLE_DESTINO_H
