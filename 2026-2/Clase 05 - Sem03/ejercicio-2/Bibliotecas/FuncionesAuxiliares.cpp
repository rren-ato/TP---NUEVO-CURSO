#include "FuncionesAuxiliares.h"
#include <iomanip>

bool abrirArchivos(ifstream& archivoEntrada, ofstream& archivoReporte) {
    archivoEntrada.open("ArchivosDeDatos/facturacion.txt", ios::in);
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

void imprimirFechaHora(ofstream& archivoReporte, long long clave) {
    long long fechaEntera = clave / 1000000;
    long long horaEntera = clave % 1000000;

    int anio = (int)(fechaEntera / 10000);
    int mes  = (int)((fechaEntera / 100) % 100);
    int dia  = (int)(fechaEntera % 100);

    int hora    = (int)(horaEntera / 10000);
    int minuto  = (int)((horaEntera / 100) % 100);
    int segundo = (int)(horaEntera % 100);

    imprimirFecha(archivoReporte, dia, mes, anio);
    archivoReporte << " ";
    imprimirHora(archivoReporte, hora, minuto, segundo);
}

void imprimirEncabezado(ofstream& archivoReporte) {
    imprimirLineaSeparadora(archivoReporte, 60);
    archivoReporte << "REPORTE DE FACTURA" << endl;
    imprimirLineaSeparadora(archivoReporte, 60);
    archivoReporte << left  << setw(10) << "Fecha" << "  "
                   << left  << setw(8)  << "Hora"
           << right << setw(8)  << "Codigo"
           << right << setw(8)  << "Cant"
           << right << setw(12) << "P.Unit"
           << right << setw(12) << "Subtotal" << endl;
    imprimirLineaSeparadora(archivoReporte, 60);
}

void imprimirFila(ofstream& archivoReporte,
                  int dia, int mes, int anio,
                  int hora, int minuto, int segundo,
                  int codigo, int cantidad, double precioUnitario) {
    double subtotal = cantidad * precioUnitario;

    imprimirFecha(archivoReporte, dia, mes, anio);
    archivoReporte << "  ";
    imprimirHora(archivoReporte, hora, minuto, segundo);

    archivoReporte << right
                   << setw(8) << codigo
                   << setw(8) << cantidad
                   << fixed << setprecision(2)
                   << setw(12) << precioUnitario
                   << setw(12) << subtotal << endl;
}

void imprimirTotales(ofstream& archivoReporte,
                     int movimientos, long long primerMov, long long ultimoMov,
                     double subtotalGeneral, double igv, double total) {
    imprimirLineaSeparadora(archivoReporte, 60);
    archivoReporte << "Movimientos registrados: " << movimientos << endl;

    archivoReporte << "Primer movimiento: ";
    imprimirFechaHora(archivoReporte, primerMov);
    archivoReporte << endl;

    archivoReporte << "Ultimo movimiento: ";
    imprimirFechaHora(archivoReporte, ultimoMov);
    archivoReporte << endl;

    imprimirLineaSeparadora(archivoReporte, 60);
    archivoReporte << fixed << setprecision(2) << setfill(' ');
    archivoReporte << left << setw(14) << "Subtotal:"  << right << setw(12) << subtotalGeneral << endl;
    archivoReporte << left << setw(14) << "IGV (18%):" << right << setw(12) << igv << endl;
    archivoReporte << left << setw(14) << "TOTAL:"     << right << setw(12) << total << endl;
    imprimirLineaSeparadora(archivoReporte, 60);
}

void generarReporteFactura(ifstream& archivoEntrada, ofstream& archivoReporte) {
    int dia, mes, anio;
    int hora, minuto, segundo;
    int codigo, cantidad;
    double precioUnitario;
    char sep;

    int movimientos = 0;
    double subtotalGeneral = 0;
    long long primerMov = 0;
    long long ultimoMov = 0;

    imprimirEncabezado(archivoReporte);

    while (true) {
        archivoEntrada >> dia;

        if (archivoEntrada.eof()) {
            break;
        }

        archivoEntrada >> sep >> mes >> sep >> anio
                >> hora >> sep >> minuto >> sep >> segundo
                >> codigo >> cantidad >> precioUnitario;

        imprimirFila(archivoReporte, dia, mes, anio, hora, minuto, segundo,
                     codigo, cantidad, precioUnitario);

        subtotalGeneral += cantidad * precioUnitario;
        movimientos++;

        long long fechaEntera = (long long) anio * 10000 + mes * 100 + dia;
        long long horaEntera  = (long long) hora * 10000 + minuto * 100 + segundo;
        long long clave = fechaEntera * 1000000 + horaEntera;

        if (movimientos == 1) {
            primerMov = clave;
            ultimoMov = clave;
        }
        if (clave < primerMov) primerMov = clave;
        if (clave > ultimoMov) ultimoMov = clave;
    }

    double igv = subtotalGeneral * 0.18;
    double total = subtotalGeneral + igv;

    imprimirTotales(archivoReporte, movimientos, primerMov, ultimoMov, subtotalGeneral, igv, total);
}
