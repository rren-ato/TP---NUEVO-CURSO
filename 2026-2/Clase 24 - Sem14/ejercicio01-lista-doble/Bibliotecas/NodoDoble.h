#ifndef LISTADOBLE_NODODOBLE_H
#define LISTADOBLE_NODODOBLE_H

struct NodoDoble {
    int dato;                       // información
    struct NodoDoble* anterior;     // nodo previo
    struct NodoDoble* siguiente;    // próximo nodo
};

#endif //LISTADOBLE_NODODOBLE_H
