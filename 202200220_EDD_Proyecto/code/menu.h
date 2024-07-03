#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <fstream>
#include "./json/json.hpp"
#include "./estructuras/estructuras.h"

using namespace std;
using json = nlohmann::json;

// Variables compartidas
extern BTree* arbolAviones;
extern ListaCircularDoble* listaAviones;
extern Arbol* arbolPilotos;
extern HashTable hashPilotos;
extern Grafo* grafoRutas;
extern MatrizDispersa* matrizDispersa;
// Declaración de funciones
void cargarAviones();
void cargarPilotos();
void cargarRutas();
void cargarMovimientos();
void consultarHorasVuelo();
void recomendarRuta();

//Reportes
void visualizarReportes();
void generarGrafico(string dotFile, string pngFile);

#endif
