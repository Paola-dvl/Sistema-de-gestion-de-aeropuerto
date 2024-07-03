#include "estructuras.h"

void MatrizDispersa::insertarVuelo(Avion* vuelo){ //Fila
    if(getFila(vuelo->vuelo) != nullptr) return;
    Piloto* piloto = arbolPilotos->getPiloto(arbolPilotos->root, vuelo->vuelo);
    if(piloto == nullptr) return;
    Lugar* destino = grafoRutas->buscarLugar(vuelo->ciudad_destino);
    if(destino == nullptr) return;
    cout << "Avion paso" << endl;
    Celda* filActual = head;
    Celda* filNueva = new Celda();
    filNueva->vuelo = vuelo;
    while(filActual != nullptr){
        if(filActual->abajo == nullptr || filActual->abajo->vuelo->vuelo > filNueva->vuelo->vuelo){
            filNueva->abajo = filActual->abajo;
            if(filActual->abajo != nullptr) filActual->abajo->arriba = filNueva;
            filActual->abajo = filNueva;
            filNueva->arriba = filActual;
            filNueva->fila = filActual->fila + 1;
            filActual = filNueva->abajo;
            while(filActual != nullptr){
                filActual->fila++;
                filActual = filActual->abajo;   
            }
            break;
        }
        filActual = filActual->abajo;
    }
    cout << "insertado vuelo: " << vuelo->numero_de_registro << endl;
    insertarPiloto(piloto);
}
void MatrizDispersa::eliminarVuelo(Avion* vuelo){
    Celda* filActual = getFila(vuelo->vuelo);
    if(filActual == nullptr) return;
    Celda* filAux = filActual->derecha;
    while(filAux != nullptr) eliminarPiloto(filAux->piloto);
}
void MatrizDispersa::insertarPiloto(Piloto* piloto){ //Celda
    if(arbolAviones->root == nullptr) return;
    if(grafoRutas->root == nullptr) return;
    if(getCelda(piloto) != nullptr) return;
    cout <<"**************" << endl;
    Celda* filActual = getFila(piloto->vuelo);
    if (filActual == nullptr){
        Avion* vuelo = arbolAviones->root->getAvionVuelo(arbolAviones->root, piloto->vuelo);
        if(vuelo == nullptr) return;
        insertarVuelo(vuelo);
        return;
    }
    Celda* colActual = getColumna(filActual->vuelo->ciudad_destino);
    if(colActual == nullptr){
        Lugar* destino = grafoRutas->buscarLugar(filActual->vuelo->ciudad_destino);
        if(destino == nullptr) return;
        insertarDestino(destino);
        return;
    }
    cout << "Piloto paso" << endl;
    Celda* celdaNueva = new Celda();
    celdaNueva->piloto = piloto;
    celdaNueva->fila = filActual->fila;
    celdaNueva->columna = colActual->columna;
    while(filActual != nullptr){
        if(filActual->derecha == nullptr || filActual->derecha->columna > colActual->columna){
            celdaNueva->derecha = filActual->derecha;
            if(filActual->derecha != nullptr) filActual->derecha->izquierda = celdaNueva;
            filActual->derecha = celdaNueva;
            celdaNueva->izquierda = filActual;
            break;
        }
        filActual = filActual->derecha;
    }
    while(colActual != nullptr){
        if(colActual->abajo == nullptr || colActual->abajo->fila > celdaNueva->fila){
            celdaNueva->abajo = colActual->abajo;
            if(colActual->abajo != nullptr) colActual->abajo->arriba = celdaNueva;
            colActual->abajo = celdaNueva;
            celdaNueva->arriba = colActual;
            break;
        }
        colActual = colActual->abajo;
    }
    cout << "Insertado piloto: " << piloto->numero_de_id << endl;
}
void MatrizDispersa::eliminarPiloto(Piloto* piloto){
    Celda* celda = getCelda(piloto);
    if(celda == nullptr) return;
    celda->izquierda->derecha = celda->derecha;
    if(celda->derecha != nullptr) celda->derecha->izquierda = celda->izquierda;
    else if(celda->izquierda->columna == 0){
        Celda* filActual = celda->izquierda;
        filActual->arriba->abajo = filActual->abajo;
        filActual = filActual->arriba;
        if(filActual->abajo != nullptr) filActual->abajo->arriba = filActual->arriba;
        filActual = filActual->abajo;
        while(filActual != nullptr){
            filActual->fila--;
            Celda* celdaAux = filActual->derecha;
            while(celdaAux != nullptr){
                celdaAux->fila = filActual->fila;
                celdaAux = celdaAux->derecha;
            }
            filActual = filActual->abajo;   
        }
    }
    celda->arriba->abajo = celda->abajo;
    if(celda->abajo != nullptr) celda->abajo->arriba = celda->arriba;
    else if(celda->arriba->fila == 0){
        Celda* colActual = celda->arriba;
        colActual->izquierda->derecha = colActual->derecha;
        colActual = colActual->izquierda;
        if(colActual->derecha != nullptr) colActual->derecha->izquierda = colActual->izquierda;
        colActual = colActual->derecha;
        while(colActual != nullptr){
            colActual->columna--;
            Celda* celdaAux = colActual->abajo;
            while(celdaAux != nullptr){
                celdaAux->columna = colActual->columna;
                celdaAux = celdaAux->abajo;
            }
            colActual = colActual->derecha;
        }
    }
}
bool MatrizDispersa::existeAvion(BTreeNode* node, const std::string& destino) {
    for (int i = 0; i < node->t - 1; ++i) {
        if (node->keys[i].ciudad_destino == destino){
            Piloto* piloto = arbolPilotos->getPiloto(arbolPilotos->root, node->keys[i].vuelo);
            if (piloto != nullptr) return true;
            return false;
        }
    }
    for (size_t i = 0; i < node->t; ++i) {
        if (!node->leaf) {
            bool existe = existeAvion(node->C[i], destino);
            if(!existe) return existe;
        }
    }
    return false;
}
void MatrizDispersa::insertarAvion(BTreeNode* node, const std::string& destino) {
    for (int i = 0; i < node->t - 1; ++i) {
        if (node->keys[i].ciudad_destino == destino){
            Piloto* piloto = arbolPilotos->getPiloto(arbolPilotos->root, node->keys[i].vuelo);
            if (piloto != nullptr) if(getCelda(piloto) == nullptr) insertarPiloto(piloto);
        }
    }
    for (size_t i = 0; i < node->t; ++i) {
        if (!node->leaf) {
            existeAvion(node->C[i], destino);
        }
    }
}
void MatrizDispersa::insertarDestino(Lugar* destino){ //Columna
    if(getColumna(destino->nombre) != nullptr) return;
    if(arbolAviones->root == nullptr) return;
    if(!existeAvion(arbolAviones->root, destino->nombre)) return;
    cout << "Destino paso" << endl;
    Celda* colActual = head;
    Celda* colNueva = new Celda();
    colNueva->destino = destino;
    while(colActual != nullptr){
        if(colActual->derecha == nullptr || colActual->derecha->destino->nombre > colNueva->destino->nombre){
            colNueva->derecha = colActual->derecha;
            if(colActual->derecha != nullptr) colActual->derecha->arriba = colNueva;
            colActual->derecha = colNueva;
            colNueva->arriba = colActual;
            colNueva->columna = colActual->columna + 1;
            colActual = colNueva->derecha;
            while(colActual != nullptr){
                colActual->columna++;
                colActual = colActual->derecha;   
            }
            break;
        }
        colActual = colActual->derecha;
    }
    insertarAvion(arbolAviones->root, destino->nombre);
    cout << "Insertado destino: " << destino->nombre << endl;
}
void MatrizDispersa::eliminarDestino(Lugar* destino){
    Celda* colActual = getColumna(destino->nombre);
    if(colActual == nullptr) return;
    Celda* colAux = colActual->abajo;
    while(colAux != nullptr) eliminarPiloto(colAux->piloto);
}
void MatrizDispersa::insertarCelda(Celda* fila, Celda* columna, Celda* celda){
    while(fila != nullptr){
        if(fila->columna == celda->columna){
            celda->derecha = fila->derecha;
            fila->derecha = celda;
            celda->izquierda = fila;
            celda->derecha->izquierda = celda;
            break;
        }
        fila = fila->derecha;
    }
    while(columna != nullptr){
        if(columna->fila == celda->fila){
            celda->abajo = columna->abajo;
            columna->abajo = celda;
            celda->arriba = columna;
            celda->abajo->arriba = celda;
            break;
        }
        columna = columna->abajo;
    }
}

Celda* MatrizDispersa::getFila(string vuelo){
    Celda* filActual = head->abajo;
    while(filActual != nullptr){
        if(filActual->vuelo->vuelo == vuelo) break;
        filActual = filActual->abajo;
    }
    return filActual;
}
Celda* MatrizDispersa::getColumna(string destino){
    Celda* colActual = head->derecha;
    while(colActual != nullptr){
        if(colActual->destino->nombre == destino) break;
        colActual = colActual->derecha;
    }
    return colActual;
}
Celda* MatrizDispersa::getCelda(Piloto* piloto){
    Celda* filActual = getFila(piloto->vuelo);
    if (filActual == nullptr) return nullptr;
    Celda* colActual = getColumna(filActual->vuelo->ciudad_destino);
    if(colActual == nullptr) return nullptr;
    while(filActual != nullptr){
        if(filActual->columna == colActual->columna) break;
        filActual = filActual->derecha;
    }
    return filActual;
}

void MatrizDispersa::exportToDOT(const string& archivo){
    std::ofstream file(archivo);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << archivo << " para escribir." << std::endl;
        return;
    }

    file << "digraph Matriz {\n";
    file << "node [shape=box]\n";
    if (head->derecha != nullptr) {
        Celda* filActual = head;
        string nodo1, nodo2, nodos = "", conexion = "";
        while(filActual != nullptr){
            cout << "leyendo " << filActual->fila << ", " << filActual->columna << endl;
            file << "rank=same {";
            Celda* colActual = filActual;
            while(colActual != nullptr){
                nodo1 = "n" + to_string(colActual->fila) + "_" + to_string(colActual->columna);
                if(colActual->columna == 0 && colActual->fila == 0)
                    nodos += nodo1 + "[label=\"RAIZ\"]\n";
                else if(colActual->columna == 0)
                    nodos += nodo1 + "[label=\"" + colActual->vuelo->vuelo + "\"]\n";
                else if(colActual->fila == 0)
                    nodos += nodo1 + "[label=\"" + colActual->destino->nombre + "\"]\n";
                else
                    nodos += nodo1 + "[label=\"" + colActual->piloto->numero_de_id + "\"]\n";
                file << nodo1 << " ";
                if(colActual->derecha != nullptr){
                    file << " -> ";
                    nodo2 = "n" + to_string(colActual->derecha->fila) + "_" + to_string(colActual->derecha->columna);
                    conexion += nodo2 + " -> " + nodo1 + "\n";
                }
                if(colActual->abajo != nullptr){
                    nodo2 = "n" + to_string(colActual->abajo->fila) + "_" + to_string(colActual->abajo->columna);
                    conexion += nodo1 + " -> " + nodo2 + "\n";
                    conexion += nodo2 + " -> " + nodo1 + "\n";
                }
                colActual = colActual->derecha;
            }
            file << "}\n";
            filActual = filActual->abajo;
        }
        file << conexion << "\n";
        file << nodos << "\n";
    }
    file << "}\n";
    file.close();
}