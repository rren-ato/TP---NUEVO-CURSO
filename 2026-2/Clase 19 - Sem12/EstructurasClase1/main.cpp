#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include "Bibliotecas/Empleado.h"
#include "Bibliotecas/Fecha.h"
#include "Bibliotecas/NuevoEmpleado.h"
#include "Bibliotecas/Funciones.h"

int main(){
    // struct Fecha hoy;
    // hoy.dia=3;
    // hoy.mes=11;
    // hoy.anio=2026;
    // cout<<"La fecha de hoy es "<<setfill('0')<<setw(2)<<hoy.dia<<'/'
    //     <<setw(2)<<hoy.mes<<'/'<<hoy.anio<<setfill(' ')<<endl;
    // struct Fecha maniana;
    // maniana=hoy;
    // maniana.dia++;
    // cout<<"La fecha de mañana será "<<setfill('0')<<setw(2)<<hoy.dia<<'/'
    //     <<setw(2)<<hoy.mes<<'/'<<hoy.anio<<setfill(' ')<<endl;
    // struct Fecha nuevaFecha{};
    // struct Fecha navidad{25,12,2026};
    // imprimirFecha(nuevaFecha);
    // imprimirFecha(navidad);
    // struct Fecha otraFecha;
    // leerFecha(otraFecha);
    // imprimirFecha(otraFecha);
    // otraFecha=leerRetornarFecha();
    // imprimirFecha(otraFecha);
    struct NuevoEmpleado arrEmpleados[TAM_EMPLEADOS];
    struct NuevoEmpleado *arrEmpleadosDinamico = new struct NuevoEmpleado[TAM_EMPLEADOS];
    int cantEmpleados;
    cargarEmpleados("ArchivosDeDatos/empleados.csv",arrEmpleados,cantEmpleados);
    mostrarEmpleados("ArchivosDeReporte/reportePersonas.txt",arrEmpleados,cantEmpleados);
    ordenarEmpleados(arrEmpleados,cantEmpleados);
    mostrarEmpleados("ArchivosDeReporte/reporteOrdenadoPersonas.txt",arrEmpleados,cantEmpleados);
    return 0;
}