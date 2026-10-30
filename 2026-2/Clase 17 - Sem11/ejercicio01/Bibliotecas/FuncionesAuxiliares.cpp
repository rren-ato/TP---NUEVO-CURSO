//
// Created by Eric Huiza on 10/29/26.
//

#include "FuncionesAuxiliares.h"

void reemplazar(char* texto, const char* cadBus, const char* cadReem) {
    char aux[500];
    char* pt;
    pt = strstr(texto, cadBus);   // 1. ubicar
    if (pt == nullptr) {
        return;
    }
    *pt = 0;                                   // 2. cortar
    strcpy(aux, texto);                     // 3. parte izquierda
    strcat(aux, cadReem);                   // 4. reemplazo
    strcat(aux, &pt[strlen(cadBus)]);    // 5. parte derecha
    strcpy(texto, aux);                     // 6. devolver
}