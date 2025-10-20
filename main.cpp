#include "editorial.h"

#include <iostream>
#include <string>
#include <queue>

using namespace std;


/**
 * @brief Función principal que ejecuta el simulador.
 */
int main()
{
    Editorial miEditorial; // 1. ¡Creamos el objeto! El constructor se ejecuta aquí.
    int opcion;

    do {
        mostrar_menu();

        // Manejo robusto de la entrada para evitar errores
        if (!(cin >> opcion)) {
            cout << "\n[ERROR] Entrada no valida. Por favor, introduzca un numero.\n\n\n" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = -1;
        }

        switch (opcion) {
            case 1:
                int n_pedidos;
                cout << "Introduzca el numero de pedidos a generar: ";
                cin >> n_pedidos;
                miEditorial.generarPedidos(n_pedidos); // 2. Llamamos al MÉTODO del objeto
                break;
            case 2:
                miEditorial.ejecutarPasoSimulacion();
                break;
            case 3:
                miEditorial.mostrarEstadoSistema(); // 3. Llamamos al MÉTODO del objeto
                break;
            case 4:
                int id_lib;
                cout << "Introduzca el ID de la libreria (0 a " << LIBRERIAS - 1 << "): ";
                cin >> id_lib;
                miEditorial.verContenidoCaja(id_lib);
                break;
            case 0:
                cout << "\nSaliendo del simulador...\n";
                break;
            default:
                cout << "\n[ERROR] Opcion no valida.\n";
                break;
        }
    } while (opcion != 0);

    return 0;
}



