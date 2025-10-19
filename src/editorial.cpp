#include "editorial.h"
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

