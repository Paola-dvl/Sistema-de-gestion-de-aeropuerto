#include "estructuras.h"

void ListaCircularDoble::insertar(Avion avion) {
    ListaCircularDobleNodo* nuevoNodo = new ListaCircularDobleNodo;
    nuevoNodo->avion = avion;
    if (head == nullptr) {
        head = nuevoNodo;
        head->ant = head;
        head->sig = head;
        cout << "La aerolinea " << avion.numero_de_registro << " se ha registrado. (Mantenimiento)" << endl;
    } else {
        nuevoNodo->ant = head;
        nuevoNodo->sig = head->sig;
        head->sig->ant = nuevoNodo;
        head->sig = nuevoNodo;
        cout << "La aerolinea " << avion.numero_de_registro << " se ha registrado. (Mantenimiento)" << endl;
    }
}

Avion* ListaCircularDoble::buscarAvion(string numero_de_registro){
    if(head != nullptr){
        ListaCircularDobleNodo* nodoActual = head;
        do{
            if(nodoActual->avion.numero_de_registro == numero_de_registro) return &nodoActual->avion;
            nodoActual = nodoActual->sig;
        } while(nodoActual != head);
    }
    return nullptr;
}
void ListaCircularDoble::eliminar(string numero_de_registro){
    if(head != nullptr){
        ListaCircularDobleNodo* nodoActual = head;
        do{
            if(nodoActual->avion.numero_de_registro == numero_de_registro){
                if(nodoActual->sig == nodoActual) head = nullptr;
                else{
                    nodoActual->ant->sig = nodoActual->sig;
                    nodoActual->sig->ant = nodoActual->ant;
                }
                break;
            }
            nodoActual = nodoActual->sig;
        } while(nodoActual != head);
    }
}

void ListaCircularDoble::exportToDOT(const std::string &ruta) {
        std::ofstream archivo(ruta);
        archivo << "digraph G {\n";
        archivo << "  node [shape=box];\n";

        if (head != nullptr) {
            ListaCircularDobleNodo* actual = head;
            do {
                archivo << "  \"" << actual->avion.vuelo << "\" [label=\"" << actual->avion.vuelo << " - " << actual->avion.estado << "\"];\n";
                archivo << "  \"" << actual->avion.vuelo << "\" -> \"" << actual->ant->avion.vuelo << "\" [dir=both];\n";
                archivo << "  \"" << actual->avion.vuelo << "\" -> \"" << actual->sig->avion.vuelo << "\" [dir=both];\n";
                actual = actual->ant;
            } while (actual != head);
        }

        archivo << "}\n";
        archivo.close();
    }