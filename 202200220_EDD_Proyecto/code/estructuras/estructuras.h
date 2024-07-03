#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Avion {
    string vuelo;
    string numero_de_registro;
    string modelo;
    int capacidad;
    string aerolinea;
    string ciudad_destino;
    string estado;
};
struct Piloto {
    string nombre;
    string nacionalidad;
    string numero_de_id;
    string vuelo;
    int horas_de_vuelo;
    string tipo_de_licencia;
};
//Arbol B
class BTreeNode {
public:
    bool isLeaf;
    vector<Avion> keys;
    vector<BTreeNode*> children;
    int t; // Grado mínimo
    int m; // Grado máximo
    BTreeNode(int _t, int _m, bool _isLeaf);
    void traverse();
    BTreeNode* search(const string& k);
    Avion* getAvionVuelo(BTreeNode* node, const std::string& vuelo);
    Avion* getAvionDestino(BTreeNode* node, const std::string& destino);
    Avion* getAvionRegistro(const string& k);
    void insertNonFull(const Avion& k);
    void splitChild(int i, BTreeNode* y);
    void remove(const string& k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    Avion getPredecessor(int idx);
    Avion getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);

    friend class BTree;
};
class BTree {
public:
    BTreeNode* root;
    int t; // Grado mínimo
    int m; //grado maximo
    BTree(int _m) {
        root = nullptr;
        t = _m/2;
        m = _m - 1;
    }
    void traverse() {
        if (root != nullptr) root->traverse();
    }
    BTreeNode* search(const string& k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }
    void insert(const Avion& k);
    void remove(const string& k);
    void exportToDOT(const string& archivo);
    void exportToDOTHelper(ofstream& file, BTreeNode* node, int& nodeId);
};

//Lista Circular
struct ListaCircularDobleNodo {
    Avion avion;
    ListaCircularDobleNodo* ant;
    ListaCircularDobleNodo* sig;
};
class ListaCircularDoble {
private:
public:
    ListaCircularDobleNodo* head;
    ListaCircularDoble() : head(nullptr) {}
    void insertar(Avion avion);
    void exportToDOT(const string &ruta);
    Avion* buscarAvion(string numero_de_registro);
    void eliminar(string numero_de_registro);
};

//Arbol Binario
struct Node {
    Piloto piloto;
    Node* left;
    Node* right;
};
class Arbol{
public:
    Node* root;
    Node* insert(Node* root, Piloto piloto);
    Arbol() : root(nullptr) {}
    void preOrder(Node* root);
    void inOrder(Node* root);
    void postOrder(Node* root);
    void eliminar(Node* root, string numero_de_id);
    void exportToDOT(const string& archivo);
    Piloto* getPiloto(Node* root, string vuelo);
    Piloto* getPilotoId(Node* root, string numero_de_id);
private:
    int i;
    void exportToDOTHelper(ofstream& file, Node* root);
    Node* findMin(Node* root);
};

//Hash
struct HashNode {
    Piloto piloto;
    HashNode* next;

    HashNode(Piloto p) : piloto(p), next(nullptr) {}
};
class HashTable {
private:
    HashNode** table;
    int size;
    int hashFunction(const std::string& key);

public:
    HashTable(int size);
    ~HashTable();
    bool insert(Piloto piloto);
    void eliminar(Piloto* piloto);
    void exportToDOT(const std::string& archivo);
};

//Grafo dirigido/ Lista de adyasiencia
struct Lugar;
struct Destino {
    Lugar* lugar;
    int distancia;
    Destino* siguiente;
};
struct Lugar {
    int id;
    string nombre;
    Destino* destinos;
    Lugar* siguiente;
};
struct Ruta{
    int distancia;
    string ruta;
};
class Grafo{
private:
    Lugar* insertarLugar(string lugar);
public:
    Lugar* root;
    int indice = 0;
    Ruta mejorRuta;
    int visitados[0];
    Grafo() : root(nullptr) {}
    Lugar* buscarLugar(string lugar);
    void insertarLugarDestino(string lugar, string destino, int distancia);
    void exportToDOT(const string& archivo);
    Ruta encontrarRuta(Lugar* origen, Lugar* destino);
};

//Matriz disperza
class Celda{
private:
public:
    int fila, columna;
    Piloto* piloto;
    Avion* vuelo;
    Lugar* destino;
    Celda* arriba, *abajo, *derecha, *izquierda;
    Celda(): arriba(nullptr), abajo(nullptr), derecha(nullptr), izquierda(nullptr), fila(0), columna(0) {}
};
class MatrizDispersa{
private:
    Celda* head;
    Grafo* grafoRutas;
    Arbol* arbolPilotos;
    BTree* arbolAviones; 
    void insertarCelda(Celda* fila, Celda* columna, Celda* celda);
    Celda* getColumna(string destino);
    Celda* getFila(string vuelo);
    Celda* getCelda(Piloto* piloto);
    bool existeAvion(BTreeNode* node, const std::string& destino);
    void insertarAvion(BTreeNode* node, const std::string& destino);
public:
    MatrizDispersa(Grafo* grafoRutas, Arbol* arbolPilotos, BTree* arbolAviones): 
        head(new Celda()), grafoRutas(grafoRutas), arbolPilotos(arbolPilotos), arbolAviones(arbolAviones) {}
    void insertarVuelo(Avion* vuelo);
    void eliminarVuelo(Avion* vuelo);
    void insertarPiloto(Piloto* piloto);
    void eliminarPiloto(Piloto* piloto);
    void insertarDestino(Lugar* destino);
    void eliminarDestino(Lugar* destino);
    void exportToDOT(const string& archivo);
};

#endif