#include "../menu.h"

HashTable hashPilotos(18); 
Grafo* grafoRutas = new Grafo();
Arbol* arbolPilotos = new Arbol();
BTree* arbolAviones = new BTree(5);
ListaCircularDoble* listaAviones = new ListaCircularDoble();

MatrizDispersa* matrizDispersa = new MatrizDispersa(grafoRutas, arbolPilotos, arbolAviones);