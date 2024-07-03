#include "../menu.h"

void cargarAviones() {
    string filePath;
    cout << "Ingrese el path del archivo JSON de los aviones: ";
    cin >> filePath;
    
    ifstream inFile(filePath);
    if (!inFile) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return;
    }
    json avionesJson;
    inFile >> avionesJson;

    for (auto& avion : avionesJson) {
        Avion a;
        a.vuelo = avion["vuelo"];
        a.numero_de_registro = avion["numero_de_registro"];
        a.modelo = avion["modelo"];
        a.capacidad = avion["capacidad"];
        a.aerolinea = avion["aerolinea"];
        a.ciudad_destino = avion["ciudad_destino"];
        a.estado = avion["estado"];

        if (a.estado == "Disponible") {
            arbolAviones->insert(a);
            matrizDispersa->insertarVuelo(&a);
        } else if (a.estado == "Mantenimiento"){
            listaAviones->insertar(a);
        }
    }

    cout << "Aviones cargados exitosamente." << endl;
}
