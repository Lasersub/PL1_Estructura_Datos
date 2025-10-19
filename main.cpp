#include "editorial.h"

using namespace std;

// Muestra el men� al usuario
void mostrar_menu()
{
    cout << "\n=======================================================" << endl;
    cout << "   SIMULACION DE PEDIDOS EN EDITORIAL" << endl;
    cout << "=========================================================" << endl;
    cout << "1. Generar N pedidos aleatorios" << endl;
    cout << "2. Ejecutar un paso de simulacion" << endl;
    cout << "3. Mostrar el estado del sistema" << endl;
    cout << "4. Ver el contenido de una caja de una libreria" << endl;
    cout << "0. Salir del programa" << endl;
    cout << "=========================================================" << endl;
    cout << "Seleccione una opcion: ";
}

/**
 * @brief Funci�n principal que ejecuta el simulador.
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
            cout << "[ERROR] Entrada no v�lida. Por favor, introduzca un n�mero." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = -1;
        }

        switch (opcion) {
            case 1: // Generar N pedidos aleatorios
                cout << "Introduzca el n�mero de pedidos a generar: ";
                break;
            case 2: // Ejecutar un paso de simulaci�n (una fase)
                break;
            case 3: // Mostrar el estado del sistema
                break;
            case 4: // Ver el contenido de una caja de una librer�a
                cout << "Introduzca el ID de la librer�a (1 a " << "NUM_LIBRERIAS" << "): ";
                break;
            case 0: // Salir del programa
                cout << "Saliendo del simulador. �Adi�s nigger!" << endl;
                break;
            default:
                if (opcion != -1) // Si el error no vino del manejo de la entrada
                    cout << "[ERROR] Opci�n no v�lida. Int�ntelo de nuevo." << endl;
                break;
        }
    } while (opcion != 0);

    return 0;
}



