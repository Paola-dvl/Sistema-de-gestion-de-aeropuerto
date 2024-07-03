#include "estructuras.h"

void Grafo::insertarLugarDestino(string lugar, string destino, int distancia){
    Lugar* l1 = buscarLugar(lugar);
    Lugar* l2 = buscarLugar(destino);
    if (l1 == nullptr) l1 = insertarLugar(lugar);
    if (l2 == nullptr) l2 = insertarLugar(destino);
    Destino* destinoActual = l1->destinos;
    while(destinoActual != nullptr){
        if (destinoActual->lugar->nombre == destino)  break;
        destinoActual = destinoActual->siguiente;
    }
    if (destinoActual == nullptr){
        Destino* d2 = new Destino;
        d2->lugar = l2;
        d2->siguiente = nullptr;
        d2->distancia = distancia;
        if(l1->destinos == nullptr) l1->destinos = d2;
        else{
            Destino* destinoActual = l1->destinos;
            while(destinoActual->siguiente != nullptr) destinoActual = destinoActual->siguiente;
            destinoActual->siguiente = d2;
        }
        cout << "La ruta de " << lugar << " hacia " << destino << " se ha registrado." << endl;
    } else cout << "ERROR!! El viaje de " << lugar << " hacia " << destino << " ya esta registrado, saltando." << endl;
}

Lugar* Grafo::insertarLugar(string lugar){
    Lugar* l = new Lugar;
    l->id = indice++;
    l->nombre = lugar;
    l->destinos = nullptr;
    l->siguiente = nullptr;
    if (root == nullptr) root = l;
    else {
        Lugar* lugarActual = root;
        while (lugarActual->siguiente != nullptr) lugarActual = lugarActual->siguiente;
        lugarActual->siguiente = l;
    }
    return l;
}

Lugar* Grafo::buscarLugar(string lugar){
    Lugar* lugarActual = root;
    while (lugarActual != nullptr){
        if (lugarActual->nombre == lugar) return lugarActual;
        lugarActual = lugarActual->siguiente;
    }
    return lugarActual;
}

Ruta Grafo::encontrarRuta(Lugar* origen, Lugar* destino){
    Ruta ruta;
    ruta.ruta = "";
    ruta.distancia = INT_MAX;
    visitados[origen->id] = 1;
    Destino* destinoActual = origen->destinos;
    while (destinoActual != nullptr){
        if (destinoActual->lugar->nombre == destino->nombre){
            ruta.distancia = destinoActual->distancia;
            ruta.ruta = destino->nombre;
            return ruta;
        } else if (visitados[destino->id]){
            Ruta rutaDest = encontrarRuta(destinoActual->lugar, destino);
            if(rutaDest.distancia != INT_MAX) rutaDest.distancia += destinoActual->distancia;
            if(rutaDest.distancia < ruta.distancia) ruta = rutaDest;
        }
        destinoActual = destinoActual->siguiente;
    }
    visitados[origen->id] = 0;
    if(ruta.distancia != INT_MAX) ruta.ruta = origen->nombre + " -> " + ruta.ruta;
    return ruta;
}

void Grafo::exportToDOT(const std::string& archivo) {
    std::ofstream file(archivo);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << archivo << " para escribir." << std::endl;
        return;
    }

    file << "graph Grafo {\nlayout=neato;\n";
    int idVisitados [indice] = {0};
    Lugar* lugarActual = root;
    while (lugarActual != nullptr){
        if (!idVisitados[lugarActual->id])
        file << "node" << lugarActual->id << " [label=\"" << lugarActual->nombre << "\"];\n";
        idVisitados[lugarActual->id] = 1;
        Destino* d = lugarActual->destinos;
        while(d != nullptr){
            //if (!idVisitados[d->lugar->id])
            file << "node" << lugarActual->id << " -- node" << d->lugar->id << " [label=\"" << d->distancia << "\", len=5.00];\n";
            d = d->siguiente;
        }
        lugarActual = lugarActual->siguiente;
    }
    file << "}\n";
    file.close();
}