#include "editorial.h"

#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

//========================
//       NODO
//========================

Nodo::Nodo(Pedido p, Nodo *sig)
{
    dato = p;
    siguiente = sig;
}

//========================
//        PILA
//========================

Pila::Pila()
{
    cima = nullptr;
}

Pila::~Pila()
{
    while (!esVacia())
        desapilar();
}

bool Pila::esVacia()
{
    return cima == nullptr;
}

void Pila::apilar(Pedido p)
{
    Nodo *nuevo = new Nodo(p, cima);
    cima = nuevo;
}

Pedido Pila::desapilar()
{
    Pedido p{};
    if (!esVacia())
    {
        Nodo *aux = cima;
        p = aux->dato;
        cima = aux->siguiente;
        delete aux;
    }
    return p;
}

void Pila::mostrar()
{
    if (esVacia())
    {
        cout << "Pila vacía" << endl;
    }
    else
    {
        cout << "Contenido de la pila:" << endl;
        Nodo *aux = cima;
        while (aux)
        {
            cout << "ID Editorial: " << aux->dato.id_editorial << endl;
            cout << "ID Pedido:    " << aux->dato.id_pedido << endl;
            cout << "Código Libro: " << aux->dato.cod_libro << endl;
            cout << "Materia:      " << aux->dato.materia << endl;
            cout << "Unidades:     " << aux->dato.unidades << endl;
            cout << "Estado:       " << aux->dato.estado << endl;
            cout << "---------------------------" << endl;
            aux = aux->siguiente;
        }
    }
}

//========================
//         COLA
//========================

Cola::Cola()
{
    primero = nullptr;
    ultimo = nullptr;
}

Cola::~Cola()
{
    while (!esVacia())
        desencolar();
}

void Cola::encolar(Pedido p)
{
    Nodo *nuevo = new Nodo(p);
    if (esVacia())
    {
        primero = nuevo;
        ultimo = nuevo;
    }
    else
    {
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }
}

Pedido Cola::desencolar()
{
    Pedido p{};
    if (!esVacia())
    {
        Nodo *aux = primero;
        p = aux->dato;
        if (primero == ultimo)
        {
            primero = nullptr;
            ultimo = nullptr;
        }
        else
        {
            primero = primero->siguiente;
        }
        delete aux;
    }
    return p;
}

bool Cola::esVacia()
{
    return primero == nullptr;
}

void Cola::mostrar()
{
    if (esVacia())
    {
        cout << "Cola vacía" << endl;
    }
    else
    {
        cout << "Contenido de la cola:" << endl;
        Nodo *aux = primero;
        while (aux)
        {
            cout << "ID Editorial: " << aux->dato.id_editorial << endl;
            cout << "ID Pedido:    " << aux->dato.id_pedido << endl;
            cout << "Código Libro: " << aux->dato.cod_libro << endl;
            cout << "Materia:      " << aux->dato.materia << endl;
            cout << "Unidades:     " << aux->dato.unidades << endl;
            cout << "Estado:       " << aux->dato.estado << endl;
            cout << "---------------------------" << endl;
            aux = aux->siguiente;
        }
    }
}
// Muestra el menú principal al usuario
void mostrar_menu()
{
    cout << "\n=========================================================" << endl;
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

//========================
//        OPCIÓN 1
//========================


// Cola global para guardar los pedidos
std::queue<Pedido> cola_pedidos;

// Genera un código aleatorio de 6 caracteres alfanuméricos
string generarCodigo()
{
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string code = "";
    for (int i = 0; i < 6; i++)
        code += chars[rand() % chars.size()];
    return code;
}

// Genera una materia aleatoria
string generarMateria()
{
    string materias[] = {"Tecnologia", "Historia", "Musica", "Arte", "Matematicas", "Ciencias"};
    return materias[rand() % 6];
}


// Genera y muestra n pedidos aleatorios
void generar_pedidos(int n_pedidos)
{
    srand(time(nullptr));

    cout << "QIniciado:" << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << left << setw(6) << "Lib"
         << setw(10) << "Id"
         << setw(10) << "Codigo"
         << setw(15) << "Materia"
         << setw(5) << "U"
         << setw(10) << "Estado     |" << endl;
    cout << "----------------------------------------------------------" << endl;

    for (int i = 0; i < n_pedidos; i++)
    {
        Pedido p;
        p.id_editorial = rand() % 5 + 1;
        p.id_pedido = "P" + to_string(20000 + rand() % 99999);
        p.cod_libro = generarCodigo();
        p.materia = generarMateria();
        p.unidades = rand() % 20 + 1;
        p.estado = "Iniciado";

        // Guardar en la cola
        cola_pedidos.push(p);

        // Mostrar en pantalla
        cout << left << setw(6) << p.id_editorial
             << setw(10) << p.id_pedido
             << setw(10) << p.cod_libro
             << setw(15) << p.materia
             << setw(5) << p.unidades
             << setw(10) << p.estado << " |" << endl;
    }
}

//========================
//        OPCIÓN 2
//========================






//========================
//        OPCIÓN 3
//========================


void mostrar_estado_sistema(queue<Pedido> cola_original)
{
    if (cola_original.empty())
    {
        cout << "\n[ERROR] No existe ningun pedido actualmente";
    }
    else
    {
        cout << "\n\n\n----------------------------------------------------------" << endl;
        cout << left << setw(6) << "Lib"
             << setw(10) << "Id"
             << setw(10) << "Codigo"
             << setw(15) << "Materia"
             << setw(5) << "U"
             << setw(10) << "Estado     |" << endl;
        cout << "----------------------------------------------------------" << endl;

        while (!cola_original.empty())
        {
            Pedido p = cola_original.front();
            cola_original.pop();

            cout << left << setw(6) << p.id_editorial
                 << setw(10) << p.id_pedido
                 << setw(10) << p.cod_libro
                 << setw(15) << p.materia
                 << setw(5) << p.unidades
                 << setw(10) << p.estado << " |" << endl;
        }
    }
    cout << "\n\n\n" << endl;
}

