#ifndef COURIERLISTASIMPLE_FUNCIONESAUXILIARES_H
#define COURIERLISTASIMPLE_FUNCIONESAUXILIARES_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "Nodo.h"
#include "Envio.h"
#include "Resumen.h"
#include "TotalZona.h"

using namespace std;

#define TAM_LINEA 100
#define ANIO_BASE 1900
#define PESO_LIMITE 10.0
#define RECARGO_PESO 0.15
#define ANCHO_REPORTE 100

// Creación de la lista de envíos
void crearLista(const char* nombArch, struct Nodo*& lista, struct Resumen& resumen);
void leerDatosEnvio(ifstream& arch, struct Envio& envio);
void inicializarDatosPendientes(struct Envio& envio);
void insertarOrdenada(struct Nodo*& lista, struct Envio& envio);
bool vaAntes(const struct Envio& a, const struct Envio& b);
struct Nodo* buscarEnvio(const char* codigo, struct Nodo* lista);
char* leerCadenaExacta(ifstream& arch, char delimitador);

// Clientes y destinos
void completarClientes(const char* nombArch, struct Nodo* lista);
void asignarCliente(struct Nodo* lista, int dni, const char* nombre, int telefono);
void asignarPersona(struct Persona& persona, const char* nombre, int telefono);
void completarDestinos(const char* nombArch, struct Nodo* lista);
void leerDestino(ifstream& arch, struct Destino& destino);
void asignarDestino(struct Nodo* lista, const struct Destino& destino);
void eliminarSinCobertura(struct Nodo*& lista, struct Resumen& resumen);

// Entregas y costos
void registrarEntregas(const char* nombArch, struct Nodo* lista, struct Resumen& resumen);
bool aplicarEntrega(struct Nodo* lista, const char* codigo, const struct Entrega& entrega);
void calcularCostos(struct Nodo* lista);
void calculaCostoDeEnvio(struct Envio& envio);

// Fechas
void leerFecha(ifstream& arch, struct Fecha& fecha);
bool esBisiesto(int anio);
int diasDelMes(int mes, int anio);
int diasDelAnio(int anio);
bool fechaValida(const struct Fecha& fecha);
int compararFechas(const struct Fecha& a, const struct Fecha& b);
int diasDesdeBase(const struct Fecha& fecha);
int diasEntre(const struct Fecha& desde, const struct Fecha& hasta);

// Reportes
void mostrarLista(const char* nombArch, const char* titulo, struct Nodo* lista,
                  const struct Resumen& resumen);
void inicializarZonas(struct TotalZona zonas[]);
void acumularZona(struct TotalZona zonas[], const struct Envio& envio);
void imprimeEncabezado(ofstream& arch, const char* titulo);
void imprimeEnvio(ofstream& arch, const struct Envio& envio);
void imprimeEntrega(ofstream& arch, const struct Entrega& entrega);
void imprimePersona(ofstream& arch, const char* rol, const struct Persona& persona);
void imprimeZonas(ofstream& arch, const struct TotalZona zonas[]);
void imprimeResumen(ofstream& arch, int cantidad, int pendientes, const char* codMayor,
                    int diasMayor, const struct Resumen& resumen);
void imprimeFecha(ofstream& arch, const struct Fecha& fecha);
void imprimeLinea(ofstream& arch, char car, int n);

// Liberación de memoria
void liberarEnvio(struct Envio& envio);
void eliminarLista(struct Nodo*& lista);

#endif //COURIERLISTASIMPLE_FUNCIONESAUXILIARES_H
