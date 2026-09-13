#include "FuncionesAuxiliares.h"
#include <iomanip>

#define TAM_LINEA 100

bool abrirArchivos(ifstream& csv, ofstream& json) {
    csv.open("ArchivosDeDatos/ventas.csv", ios::in);
    json.open("ArchivosDeDatos/ventas.json", ios::out);
    return csv.is_open() and json.is_open();
}

bool abrirArchivos2(ifstream& json, ofstream& reporte) {
    json.open("ArchivosDeDatos/ventas.json", ios::in);
    reporte.open("ArchivosDeReporte/reporte.txt", ios::out);
    return json.is_open() and reporte.is_open();
}

void cerrarArchivos(ifstream& csv, ofstream& json) {
    csv.close();
    json.close();
}

void cerrarArchivos2(ifstream& json, ofstream& reporte) {
    json.close();
    reporte.close();
}

void imprimirLineaSeparadora(ofstream& salida, int longitud, char caracter) {
    salida << setfill(caracter)
           << setw(longitud)
           << ""
           << setfill(' ') << endl;
}

void imprimirFechaHoraISO(ofstream& salida,
    int anio, int mes, int dia, int hora, int minuto, int segundo) {
    salida << setfill('0')
           << setw(4) << anio << "-" << setw(2) << mes << "-" << setw(2) << dia << "T"
           << setw(2) << hora << ":" << setw(2) << minuto << ":" << setw(2) << segundo
           << setfill(' ');
}

long long fechaHora(int anio, int mes, int dia, int hora, int minuto, int segundo) {
    long long fechaEntera = (long long) anio * 10000 + mes * 100 + dia;   // yyyymmdd
    long long horaEntera  = (long long) hora * 10000 + minuto * 100 + segundo;  // hhmmss
    return fechaEntera * 1000000 + horaEntera;                           // yyyymmddhhmmss
}

void imprimirFechaHoraISO(ofstream& salida, long long fechaHora) {
    int segundo = (int) (fechaHora % 100);
    fechaHora /= 100;
    int minuto = (int) (fechaHora % 100);
    fechaHora /= 100;
    int hora = (int) (fechaHora % 100);
    fechaHora /= 100;
    int dia = (int) (fechaHora % 100);
    fechaHora /= 100;
    int mes = (int) (fechaHora % 100);
    fechaHora /= 100;
    int anio = (int) fechaHora;
    imprimirFechaHoraISO(salida, anio, mes, dia, hora, minuto, segundo);
}

bool esBisiesto(int anio) {
    if (anio % 400 == 0) {
        return true;
    }
    if (anio % 100 == 0) {
        return false;
    }
    if (anio % 4 == 0) {
        return true;
    }
    return false;
}

int diasDelMes(int mes, int anio) {
    if (mes == 1 or mes == 3 or mes == 5 or mes == 7 or mes == 8 or mes == 10 or mes == 12) {
        return 31;
    }
    if (mes == 4 or mes == 6 or mes == 9 or mes == 11) {
        return 30;
    }
    if (esBisiesto(anio)) {
        return 29;
    }
    return 28;
}

bool fechaHoraValida(int dia, int mes, int anio, int hora, int minuto, int segundo) {
    if (anio < 1) {
        return false;
    }
    if (mes < 1 or mes > 12) {
        return false;
    }
    if (dia < 1 or dia > diasDelMes(mes, anio)) {
        return false;
    }
    if (hora < 0 or hora > 23) {
        return false;
    }
    if (minuto < 0 or minuto > 59) {
        return false;
    }
    if (segundo < 0 or segundo > 59) {
        return false;
    }
    return true;
}

bool leerVentaCSV(ifstream& csv,
    int& dia, int& mes, int& anio, int& hora, int& minuto, int& segundo,
    int& id, char& categoria, double& importe) {

    int cantidad;
    char sep;
    double precioUnitario;

    if (!(csv >> dia)) {
        return false;
    }
    csv >> sep >> mes >> sep >> anio
        >> sep >> hora >> sep >> minuto >> sep >> segundo
        >> sep >> id >> sep >> categoria
        >> sep >> cantidad >> sep >> precioUnitario;

    importe = cantidad * precioUnitario;
    return true;
}

void acumularVenta(double importe, long long fechaHora, int id,
    int& nVentas, double& total, double& mayor, long long& fechaHoraMayor,
    int& idMayor, double& menor, long long& fechaHoraMenor, int& idMenor) {

    nVentas++;
    total += importe;

    if (nVentas == 1 or importe > mayor) {
        mayor = importe;
        fechaHoraMayor = fechaHora;
        idMayor = id;
    }
    if (nVentas == 1 or importe < menor) {
        menor = importe;
        fechaHoraMenor = fechaHora;
        idMenor = id;
    }
}

void imprimirResumenJSON(ofstream& json,
                         int nVentas, int ventasInvalidas, double total,
                         double mayor, long long fechaHoraMayor, int idMayor,
                         double menor, long long fechaHoraMenor, int idMenor) {
    json << "{\"ventas\": " << nVentas
         << ", \"ventasInvalidas\": " << ventasInvalidas
         << ", \"total\": " << fixed << setprecision(2) << total
         << ", \"mayorImporte\": " << mayor
         << ", \"mayorId\": " << idMayor
         << ", \"mayorFechaHora\": \"";
    imprimirFechaHoraISO(json, fechaHoraMayor);
    json << "\", \"menorImporte\": " << menor
         << ", \"menorId\": " << idMenor
         << ", \"menorFechaHora\": \"";
    imprimirFechaHoraISO(json, fechaHoraMenor);
    json << "\"}" << endl;
}

void imprimirVentaJSON(ofstream& json,
                       int anio, int mes, int dia, int hora, int minuto, int segundo,
                       int id, char categoria, double importe) {
    json << "{\"fechaHora\": \"";
    imprimirFechaHoraISO(json, anio, mes, dia, hora, minuto, segundo);
    json << "\", \"id\": " << id
         << ", \"categoria\": \"" << categoria << "\""
         << ", \"importe\": " << fixed << setprecision(2) << importe
         << "}" << endl;
}

void generarJSON(ifstream& csv, ofstream& json) {
    int dia, mes, anio, hora, minuto, segundo, id;
    char categoria;
    double importe;

    int nVentas = 0, ventasInvalidas = 0, idMayor = 0, idMenor = 0;
    double total = 0, mayor = 0, menor = 0;
    long long fechaHoraMayor = 0, fechaHoraMenor = 0;

    while (leerVentaCSV(csv, dia, mes, anio, hora, minuto, segundo, id, categoria, importe)) {
        if (!fechaHoraValida(dia, mes, anio, hora, minuto, segundo)) {
            ventasInvalidas++;
            continue;
        }

        long long _fechaHora = fechaHora(anio, mes, dia, hora, minuto, segundo);

        imprimirVentaJSON(json, anio, mes, dia, hora, minuto, segundo, id, categoria, importe);
        acumularVenta(importe, _fechaHora, id, nVentas, total, mayor,
                      fechaHoraMayor, idMayor, menor, fechaHoraMenor, idMenor);
    }

    imprimirResumenJSON(json, nVentas, ventasInvalidas, total,
                        mayor, fechaHoraMayor, idMayor, menor, fechaHoraMenor, idMenor);
}

long long leerFechaHoraISO(ifstream& json) {
    char sep;
    int anio, mes, dia, hora, minuto, segundo;

    json.ignore(TAM_LINEA, ':');
    json.ignore(TAM_LINEA, '"');
    json >> anio >> sep >> mes >> sep >> dia >> sep
         >> hora >> sep >> minuto >> sep >> segundo;
    return fechaHora(anio, mes, dia, hora, minuto, segundo);
}

bool esLineaDeVenta(ifstream& json) {
    json.ignore(TAM_LINEA, '"');   // pasa el {" inicial
    return json.peek() == 'f';     // 'f' de "fechaHora"; el resumen empieza con "ventas"
}

void leerResumenJSON(ifstream& json,
                     int& nVentas, int& ventasInvalidas, double& total,
                     double& mayor, long long& fechaHoraMayor, int& idMayor,
                     double& menor, long long& fechaHoraMenor, int& idMenor) {
    json.ignore(TAM_LINEA, ':');   // "ventas":
    json >> nVentas;
    json.ignore(TAM_LINEA, ':');   // "ventasInvalidas":
    json >> ventasInvalidas;
    json.ignore(TAM_LINEA, ':');   // "total":
    json >> total;
    json.ignore(TAM_LINEA, ':');   // "mayorImporte":
    json >> mayor;
    json.ignore(TAM_LINEA, ':');   // "mayorId":
    json >> idMayor;
    fechaHoraMayor = leerFechaHoraISO(json);   // "mayorFechaHora":
    json.ignore(TAM_LINEA, ':');   // "menorImporte":
    json >> menor;
    json.ignore(TAM_LINEA, ':');   // "menorId":
    json >> idMenor;
    fechaHoraMenor = leerFechaHoraISO(json);   // "menorFechaHora":
    json.ignore(TAM_LINEA, '\n');   // cierre } y fin de linea
}

void leerVentaJSON(ifstream& json, long long& fechaHora, int& id, char& categoria, double& importe) {
    fechaHora = leerFechaHoraISO(json);   // "fechaHora":
    json.ignore(TAM_LINEA, ':');   // "id":
    json >> id;
    json.ignore(TAM_LINEA, ':');   // "categoria":
    json.ignore(TAM_LINEA, '"');
    json >> categoria;
    json.ignore(TAM_LINEA, ':');   // "importe":
    json >> importe;
    json.ignore(TAM_LINEA, '\n');   // cierre } y fin de linea
}

void imprimirEncabezadoReporte(ofstream& reporte) {
    imprimirLineaSeparadora(reporte, 43);
    reporte << "REPORTE DE VENTAS (leido desde JSON)" << endl;
    imprimirLineaSeparadora(reporte, 43);
    reporte << left  << setw(19) << "Fecha y hora"
            << right << setw(6)  << "Id"
            << right << setw(4)  << "Cat"
            << right << setw(14) << "Importe" << endl;
    imprimirLineaSeparadora(reporte, 43);
}

void imprimirFilaVenta(ofstream& reporte, long long fechaHora, int id, char categoria, double importe) {
    imprimirFechaHoraISO(reporte, fechaHora);
    reporte << right << setw(6) << id
            << setw(4) << categoria
            << fixed << setprecision(2) << setw(14) << importe << endl;
}

void imprimirExtremo(ofstream& reporte, double valor, int id, long long fechaHora) {
    reporte << right << setw(23) << fixed << setprecision(2) << valor << endl;
    reporte << setw(2) << "" << "venta #" << id << " del ";
    imprimirFechaHoraISO(reporte, fechaHora);
    reporte << endl;
}

void imprimirPie(ofstream& reporte, int nVentas, int ventasInvalidas, double total,
                 double mayor, long long fechaHoraMayor, int idMayor,
                 double menor, long long fechaHoraMenor, int idMenor) {
    imprimirLineaSeparadora(reporte, 43);
    reporte << fixed << setprecision(2);
    reporte << left << setw(20) << "Ventas:" << right << setw(23) << nVentas << endl;
    reporte << left << setw(20) << "Fechas invalidas:" << right << setw(23) << ventasInvalidas << endl;
    reporte << left << setw(20) << "Total importes:" << right << setw(23) << total << endl;

    reporte << left << setw(20) << "Importe mayor:";
    imprimirExtremo(reporte, mayor, idMayor, fechaHoraMayor);

    reporte << left << setw(20) << "Importe menor:";
    imprimirExtremo(reporte, menor, idMenor, fechaHoraMenor);

    imprimirLineaSeparadora(reporte, 43);
}

void generarReporte(ifstream& json, ofstream& reporte) {
    int nVentas = 0, ventasInvalidas = 0, idMayor = 0, idMenor = 0;
    double total = 0, mayor = 0, menor = 0;
    long long fechaHoraMayor = 0, fechaHoraMenor = 0;

    long long fechaHora;
    int id;
    char categoria;
    double importe;

    imprimirEncabezadoReporte(reporte);

    while (true) {
        if (json.peek() != '{' or json.eof()) {
            break;
        }

        if (esLineaDeVenta(json)) {
            leerVentaJSON(json, fechaHora, id, categoria, importe);
            imprimirFilaVenta(reporte, fechaHora, id, categoria, importe);
        } else {
            leerResumenJSON(json, nVentas, ventasInvalidas, total,
                            mayor, fechaHoraMayor, idMayor, menor, fechaHoraMenor, idMenor);
        }
    }

    imprimirPie(reporte, nVentas, ventasInvalidas, total,
                mayor, fechaHoraMayor, idMayor, menor, fechaHoraMenor, idMenor);
}
