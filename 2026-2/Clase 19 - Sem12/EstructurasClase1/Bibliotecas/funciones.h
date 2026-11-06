//
// Created by svarg on 29/10/2026.
//

#ifndef ESTRUCTURAS1_FUNCIONES_H
#define ESTRUCTURAS1_FUNCIONES_H

#define TAM_EMPLEADOS 50

void leerFecha(struct Fecha &fechaLeida);
struct Fecha leerRetornarFecha();
void imprimirFecha(struct Fecha &fechaLeida);

void cargarEmpleados(const char *nombArch,struct NuevoEmpleado *arrEmpleados,int &cantEmpleados);
void mostrarEmpleados(const char *nombArch,struct NuevoEmpleado *arrEmpleados,int cantEmpleados);
void imprimirEmpleado(ofstream &arch,struct NuevoEmpleado &datEmpleado);
void imprimirDNIArch(ofstream &arch,int dni);
void imprimirFechaArch(ofstream &arch,struct Fecha fechaImp);

void ordenarEmpleados(struct NuevoEmpleado *arrEmpleados,int cantEmpleados);
void intercambiarNuevoEmpleado(struct NuevoEmpleado &datoI,struct NuevoEmpleado &datoJ);
#endif //ESTRUCTURAS1_FUNCIONES_H