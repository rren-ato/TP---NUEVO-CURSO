#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Empleado.h"

using namespace std;

//
// Created by svarg on 29/10/2026.
//

#include "Fecha.h"
#include "NuevoEmpleado.h"

#include "FuncionesCadenas.h"
#include "funciones.h"

void leerFecha(struct Fecha &fechaLeida){
    char sep;
    cout<<"Ingrese una fecha (d/m/a): ";
    cin>>fechaLeida.dia>>sep>>fechaLeida.mes>>sep>>fechaLeida.anio;
}

struct Fecha leerRetornarFecha(){
    char sep;
    struct Fecha fechaLeida;
    cout<<"Ingrese una fecha (d/m/a): ";
    cin>>fechaLeida.dia>>sep>>fechaLeida.mes>>sep>>fechaLeida.anio;
    return fechaLeida;
}

void imprimirFecha(struct Fecha &fechaLeida){
    cout<<"La fecha es "<<setfill('0')<<setw(2)<<fechaLeida.dia<<'/'
        <<setw(2)<<fechaLeida.mes<<'/'<<fechaLeida.anio<<setfill(' ')
        <<endl;
}

void cargarEmpleados(const char *nombArch,struct NuevoEmpleado *arrEmpleados,int &cantEmpleados){
    ifstream arch=abrirArchLec(nombArch);
    struct NuevoEmpleado empleadoAux;
    struct Fecha fechaAux;
    char sep;
    cantEmpleados=0;
    while (true) {
        empleadoAux.nombre=leeCadenaExacta(arch,',');
        if (arch.eof()) break;
        arch>>sep>>empleadoAux.dni>>sep>>empleadoAux.sueldo>>sep>>fechaAux.dia>>sep>>fechaAux.mes
            >>sep>>fechaAux.anio>>sep>>empleadoAux.distrito;
        arch.get();
        empleadoAux.nacimiento=fechaAux;
        arrEmpleados[cantEmpleados]=empleadoAux;
        cantEmpleados++;
    }
}

void mostrarEmpleados(const char *nombArch,struct NuevoEmpleado *arrEmpleados,int cantEmpleados){
    ofstream arch=abrirArchEsc(nombArch);
    arch<<setw(60)<<"REPORTE DE EMPLEADOS"<<endl<<fixed<<setprecision(2);
    arch<<setw(5)<<"DNI"<<setw(15)<<"NOMBRE"<<setw(33)<<"FEC.NACIMIENTO"
        <<setw(10)<<"SUELDO"<<setw(12)<<"DISTRITO"<<endl;
    for (int i=0;i<cantEmpleados;i++) {
        //primera opción
        // imprimirDNIArch(arch,arrEmpleados[i].dni);
        // arch<<setw(3)<<' '<<left<<setw(30)<<arrEmpleados[i].nombre<<right;
        // imprimirFechaArch(arch,arrEmpleados[i].nacimiento);
        // arch<<setw(12)<<arrEmpleados[i].sueldo<<setw(10)<<arrEmpleados[i].distrito<<endl;
        //segunda opción
        imprimirEmpleado(arch,arrEmpleados[i]);
    }
}

void imprimirEmpleado(ofstream &arch,struct NuevoEmpleado &datEmpleado){
    imprimirDNIArch(arch,datEmpleado.dni);
    arch<<setw(3)<<' '<<left<<setw(30)<<datEmpleado.nombre<<right;
    imprimirFechaArch(arch,datEmpleado.nacimiento);
    arch<<setw(12)<<datEmpleado.sueldo<<setw(10)<<datEmpleado.distrito<<endl;
}

void imprimirDNIArch(ofstream &arch,int dni){
    arch<<setfill('0')<<setw(8)<<dni<<setfill(' ');
}

void imprimirFechaArch(ofstream &arch,struct Fecha fechaImp){
    arch<<setfill('0')<<setw(2)<<fechaImp.dia<<'/'<<setw(2)<<fechaImp.mes<<'/'<<fechaImp.anio<<setfill(' ');

}

void ordenarEmpleados(struct NuevoEmpleado *arrEmpleados,int cantEmpleados){
    for (int i=0;i<cantEmpleados-1;i++)
        for (int j=i+1;j<cantEmpleados;j++)
            if (arrEmpleados[i].distrito<arrEmpleados[j].distrito or
                 (arrEmpleados[i].distrito==arrEmpleados[j].distrito and
                     strcmp(arrEmpleados[i].nombre,arrEmpleados[j].nombre)>0))
                intercambiarNuevoEmpleado(arrEmpleados[i],arrEmpleados[j]);
}

void intercambiarNuevoEmpleado(struct NuevoEmpleado &datoI,struct NuevoEmpleado &datoJ){
    struct NuevoEmpleado aux=datoI;
    datoI=datoJ;
    datoJ=aux;
}