#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include <cstring>
//
// Created by svarg on 30/10/2026.
//


#include "FuncionesCadenas.h"


char *leeCadenaExacta(ifstream &arch,char delim) {
    char aux[200],*ptr;
    arch.getline(aux,200,delim);
    if (arch.eof()) return nullptr;
    ptr=new char[strlen(aux)+1];
    strcpy(ptr,aux);
    return ptr;
}

ifstream abrirArchLec(const char *nombArch) {
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<" "<<endl;
        exit(1);
    }
    return arch;
}

ofstream abrirArchEsc(const char *nombArch) {
    ofstream arch(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<" "<<endl;
        exit(1);
    }
    return arch;
}