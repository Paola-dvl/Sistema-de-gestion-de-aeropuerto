#include "../menu.h"

void cargarRutas() {
    string filePath;
    cout << "Ingrese el path del archivo TXT de las rutas: ";
    cin >> filePath;
    
    ifstream inFile(filePath);
    if (!inFile) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(inFile, linea)) {
        string lugar, destino, distanciaStr;
        stringstream ss(linea);
        getline(ss, lugar, '/');
        getline(ss, destino, '/');
        ss >> distanciaStr;
        int distancia = stoi(distanciaStr);
        if (lugar == destino) cout << "ERROR!!! El lugar de origen y el destino no pueden ser iguales";
        else{
            grafoRutas->insertarLugarDestino(lugar, destino, distancia);
            Lugar* l = grafoRutas->buscarLugar(lugar);
            matrizDispersa->insertarDestino(l);
        }
    }
}
