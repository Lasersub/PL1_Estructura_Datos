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
    int opcion;
    int n_pedidos;
    int id_lib;

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
            case 1: // Generar N pedidos aleatorios
                cout << "Introduzca el numero de pedidos a generar: ";
                if (!(cin >> n_pedidos) || n_pedidos <= 0) {
                    cout << "\n[ERROR] Numero de pedidos no valido.\n\n\n" << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                } else {
                    cout << "\n\n\nGenerados " << n_pedidos << " en QIniciado\n" << endl;
                    generar_pedidos(n_pedidos);
                    cout << "\nPedidos en la cola: " << cola_pedidos.size() <<  "\n\n\n" << endl;
                }
                break;
            case 2: // Ejecutar un paso de simulación (una fase)
                break;
            case 3: // Mostrar el estado del sistema
                    mostrar_estado_sistema(cola_pedidos);
                break;
            case 4: // Ver el contenido de una caja de una librería
                cout << "Introduzca el ID de la librería (1 a " << "NUM_LIBRERIAS" << "): ";
                break;
            case 0: // Salir del programa
                cout << "\n\n\nSaliendo del simulador. SYBAU nigger!\n\n\n" << endl;
                break;
            default:
                if (opcion != -1) // Si el error no vino del manejo de la entrada
                    cout << "\n[ERROR] Opcion no valida. Intentelo de nuevo.\n\n\n" << endl;
                break;
        }
    } while (opcion != 0);

    return 0;
}



