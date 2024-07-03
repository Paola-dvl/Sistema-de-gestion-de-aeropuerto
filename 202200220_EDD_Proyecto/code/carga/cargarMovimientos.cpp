#include "../menu.h"

void cargarMovimientos() {
    string filePath;
    cout << "Ingrese el path del archivo TXT de los movimientos: ";
    cin >> filePath;
    
    ifstream inFile(filePath);
    if (!inFile) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(inFile, linea)) {
        stringstream ss(linea);
        string command;
        getline(ss, command, '(');
        if (command == "DarDeBaja") {
            string id;
            getline(ss, id, ')');
            Piloto* piloto = arbolPilotos->getPilotoId(arbolPilotos->root, id);
            if(piloto != nullptr){
                hashPilotos.eliminar(piloto);
                matrizDispersa->eliminarPiloto(piloto);
                arbolPilotos->eliminar(arbolPilotos->root, piloto->numero_de_id);
                cout << "Piloto con id " << id << " dado de baja." << endl;
            } 
            else cout << "ERROR!!! Piloto con id " << id << " no encontrado." << endl;           
        } else{
            stringstream ss_(linea);
            string command;
            getline(ss_, command, ',');
            if (command == "MantenimientoAviones") {
                string accion, id;
                getline(ss_, accion, ',');
                getline(ss_, id, ';');
                if(accion == "Salida"){
                    Avion* avion = nullptr;
                    if(arbolAviones->root != nullptr) arbolAviones->root->getAvionRegistro(id);
                    if(avion != nullptr){
                        arbolAviones->root->remove(id);
                        listaAviones->insertar(*avion);
                        matrizDispersa->eliminarVuelo(avion);
                        cout << "Avion con id " << id << " sacado." << endl;
                    }
                    else cout << "ERROR!!! Avion con id " << id << " no encontrado." << endl;
                }else if (accion == "Ingreso"){
                    Avion* avion = listaAviones->buscarAvion(id);
                    if(avion != nullptr){
                        listaAviones->eliminar(id);
                        arbolAviones->insert(*avion);
                        matrizDispersa->insertarVuelo(avion);
                        cout << "Avion con id " << id << " ingresado." << endl;
                    }
                    else cout << "ERROR!!! Avion con id " << id << " no encontrado." << endl;
                }
            } else {
                cerr << "Comando desconocido: " << command << endl;
            }
        }
    }
}
