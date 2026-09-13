#include "FuncionesAuxiliares.h"
#include <iomanip>

bool abrirArchivos(ifstream& archivoEntrada, ofstream& archivoReporte) {
    archivoEntrada.open("ArchivosDeDatos/mediciones.txt", ios::in);
    archivoReporte.open("ArchivosDeReporte/reporte.txt", ios::out);
    return archivoEntrada.is_open() and archivoReporte.is_open();
}

void reabrirEntrada(ifstream& archivoEntrada) {
    archivoEntrada.close();
    archivoEntrada.open("ArchivosDeDatos/mediciones.txt", ios::in);
}

void cerrarArchivos(ifstream& archivoEntrada, ofstream& archivoReporte) {
    archivoEntrada.close();
    archivoReporte.close();
}

void calcularEstadisticas(ifstream& archivoEntrada,
                          int& cantidad, double& suma, double& promedio,
                          double& maximo, int& fechaMaximo,
                          double& minimo, int& fechaMinimo) {
    int dia, mes, anio;
    char sep;
    double valor;

    cantidad = 0;
    suma = 0;
    promedio = 0;
    maximo = 0;
    minimo = 0;
    fechaMaximo = 0;
    fechaMinimo = 0;

    while (archivoEntrada >> dia) {
        archivoEntrada >> sep >> mes >> sep >> anio >> valor;

        int fecha = anio * 10000 + mes * 100 + dia;

        if (cantidad == 0) {
            maximo = valor;
            minimo = valor;
            fechaMaximo = fecha;
            fechaMinimo = fecha;
        }
        if (valor > maximo) {
            maximo = valor;
            fechaMaximo = fecha;
        }
        if (valor < minimo) {
            minimo = valor;
            fechaMinimo = fecha;
        }

        suma += valor;
        cantidad++;
    }

    if (cantidad > 0) {
        promedio = suma / cantidad;
    }
}

void contarRelativosAlPromedio(ifstream& archivoEntrada, double promedio,
                               int& sobre, int& bajo, int& iguales) {
    int dia, mes, anio;
    char sep;
    double valor;

    sobre = 0;
    bajo = 0;
    iguales = 0;

    while (archivoEntrada >> dia) {
        archivoEntrada >> sep >> mes >> sep >> anio >> valor;

        if (valor > promedio) {
            sobre++;
        } else if (valor < promedio) {
            bajo++;
        } else {
            iguales++;
        }
    }
}

void imprimirLineaSeparadora(ofstream& archivoReporte, int longitud, char caracter) {
    archivoReporte << setfill(caracter)
                   << setw(longitud)
                   << ""
                   << setfill(' ')
                   << endl;
}

void imprimirFechaEntera(ofstream& archivoReporte, int fecha) {
    int anio = fecha / 10000;
    int mes  = (fecha / 100) % 100;
    int dia  = fecha % 100;
    archivoReporte << setfill('0')
                   << setw(2) << dia << "/"
                   << setw(2) << mes << "/"
                   << setw(4) << anio
           << setfill(' ');
}

void generarReporte(ofstream& archivoReporte,
                    int cantidad, double suma, double promedio,
                    double maximo, int fechaMaximo,
                    double minimo, int fechaMinimo,
                    int sobre, int bajo, int iguales) {
    double rango = maximo - minimo;

    imprimirLineaSeparadora(archivoReporte, 44);
    archivoReporte << "REPORTE DE MEDICIONES" << endl;
    imprimirLineaSeparadora(archivoReporte, 44);

    archivoReporte << fixed << setprecision(2);
    archivoReporte << left << setw(30) << "Mediciones procesadas:" << right << setw(12) << cantidad  << endl;
    archivoReporte << left << setw(30) << "Suma total:"            << right << setw(12) << suma      << endl;
    archivoReporte << left << setw(30) << "Promedio:"              << right << setw(12) << promedio  << endl;
    archivoReporte << left << setw(30) << "Rango (max - min):"     << right << setw(12) << rango     << endl;

    imprimirLineaSeparadora(archivoReporte, 44);

    archivoReporte << left << setw(30) << "Valor maximo:" << right << setw(12) << maximo << endl;
    archivoReporte << "  Registrado el ";
    imprimirFechaEntera(archivoReporte, fechaMaximo);
    archivoReporte << endl;
    archivoReporte << left << setw(30) << "Valor minimo:" << right << setw(12) << minimo << endl;
    archivoReporte << "  Registrado el ";
    imprimirFechaEntera(archivoReporte, fechaMinimo);
    archivoReporte << endl;

    imprimirLineaSeparadora(archivoReporte, 44);

    archivoReporte << left << setw(30) << "Dias sobre el promedio:" << right << setw(12) << sobre   << endl;
    archivoReporte << left << setw(30) << "Dias bajo el promedio:"  << right << setw(12) << bajo    << endl;
    archivoReporte << left << setw(30) << "Dias igual al promedio:" << right << setw(12) << iguales << endl;

    imprimirLineaSeparadora(archivoReporte, 44);
}
