#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//
// Created by svarg on 30/10/2026.
//

#include "Captura.h"
#include "Infraccion.h"
#include "Vehiculo.h"

#include "FuncionesAdicionales.h"

void cargarVehiculos(const char* nombArch,
                     struct Vehiculo*& arrVehiculos, int& cantVehiculos) {

    ifstream arch = abrirArchLec(nombArch);
    struct Vehiculo datVehic {};
    int cant;
    arch >> cant;
    arrVehiculos = new Vehiculo[cant];
    cantVehiculos = 0;
    while (true) {
        arch >> datVehic.codigo;
        if (arch.eof()) break;
        arch >> datVehic.categoria >> datVehic.dni;
        arch >> ws;
        datVehic.placa = leeCadenaExacta(arch, ' ');
        completaRevisiones(arch, datVehic);
        datVehic.arrInfracciones[0].tipo = 'M';
        datVehic.arrInfracciones[1].tipo = 'G';
        arrVehiculos[cantVehiculos] = datVehic;
        cantVehiculos++;
    }

}

void completaRevisiones(ifstream &arch, struct Vehiculo &datVehic) {
    int anio, i = 0;
    while (true) {
        arch >> anio;
        datVehic.arrRevisiones[i] = anio;
        i++;
        if (arch.get() == '\n') break;
    }
    datVehic.cantRevisiones = i;
}

ifstream abrirArchLec(const char *nombArch) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "Error: el archivo " << nombArch << " no se pudo abrir" << endl;
        exit(1);
    }
    return arch;
}

ofstream abrirArchEsc(const char *nombArch) {
    ofstream arch(nombArch, ios::out);
    if (not arch.is_open()) {
        cout << "Error: el archivo " << nombArch << " no se pudo abrir" << endl;
        exit(1);
    }
    return arch;
}

char* leeCadenaExacta(ifstream &arch, char delim) {
    char cadena[200], *ptr;
    arch.getline(cadena, 200, delim);
    if (arch.eof()) return nullptr;
    ptr = new char[strlen(cadena) + 1];
    strcpy(ptr, cadena);
    return ptr;
}

void mostrarVehiculos(const char* nombArch, struct Vehiculo* arrVehiculos, int cantVehiculos) {
    ofstream arch = abrirArchEsc(nombArch);
    imprimirSimbolo(arch, '=',TAM_LINEA);
    arch << setw(70) << "REPORTE DE INFRACCIONES DE TRANSITO" << endl << fixed << setprecision(2);
    for (int i = 0; i < cantVehiculos; i++) {
        imprimirDatosVehiculo(arch, arrVehiculos[i]);
        imprimirRevisiones(arch, arrVehiculos[i]);
        imprimirSimbolo(arch, '-',TAM_LINEA);
        imprimirCapturas(arch, arrVehiculos[i]);
        imprimirInfracciones(arch, arrVehiculos[i]);
    }
}

void imprimirDatosVehiculo(ofstream &arch, struct Vehiculo &datVehic) {
    imprimirSimbolo(arch, '=',TAM_LINEA);
    arch << "VEHICULO " << setw(6) << datVehic.codigo << " (" << left << datVehic.placa << ")";
    arch << setw(5) << ' ' << "Categoria: ";
    if (datVehic.categoria == 'E')
        arch << setw(15) << "Emergencia";
    else if (datVehic.categoria == 'P')
        arch << setw(15) << "Pesado";
    else if (datVehic.categoria == 'L')
        arch << setw(15) << "Ligero";
    else
        arch << setw(15) << "Motocicleta";
    arch << setw(5) << ' ' << "DNI: " << right << setw(10) << datVehic.dni;
}

void imprimirRevisiones(ofstream &arch, struct Vehiculo &datVehic) {
    arch << setw(5) << ' ' << left << setw(13) << "Revisiones:" << right;
    for (int i = 0; i < datVehic.cantRevisiones; i++)
        arch << setw(5) << datVehic.arrRevisiones[i];
    arch << endl;
}

void imprimirCapturas(ofstream &arch, struct Vehiculo &datVehic) {
    if (datVehic.cantCapturasVal > 0) {
        arch << "CAPTURAS VALIDAS" << endl;
        mostrarCapturas(arch, datVehic.arrCapturasValidas, datVehic.cantCapturasVal);
    }
    if (datVehic.cantCapturasInval > 0) {
        arch << "CAPTURAS INVALIDAS" << endl;
        mostrarCapturas(arch, datVehic.arrCapturasInvalidas, datVehic.cantCapturasInval);
    }
}

void mostrarCapturas(ofstream &arch, struct Captura *arrCapturas, int cant) {
    arch << setw(8) << "carril" << setw(8) << "km" << setw(12) << "velocidad" <<
            setw(10) << "camara" << setw(10) << "fecha" << endl;
    for (int i = 0; i < cant; i++) {
        arch << setw(6) << arrCapturas[i].carril
                << setw(10) << arrCapturas[i].kilometro
                << setw(10) << arrCapturas[i].velocidad
                << setw(10) << arrCapturas[i].camara;
        imprimirFecha(arch, arrCapturas[i].fecha);
        arch << endl;
    }
    imprimirSimbolo(arch, '-',TAM_LINEA);
}

void imprimirInfracciones(ofstream &arch, struct Vehiculo &datVehic) {
    arch << "INFRACCIONES" << setw(24) << "Cantidad" << setw(10) << "Monto" << setw(15) << "Puntos" << endl;
    for (int i = 0; i < 2; i++) {
        arch << datVehic.arrInfracciones[i].tipo;
        if (datVehic.arrInfracciones[i].tipo == 'M')
            arch << left << setw(20) << " - Exceso de velocidad" << right;
        else
            arch << left << setw(20) << " - Carril no permitido" << right;
        arch << setw(10) << datVehic.arrInfracciones[i].cantidad << setw(14)
                << datVehic.arrInfracciones[i].monto << setw(12)
                << datVehic.arrInfracciones[i].puntos << endl;
    }
}

void imprimirFecha(ofstream &arch, int fecha) {
    int a, m, d;
    a = fecha / 10000;
    d = fecha % 100;
    m = (fecha % 10000) / 100;
    arch << setw(4) << ' ' << setfill('0') << setw(2) << d << '/' << setw(2) << m
            << '/' << a << setfill(' ');
}

void procesarCapturas(const char* nombArch, struct Vehiculo *arrVehiculos, int &cantVehiculos) {
    ifstream arch = abrirArchLec(nombArch);
    int cod, idPos, carril, kil, d, m, a, cam, cantCap;
    double vel;
    char sep;
    struct Captura captura;
    while (true) {
        arch >> cod;
        if (arch.eof()) break;
        idPos = buscarVehiculo(arrVehiculos, cantVehiculos, cod);
        if (idPos != NO_ENCONTRADO) {
            arch >> sep >> vel >> sep >> carril >> sep >> kil >> sep >> d >> sep >> m >> sep >> a >> sep >> cam;
            captura.carril = carril;
            captura.kilometro = kil;
            captura.velocidad = vel;
            captura.camara = cam;
            captura.fecha = a * 10000 + m * 100 + d;
            if (validarCaptura(carril, vel))
                anadirCaptura(arrVehiculos[idPos].arrCapturasValidas,
                              arrVehiculos[idPos].cantCapturasVal, captura);
            else
                anadirCaptura(arrVehiculos[idPos].arrCapturasInvalidas,
                              arrVehiculos[idPos].cantCapturasInval, captura);
        } else
            while (arch.get() != '\n');
    }
}

int buscarVehiculo(struct Vehiculo *arrVehiculos, int cantVehiculos, int cod) {
    for (int i = 0; i < cantVehiculos; i++)
        if (arrVehiculos[i].codigo == cod)
            return i;
    return NO_ENCONTRADO;
}

bool validarCaptura(int carril, int vel) {
    return carril >= 1 and carril <= 4 and vel >= 0 and vel <= 300;
}

void anadirCaptura(struct Captura *arrCapturas, int &cant, struct Captura &captura) {
    arrCapturas[cant] = captura;
    cant++;
}

void identificarInfracciones(struct Vehiculo *arrVehiculos, int cantVehiculos) {
    for (int i = 0; i < cantVehiculos; i++)
        acumularInfraccion(arrVehiculos[i]);
}

void acumularInfraccion(struct Vehiculo &datVehiculo) {
    for (int i = 0; i < datVehiculo.cantCapturasVal; i++) {
        anadirExcesoVelocidad(datVehiculo, datVehiculo.arrCapturasValidas[i]);
        anadirCarrilNoPermitido(datVehiculo, datVehiculo.arrCapturasValidas[i]);
    }
}

void anadirCarrilNoPermitido(struct Vehiculo &datVehiculo, struct Captura &captura) {
    datVehiculo.arrInfracciones[1].tipo = 'G';
    int carril1 = captura.carril == 1 and datVehiculo.categoria == 'E';
    int carril2 = captura.carril == 2 and datVehiculo.categoria == 'P';
    int carril3 = captura.carril == 3 and (datVehiculo.categoria == 'E' or datVehiculo.categoria == 'L'
                                           or datVehiculo.categoria == 'M');
    int carril4 = captura.carril = 4 and datVehiculo.categoria == 'L';
    if (not(carril1 or carril2 or carril3 or carril4)) {
        datVehiculo.arrInfracciones[1].cantidad++;
        datVehiculo.arrInfracciones[1].monto += INF_CARRIL;
        datVehiculo.arrInfracciones[1].puntos += INF_PUNTOS_50;
    }
}

void anadirExcesoVelocidad(struct Vehiculo& datVehiculo, struct Captura& captura) {
    datVehiculo.arrInfracciones[0].tipo = 'M';
    int carril1 = captura.carril == 1 and captura.velocidad <= 80;
    int carril2 = captura.carril == 2 and captura.velocidad <= 60;
    int carril3 = captura.carril == 3 and
                  ((captura.kilometro >= 1 and captura.kilometro <= 100 and captura.velocidad <= 80) or
                   (captura.kilometro >= 101 and captura.kilometro <= 200 and captura.velocidad <= 120) or
                   (captura.kilometro >= 201 and captura.kilometro <= 300 and captura.velocidad <= 100));
    int carril4 = captura.carril = 4 and captura.velocidad >= 80 and
                                   ((captura.kilometro >= 1 and captura.kilometro <= 100 and captura.velocidad <= 120)
                                    or
                                    (captura.kilometro >= 101 and captura.kilometro <= 200 and captura.velocidad <= 160)
                                    or
                                    (captura.kilometro >= 201 and captura.kilometro <= 300 and captura.velocidad <=
                                     140));
    if (not(carril1 or carril2 or carril3 or carril4)) {
        datVehiculo.arrInfracciones[0].cantidad++;
        datVehiculo.arrInfracciones[0].monto += INF_VEL;
        datVehiculo.arrInfracciones[0].puntos += INF_PUNTOS_100;
    }
}

void ordenarVehiculos(struct Vehiculo *arrVehiculos, int cantVehiculos) {
    for (int i = 0; i < cantVehiculos - 1; i++)
        for (int j = i + 1; j < cantVehiculos; j++)
            if (strcmp(arrVehiculos[i].placa, arrVehiculos[j].placa) > 0)
                intercambiarVehiculo(arrVehiculos[i], arrVehiculos[j]);
    for (int i = 0; i < cantVehiculos; i++) {
        ordenarCapturas(arrVehiculos[i].arrCapturasValidas, arrVehiculos[i].cantCapturasVal);
        ordenarCapturas(arrVehiculos[i].arrCapturasInvalidas, arrVehiculos[i].cantCapturasInval);
    }
}

void intercambiarVehiculo(struct Vehiculo &datoI, struct Vehiculo &datoJ) {
    struct Vehiculo aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}

void ordenarCapturas(struct Captura *arrCapturas, int cantCapturas) {
    for (int i = 0; i < cantCapturas - 1; i++)
        for (int j = i + 1; j < cantCapturas; j++)
            if (arrCapturas[i].fecha < arrCapturas[j].fecha)
                intercambiarCaptura(arrCapturas[i], arrCapturas[j]);
}

void intercambiarCaptura(struct Captura &datoI, struct Captura &datoJ) {
    struct Captura aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}

void imprimirSimbolo(ofstream &arch, char car, int cant) {
    arch << setfill(car) << setw(cant) << car << setfill(' ') << endl;
}
