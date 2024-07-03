#include "../menu.h"

void consultarHorasVuelo() {
    string opcion;
    do{
        cout << "-----SELECCIONE EL RECORRIDO-----" << endl;
        cout << "1. Preorden" << endl;
        cout << "2. Inorder" << endl;
        cout << "3. Postorden" << endl;
        cout << "4. Regresar" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        if (opcion.size() != 1) opcion = "0";
        switch(opcion[0]) {
            case '1':
                arbolPilotos->preOrder(arbolPilotos->root);
                break;
            case '2':
                arbolPilotos->inOrder(arbolPilotos->root);
                break;
            case '3':
                arbolPilotos->postOrder(arbolPilotos->root);
                break;
            case '4':
                cout << "Saliendo del menu..." << endl;
                break;
            default:
                cout << "Opcion invalida. Por favor, seleccione una opcion valida." << endl;
        }
    } while(opcion[0] != '4');
}
