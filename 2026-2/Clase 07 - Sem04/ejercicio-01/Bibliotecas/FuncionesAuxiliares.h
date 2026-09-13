#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>

using namespace std;

bool abrirArchivos(ifstream& clientes, ifstream& pedidos, ofstream& reporte);
void cerrarArchivos(ifstream& clientes, ifstream& pedidos, ofstream& reporte);

int acumularPedidosDeCliente(ifstream& pedidos, ofstream& salida,
    int idCliente, double& totalCliente);

void imprimirLineaSeparadora(ofstream& salida, int longitud, char caracter = '-');
void imprimirEncabezado(ofstream& salida);
void imprimirResumenCliente(ofstream& salida, int nPedidos, double totalCliente);
void imprimirCliente(ifstream& pedidos, ofstream& salida, int idCliente, char categoria,
    int& nPedidos, double& totalCliente);

void actualizarGlobales(int nPedidos, double totalCliente, int idCliente,
    int& nClientes, int& clientesSinPedidos, double& totalGeneral,
    int& idMayorGasto, double& mayorGasto);

void imprimirTotales(ofstream& salida,int nClientes, int clientesSinPedidos, double totalGeneral,
    int idMayorGasto, double mayorGasto);

void generarReporte(ifstream& clientes, ifstream& pedidos, ofstream& salida);

#endif
