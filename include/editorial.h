#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <iostream>
#include <string>

struct Pedido {
    int id_editorial;
    std::string id_pedido;
    std::string cod_libro;
    std::string materia;
    int unidades;
    std::string estado;
};

class NodoPila{
private:
    int valor;
    NodoPila *siguiente;
    friend class Pila;
public:
    NodoPila();
    NodoPila(int v, NodoPila *sig = NULL);
    ~NodoPila();
};

typedef NodoPila *pnodo;


class Pila
{
private:
    pnodo cima;
public:
    Pila();
    ~Pila();
    bool esVacia();
    void apilar(int v);
    void desapilar();
    int mostrar();
};

class NodoCola
{
    friend class Cola;
private:
    NodoCola *siguiente;
    char elemento;
public:
    NodoCola();
    NodoCola(char e, NodoCola*sig = NULL);
    ~NodoCola();
};


class Cola
{
private:
    NodoCola * primero;
    NodoCola * ultimo;
    int longitud;
public:
    Cola();
    ~Cola();
    void encolar(char);
    char inicio();
    char fin();
    char desencolar();
    bool es_vacia();
    void mostrarCola(); //No es correcto, se implementa para ver que está creada correctamente
};

#endif EDITORIAL_H

