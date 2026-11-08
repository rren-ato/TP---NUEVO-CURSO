#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include "Bibliotecas/Captura.h"
#include "Bibliotecas/Infraccion.h"
#include "Bibliotecas/Vehiculo.h"
#include "Bibliotecas/FuncionesAdicionales.h"

int main() {
    struct Vehiculo *arrVehiculos;
    int cantVehiculos;
    cargarVehiculos("ArchivosDeDatos/vehiculos_registrados.txt", arrVehiculos,
                    cantVehiculos);
    mostrarVehiculos("ArchivosDeReporte/reporteInicial.txt", arrVehiculos, cantVehiculos);
    procesarCapturas("ArchivosDeDatos/capturas_camaras.csv", arrVehiculos, cantVehiculos);
    mostrarVehiculos("ArchivosDeReporte/reporteCapturas.txt", arrVehiculos, cantVehiculos);
    identificarInfracciones(arrVehiculos, cantVehiculos);
    mostrarVehiculos("ArchivosDeReporte/reporteInfracciones.txt", arrVehiculos, cantVehiculos);
    ordenarVehiculos(arrVehiculos, cantVehiculos);
    mostrarVehiculos("ArchivosDeReporte/reporteInfraccionesOrdenado.txt", arrVehiculos, cantVehiculos);
    return 0;
}
