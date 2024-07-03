#include "../menu.h"

void recomendarRuta() {
    string origen, destino, opcion;
    do{
        cout << "Ingrese el origen: ";
        cin >> origen;
        cout << "Ingrese el destino: ";
        cin >> destino;
        Lugar* l1 = grafoRutas->buscarLugar(origen);
        Lugar* l2 = grafoRutas->buscarLugar(destino);
        if (l1 == nullptr) cout << "ERROR!!! El origen no existe." << endl;
        else if (l2 == nullptr) cout << "ERROR!!! El destino no existe." << endl;
        else{
            cout << "Calculando ruta..." << endl;
            grafoRutas->visitados[grafoRutas->indice] = {0};
            grafoRutas->mejorRuta.distancia = INT_MAX;
            Ruta ruta = grafoRutas->encontrarRuta(l1, l2);
            if(ruta.distancia == INT_MAX) cout << "ERROR!!! No se encontró una ruta." << endl;
            else cout << "Ruta: " << ruta.ruta << "\nDistancia: " << ruta.distancia << endl;
        }
        cout << "-----RECORRIDO-----" << endl;
        cout << "1. Recomendar otra ruta" << endl;
        cout << "2. Regresar" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        if (opcion.size() != 1) opcion = "0";
        switch(opcion[0]) {
            case '1':
                arbolPilotos->preOrder(arbolPilotos->root);
                break;
            case '2':
                cout << "Saliendo del menu..." << endl;
                break;
            default:
                cout << "Opcion invalida. Por favor, seleccione una opcion valida." << endl;
        }
    } while(opcion[0] != '2');
}
