#include "FuncionesAuxiliares.h"
#include <iomanip>

bool abrirArchivos(ifstream& archivoEntrada, ofstream& archivoReporte) {
    archivoEntrada.open("ArchivosDeDatos/lecturas.csv", ios::in);
    archivoReporte.open("ArchivosDeReporte/reporte.txt", ios::out);
    return archivoEntrada.is_open() and archivoReporte.is_open();
}

void cerrarArchivos(ifstream& archivoEntrada, ofstream& archivoReporte) {
    archivoEntrada.close();
    archivoReporte.close();
}

void imprimirLineaSeparadora(ofstream& archivoReporte, int longitud, char caracter) {
    archivoReporte << setfill(caracter)
                   << setw(longitud)
                   << ""
                   << setfill(' ') << endl;
}

void imprimirFecha(ofstream& archivoReporte, int dia, int mes, int anio) {
    archivoReporte << setfill('0')
                   << setw(2) << dia << "/"
                   << setw(2) << mes << "/"
           << setw(4) << anio
           << setfill(' ');
}

void imprimirHora(ofstream& archivoReporte, int hora, int minuto, int segundo) {
    archivoReporte << setfill('0')
           << setw(2) << hora << ":"
           << setw(2) << minuto << ":"
           << setw(2) << segundo
           << setfill(' ');
}

void imprimirFechaEntera(ofstream& archivoReporte, int fecha) {
    int anio = fecha / 10000;
    int mes  = (fecha / 100) % 100;
    int dia  = fecha % 100;
    imprimirFecha(archivoReporte, dia, mes, anio);
}

void imprimirHoraEntera(ofstream& archivoReporte, int horaEntera) {
    int hora    = horaEntera / 10000;
    int minuto  = (horaEntera / 100) % 100;
    int segundo = horaEntera % 100;
    imprimirHora(archivoReporte, hora, minuto, segundo);
}

void analizarLecturas(ifstream& archivoEntrada,
                      int& cantidad, double& suma, double& promedio,
                      double& maximo, int& maxId, char& maxSensor, int& maxFecha, int& maxHora,
                      double& minimo, int& minId, char& minSensor, int& minFecha, int& minHora) {
    int id, dia, mes, anio, hora, minuto, segundo;
    char sensor, sep;
    double lectura;

    cantidad = 0;
    suma = 0;
    promedio = 0;
    maximo = 0; maxId = 0; maxSensor = ' '; maxFecha = 0; maxHora = 0;
    minimo = 0; minId = 0; minSensor = ' '; minFecha = 0; minHora = 0;

    while (true) {
        archivoEntrada >> id;

        if (archivoEntrada.eof()) {
            break;
        }

        archivoEntrada >> sep >> dia >> sep >> mes >> sep >> anio
                       >> sep >> hora >> sep >> minuto >> sep >> segundo
                       >> sep >> sensor
                       >> sep >> lectura;

        int fecha = anio * 10000 + mes * 100 + dia;
        int horaEntera = hora * 10000 + minuto * 100 + segundo;

        if (cantidad == 0 or lectura > maximo) {
            maximo = lectura;
            maxId = id;
            maxSensor = sensor;
            maxFecha = fecha;
            maxHora = horaEntera;
        }
        if (cantidad == 0 or lectura < minimo) {
            minimo = lectura;
            minId = id;
            minSensor = sensor;
            minFecha = fecha;
            minHora = horaEntera;
        }

        suma += lectura;
        cantidad++;
    }

    // promedio = cantidad > 0 ? suma / cantidad : 0;

    if (cantidad > 0) {
        promedio = suma / cantidad;
    } else {
        promedio = 0;
    }
}

void generarReporte(ofstream& archivoReporte,
                    int cantidad, double suma, double promedio,
                    double maximo, int maxId, char maxSensor, int maxFecha, int maxHora,
                    double minimo, int minId, char minSensor, int minFecha, int minHora) {
    double rango = maximo - minimo;

    imprimirLineaSeparadora(archivoReporte, 48);
    archivoReporte << "REPORTE DE LECTURAS (CSV)" << endl;
    imprimirLineaSeparadora(archivoReporte, 48);

    archivoReporte << fixed << setprecision(2);
    archivoReporte << left << setw(28) << "Lecturas procesadas:" << right << setw(12) << cantidad << endl;
    archivoReporte << left << setw(28) << "Suma total:"          << right << setw(12) << suma     << endl;
    archivoReporte << left << setw(28) << "Promedio:"            << right << setw(12) << promedio << endl;
    archivoReporte << left << setw(28) << "Rango (max - min):"   << right << setw(12) << rango    << endl;

    imprimirLineaSeparadora(archivoReporte, 48);

    archivoReporte << left << setw(28) << "Lectura maxima:" << right << setw(12) << maximo << endl;
    archivoReporte << "  lectura #" << maxId << " del sensor " << maxSensor << ", registrada el ";
    imprimirFechaEntera(archivoReporte, maxFecha);
    archivoReporte << " a las ";
    imprimirHoraEntera(archivoReporte, maxHora);
    archivoReporte << endl;

    archivoReporte << left << setw(28) << "Lectura minima:" << right << setw(12) << minimo << endl;
    archivoReporte << "  lectura #" << minId << " del sensor " << minSensor << ", registrada el ";
    imprimirFechaEntera(archivoReporte, minFecha);
    archivoReporte << " a las ";
    imprimirHoraEntera(archivoReporte, minHora);
    archivoReporte << endl;

    imprimirLineaSeparadora(archivoReporte, 48);
}
