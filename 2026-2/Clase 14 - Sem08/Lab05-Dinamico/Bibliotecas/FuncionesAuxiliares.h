//
// Created by Eric Huiza on 10/9/26.
//

#ifndef LAB05_FUNCIONESAUXILIARES_H
#define LAB05_FUNCIONESAUXILIARES_H

#define CAP_PACIENTES 100
#define CAP_ATENCIONES 600
#define CAP_ESPECIALIDADES 20
#define TAM_LINEA 175

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void cargarPacientes(
    const char*, int*&, char*&, int*&, double*&, int&);
void cargarEspecialidades(const char*,
    int*&,
    double*&,
    int&);
void cargarAtenciones(const char*,
    int*&,
    int*&,
    double*&,
    int&);

void procesarAtenciones(
    const int*,
    const int*,
    const double*,
    int,

    const int*,
    double*,
    double*,
    int*,
    double*,
    int*,
    double*,
    int,

    const int*,
    const double*,
    int);

double buscarMontoLimitePaciente(const int*, const double*, int, int);
double buscarCostoHoraEspecialidad(const int*, const double*, int, int);

void pagarAtencion(const int*, double*, double*, int*, int, double, int);
void registrarPagoPendiente(const int*, double*, int*, double, int, int);

void calcularMontoMax(const int*, double*, int, double, int);
int cantidadDePacientesPendientesDePago(const int*, int);
double totalMontosPendientesDePago(const double*, int);

void ordenarPacientes(int*, char*, int*, double*, double*, int*, double*, int*, double*, int);
void intercambiar(int&, int&);
void intercambiar(char&, char&);
void intercambiar(double&, double&);

void generarReportePrueba(const char*,
    const int*, const char*, const int*, const double*, int,
    const int*, const double*, int);
void generarReportePacientesPrueba(ofstream&, const int*, const char*, const int*, const double*, int);
void generarReporteEspecialidades(ofstream&, const int*, const double*, int);

void generarReporte(const char*, const int*, const char*, const int*, const double*, const int*, const double*, const int*, const double*, int);
void imprimirPaciente(ofstream&, const int*, const char*, const int*, const double*, const int*, const double*, const int*, const double*, int);

void imprimirLinea(ofstream&, int, char='=');

#endif //LAB05_FUNCIONESAUXILIARES_H
