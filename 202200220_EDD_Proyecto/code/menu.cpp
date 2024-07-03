#include "menu.h"

void mostrarMenu() {
    cout << "-----MENU-----" << endl;
    cout << "1. Carga de aviones" << endl;
    cout << "2. Carga de pilotos" << endl;
    cout << "3. Carga de rutas" << endl;
    cout << "4. Carga de movimientos" << endl;
    cout << "5. Consulta de horas de vuelo (pilotos)" << endl;
    cout << "6. Recomendar ruta" << endl;
    cout << "7. Visualizar reportes" << endl;
    cout << "8. Salir" << endl;
}

int main() {
    string opcion;

    do {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        if (opcion.size() != 1) opcion = "0";
        switch(opcion[0]) {
            case '1':
                cargarAviones();
                break;
            case '2':
                cargarPilotos();
                break;
            case '3':
                cargarRutas();
                break;
            case '4':
                cargarMovimientos();
                break;
            case '5':
                consultarHorasVuelo();
                break;
            case '6':
                recomendarRuta();
                break;
            case '7':
                visualizarReportes();
                break;
            case '8':
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida. Por favor, seleccione una opcion valida." << endl;
        }

        cout << endl;
    } while(opcion[0] != '8');

    return 0;
}
