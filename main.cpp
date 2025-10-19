#include "editorial.h"

using namespace std;

// Muestra el menú al usuario
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
 * @brief Función principal que ejecuta el simulador.
 */
int main()
{
    mostrar_menu();

    return 0;
}



