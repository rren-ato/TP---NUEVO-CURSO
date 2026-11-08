//
// Created by svarg on 30/10/2026.
//

#ifndef CAPTURASVEHICULOS_FUNCIONESADICIONALES_H
#define CAPTURASVEHICULOS_FUNCIONESADICIONALES_H

#define NO_ENCONTRADO -1
#define INF_CARRIL 428
#define INF_VEL 963
#define INF_PUNTOS_50 50
#define INF_PUNTOS_100 100
#define TAM_LINEA 120

void cargarVehiculos(const char *nombArch,
    struct Vehiculo *&arrVehiculos,int &cantVehiculos);
void completaRevisiones(ifstream &arch,struct Vehiculo &datVehic);
void mostrarVehiculos(const char *nombArch,struct Vehiculo *arrVehiculos,int cantVehiculos);
void imprimirDatosVehiculo(ofstream &arch,struct Vehiculo &datVehic);
void imprimirRevisiones(ofstream &arch,struct Vehiculo &datVehic);
void imprimirCapturas(ofstream &arch,struct Vehiculo &datVehic);
void mostrarCapturas(ofstream &arch,struct Captura *arrCapturas,int cant);
void imprimirInfracciones(ofstream &arch,struct Vehiculo &datVehic);

void imprimirFecha(ofstream &arch,int fecha);
void procesarCapturas(const char *nombArch,struct Vehiculo *arrVehiculos,int &cantVehiculos);
int buscarVehiculo(struct Vehiculo *arrVehiculos,int cantVehiculos,int cod);
int buscarVehiculo(struct Vehiculo *arrVehiculos,int cantVehiculos,int cod);
bool validarCaptura(int carril,int vel);
void anadirCaptura(struct Captura * arrCapturas,int &cant,struct Captura &captura);
void identificarInfracciones(struct Vehiculo *arrVehiculos,int cantVehiculos);
void acumularInfraccion(struct Vehiculo &datVehiculo);
void anadirCarrilNoPermitido(struct Vehiculo &datVehiculo,struct Captura &captura);
void anadirExcesoVelocidad(struct Vehiculo &datVehiculo,struct Captura &captura);
void ordenarVehiculos(struct Vehiculo *arrVehiculos,int cantVehiculos);
void  intercambiarVehiculo(struct Vehiculo &datoI,struct Vehiculo &datoJ);
void ordenarCapturas(struct Captura *arrCapturas,int cantCapturas);
void intercambiarCaptura(struct Captura &datoI,struct Captura &datoJ);

ifstream abrirArchLec(const char *nombArch);
ofstream abrirArchEsc(const char *nombArch);
char * leeCadenaExacta(ifstream &arch,char delim);
void imprimirSimbolo(ofstream &arch,char car, int cant);
#endif //CAPTURASVEHICULOS_FUNCIONESADICIONALES_H