#include "FuncionesAuxiliares.h"
#include <iomanip>

#define TAM_LINEA 100

bool abrirArchivos(ifstream& archivoEntrada, ofstream& reporte) {
    archivoEntrada.open("ArchivosDeDatos/turnos.json", ios::in);
    reporte.open("ArchivosDeReporte/reporte.txt", ios::out);
    return archivoEntrada.is_open() and reporte.is_open();
}

void cerrarArchivos(ifstream& archivoEntrada, ofstream& reporte) {
    archivoEntrada.close();
    reporte.close();
}

void imprimirLineaSeparadora(ofstream& archivoReporte, int longitud, char caracter) {
    archivoReporte << setfill(caracter)
                   << setw(longitud)
                   << ""
                   << setfill(' ') << endl;
}

void leerTurnoJSON(ifstream& archivoEntrada, int& id, char& turno, int& pacientes) {
    archivoEntrada.ignore(TAM_LINEA, ':'); // Ignorar hasta el ':' de "id"
    archivoEntrada >> id;

    archivoEntrada.ignore(TAM_LINEA, ':'); // Ignorar hasta el ':' de "turno"
    archivoEntrada.ignore(TAM_LINEA, '"'); // Ignorar hasta la comilla de apertura
    archivoEntrada >> turno;

    archivoEntrada.ignore(TAM_LINEA, ':'); // Ignorar hasta el ':' de "pacientes"
    archivoEntrada >> pacientes;
    archivoEntrada.ignore(TAM_LINEA, '\n'); // Ignorar hasta el fin de la linea JSON
}

void acumularTurno(int pacientes, int& n, int& suma, int& minimo, int& maximo) {
    if (n == 0 or pacientes < minimo) {
        minimo = pacientes;
    }
    if (n == 0 or pacientes > maximo) {
        maximo = pacientes;
    }
    suma += pacientes;
    n++;
}

void analizarTurnos(ifstream& archivoEntrada,
                    int& nM, int& sumaM, int& minM, int& maxM,
                    int& nT, int& sumaT, int& minT, int& maxT) {
    int id, pacientes;
    char turno;

    nM = 0; sumaM = 0; minM = 0; maxM = 0;
    nT = 0; sumaT = 0; minT = 0; maxT = 0;

    while (true) {
        if (archivoEntrada.peek() != '{' or archivoEntrada.eof()) {
            break;
        }

        leerTurnoJSON(archivoEntrada, id, turno, pacientes);

        if (turno == 'M') {
            acumularTurno(pacientes, nM, sumaM, minM, maxM);
        } else if (turno == 'T') {
            acumularTurno(pacientes, nT, sumaT, minT, maxT);
        }
    }
}

void imprimirEncabezadoTurnos(ofstream& archivoReporte) {
    imprimirLineaSeparadora(archivoReporte, 62);
    archivoReporte << "REPORTE DE PACIENTES POR TURNO" << endl;
    imprimirLineaSeparadora(archivoReporte, 62);
    archivoReporte << left  << setw(10) << "Turno"
                   << right << setw(10) << "Registros"
           << right << setw(10) << "Suma"
           << right << setw(12) << "Promedio"
           << right << setw(10) << "Minimo"
           << right << setw(10) << "Maximo" << endl;
    imprimirLineaSeparadora(archivoReporte, 62);
}

void imprimirFilaTurno(ofstream& archivoReporte, char turno,
                       int n, int suma, int minimo, int maximo) {
    double promedio = n > 0 ? (double) suma / n : 0;

    archivoReporte << left  << setw(10) << turno
                   << right << setw(10) << n
                   << right << setw(10) << suma
                   << fixed << setprecision(2)
                   << setw(12) << promedio
                   << setw(10) << minimo
                   << setw(10) << maximo << endl;
}

void generarReporte(ofstream& archivoReporte,
                    int nM, int sumaM, int minM, int maxM,
                    int nT, int sumaT, int minT, int maxT) {
    imprimirEncabezadoTurnos(archivoReporte);

    imprimirFilaTurno(archivoReporte, 'M', nM, sumaM, minM, maxM);
    imprimirFilaTurno(archivoReporte, 'T', nT, sumaT, minT, maxT);

    imprimirLineaSeparadora(archivoReporte, 62);
    archivoReporte << left << setw(24) << "Total de registros:"
                   << right << setw(10) << (nM + nT) << endl;
    archivoReporte << left << setw(24) << "Total de pacientes:"
                   << right << setw(10) << (sumaM + sumaT) << endl;
    imprimirLineaSeparadora(archivoReporte, 62);
}
