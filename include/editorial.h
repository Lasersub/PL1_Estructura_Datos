#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <iostream>
#include <string>

//Struct pedido que define la clase central que sera el pedido
struct Pedido {
    int id_editorial;
    std::string id_pedido;
    std::string cod_libro;
    std::string materia;
    int unidades;
    std::string estado;
};


// Un solo Nodo que almacena un Pedido. Asi no tenemos que hacer NodoPila y NodoCola ya que seria redundancia
class Nodo
{
private:
    Pedido dato;
    Nodo *siguiente;

    // Es friend
    friend class Pila;
    friend class Cola;

public:
    // El constructor ahora recibe un Pedido
    Nodo(Pedido p, Nodo *sig = NULL);
};


class Pila
{
private:
    Nodo *cima; // Usamos nuestro Nodo genérico
public:
    Pila();
    ~Pila();
    bool esVacia();
    void apilar(Pedido p); // Recibe un Pedido
    Pedido desapilar(); // Devuelve un Pedido
    void mostrar(); // Modificado para mostrar pedidos
};


class Cola
{
private:
    Nodo *primero; // Usamos nuestro Nodo genérico
    Nodo *ultimo;
public:
    Cola();
    ~Cola();
    void encolar(Pedido p); // Recibe un Pedido
    Pedido desencolar(); // Devuelve un Pedido
    bool esVacia(); // Renombrado de 'es_vacia' para consistencia
    void mostrar();
};


// --- Funciones auxiliares ---

void mostrar_menu();

void generar_pedidos(int n_pedidos)();
#endif // EDITORIAL_H
