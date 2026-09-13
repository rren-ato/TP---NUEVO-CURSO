#include "FuncionesAuxiliares.h"
#include <iomanip>

bool abrirArchivos(ifstream& clientes, ifstream& pedidos, ofstream& reporte) {
    clientes.open("ArchivoDeDatos/clientes.csv", ios::in);
    pedidos.open("ArchivoDeDatos/pedidos.csv", ios::in);
    reporte.open("ArchivoDeReporte/reporte.txt", ios::out);
    return clientes.is_open() && pedidos.is_open() && reporte.is_open();
}

void cerrarArchivos(ifstream& clientes, ifstream& pedidos, ofstream& reporte) {
    clientes.close();
    pedidos.close();
    reporte.close();
}

void imprimirLineaSeparadora(ofstream& salida, int longitud, char caracter) {
    salida << setfill(caracter)
           << setw(longitud)
           << ""
           << setfill(' ') << endl;
}

void imprimirEncabezado(ofstream& salida) {
    imprimirLineaSeparadora(salida, 52);
    salida << "REPORTE DE PEDIDOS POR CLIENTE" << endl;
    imprimirLineaSeparadora(salida, 52);
}

int acumularPedidosDeCliente(ifstream& pedidos, ofstream& salida,
                             int idCliente, double& totalCliente) {
    int idClienteDelPedido;
    char sep;
    double monto;
    int nPedidos = 0;

    totalCliente = 0;

    // Como no se pueden guardar los pedidos en memoria, se relee el archivo
    // completo desde el inicio por cada cliente.
    pedidos.clear();
    pedidos.seekg(0);

    while (pedidos >> idClienteDelPedido) {
        pedidos >> sep >> monto;

        if (idClienteDelPedido == idCliente) {
            salida << right << setw(10) << "pedido"
                   << setw(14) << fixed << setprecision(2) << monto << endl;
            totalCliente += monto;
            nPedidos++;
        }
    }

    return nPedidos;
}

void imprimirResumenCliente(ofstream& reporte, int nPedidos, double totalCliente) {
    double promedio = nPedidos > 0 ? totalCliente / nPedidos : 0;

    reporte << fixed << setprecision(2);
    reporte << setw(2) << "" << left << setw(16) << "Pedidos:"
            << right << setw(14) << nPedidos << endl;
    reporte << setw(2) << "" << left << setw(16) << "Total:"
            << right << setw(14) << totalCliente << endl;
    reporte << setw(2) << "" << left << setw(16) << "Promedio:"
            << right << setw(14) << promedio << endl;
}

void imprimirCliente(ifstream& pedidos, ofstream& salida,
    int idCliente, char categoria, int& nPedidos, double& totalCliente) {
    salida << "Cliente " << idCliente
           << " (categoria " << categoria << ")" << endl;

    nPedidos = acumularPedidosDeCliente(pedidos, salida, idCliente, totalCliente);

    if (nPedidos == 0) {
        salida << setw(4) << "" << "sin pedidos registrados" << endl;
    }

    imprimirResumenCliente(salida, nPedidos, totalCliente);
    imprimirLineaSeparadora(salida, 52);
}

void actualizarGlobales(int nPedidos, double totalCliente, int idCliente, int& nClientes,
    int& clientesSinPedidos, double& totalGeneral, int& idMayorGasto, double& mayorGasto) {
    nClientes++;
    totalGeneral += totalCliente;

    if (nPedidos == 0) {
        clientesSinPedidos++;
    }
    if (totalCliente > mayorGasto) {
        mayorGasto = totalCliente;
        idMayorGasto = idCliente;
    }
}

void imprimirTotales(ofstream& reporte, int nClientes, int clientesSinPedidos, double totalGeneral,
    int idMayorGasto, double mayorGasto) {
    reporte << fixed << setprecision(2);
    reporte << left << setw(30) << "Clientes procesados:"
            << right << setw(12) << nClientes << endl;
    reporte << left << setw(30) << "Clientes sin pedidos:"
            << right << setw(12) << clientesSinPedidos << endl;
    reporte << left << setw(30) << "Total facturado:"
            << right << setw(12) << totalGeneral       << endl;
    reporte << left << setw(30) << "Cliente con mayor gasto:"
            << right << setw(12) << idMayorGasto       << endl;
    reporte << setw(2) << "" << left << setw(28) << "monto de ese cliente:"
            << right << setw(12) << mayorGasto << endl;
    imprimirLineaSeparadora(reporte, 52);
}

void generarReporte(ifstream& clientes, ifstream& pedidos, ofstream& salida) {
    int idCliente;
    char sep, categoria;

    int nClientes = 0, clientesSinPedidos = 0, idMayorGasto = 0;
    double totalGeneral = 0, mayorGasto = 0;

    imprimirEncabezado(salida);

    while (true) {
        clientes >> idCliente;

        if (clientes.eof()) {
            break;
        }

        clientes >> sep >> categoria;

        int nPedidos;
        double totalCliente;
        imprimirCliente(pedidos, salida, idCliente, categoria, nPedidos, totalCliente);
        actualizarGlobales(nPedidos, totalCliente, idCliente,
                           nClientes, clientesSinPedidos, totalGeneral, idMayorGasto, mayorGasto);
    }

    imprimirTotales(salida, nClientes, clientesSinPedidos, totalGeneral, idMayorGasto, mayorGasto);
}
