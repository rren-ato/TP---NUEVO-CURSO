#ifndef COURIERLISTASIMPLE_ENVIO_H
#define COURIERLISTASIMPLE_ENVIO_H

#include "Fecha.h"
#include "Persona.h"
#include "Destino.h"
#include "Entrega.h"

struct Envio {
    char* codigo;
    struct Fecha registro;
    struct Persona remitente;
    struct Persona destinatario;
    struct Destino destino;
    double peso;
    double costo;
    struct Entrega entrega;
};

#endif //COURIERLISTASIMPLE_ENVIO_H
