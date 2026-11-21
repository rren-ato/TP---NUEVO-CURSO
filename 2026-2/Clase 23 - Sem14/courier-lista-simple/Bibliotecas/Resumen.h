#ifndef COURIERLISTASIMPLE_RESUMEN_H
#define COURIERLISTASIMPLE_RESUMEN_H

// Contadores de lo que se descarta durante el proceso
struct Resumen {
    int filasDescartadas;           // envíos con fecha inválida
    int eliminadosSinCobertura;     // envíos a distritos no atendidos
    int entregasIgnoradas;          // entregas inválidas o de envíos inexistentes
};

#endif //COURIERLISTASIMPLE_RESUMEN_H
