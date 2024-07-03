#include "../menu.h"

void cargarPilotos() {
    string filePath;
    cout << "Ingrese el path del archivo JSON de los pilotos: ";
    cin >> filePath;
    
    ifstream inFile(filePath);
    if (!inFile) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return;
    }
    json pilotosJson;
    inFile >> pilotosJson;

    for (auto& piloto : pilotosJson) {
        Piloto p;
        p.nombre = piloto["nombre"];
        p.nacionalidad = piloto["nacionalidad"];
        p.numero_de_id = piloto["numero_de_id"];
        p.vuelo = piloto["vuelo"];
        p.horas_de_vuelo = piloto["horas_de_vuelo"];
        p.tipo_de_licencia = piloto["tipo_de_licencia"];
        arbolPilotos->root = arbolPilotos->insert(arbolPilotos->root, p);
        hashPilotos.insert(p);
        cout << "El piloto " << p.nombre << " se ha registrado." << endl;
        matrizDispersa->insertarPiloto(&p);
    }

    cout << "Pilotos cargados exitosamente." << endl;
}
