//
// Created by svarg on 30/10/2026.
//

#ifndef CAPTURASVEHICULOS_VEHICULO_H
#define CAPTURASVEHICULOS_VEHICULO_H

#define TAM_REVISIONES 4
#define TAM_CAPTURAS 10

struct Vehiculo{
    int codigo;
    char categoria;
    int dni;
    char* placa;
    int arrRevisiones[TAM_REVISIONES];
    int cantRevisiones;
    struct Captura arrCapturasValidas[TAM_CAPTURAS];
    int cantCapturasVal;
    struct Captura arrCapturasInvalidas[TAM_CAPTURAS];
    int cantCapturasInval;
    struct Infraccion arrInfracciones[2]; // Acumuladores
};

#endif //CAPTURASVEHICULOS_VEHICULO_H