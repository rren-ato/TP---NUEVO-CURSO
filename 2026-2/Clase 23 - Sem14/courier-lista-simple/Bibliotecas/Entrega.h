#ifndef COURIERLISTASIMPLE_ENTREGA_H
#define COURIERLISTASIMPLE_ENTREGA_H
#include "Fecha.h"

#define PENDIENTE 'P'
#define ENTREGADO 'E'
#define DEVUELTO 'D'

struct Entrega {
    char estado;
    struct Fecha fecha;
    int diasDemora;
};

#endif //COURIERLISTASIMPLE_ENTREGA_H
