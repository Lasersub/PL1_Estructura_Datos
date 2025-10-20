#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <iostream>
#include <string>
#include <queue>


// ===================================
//     CONSTANTES DE CONFIGURACI�N
// ===================================

#define MAX_PEDIDOS_CAJA 5         // N�mero m�ximo de pedidos que admite una caja
#define MAX_LIBROS_STOCK 50        // Stock inicial m�ximo para generar aleatoriamente
#define NUM_TIPOS_LIBROS 5         // N�mero de t�tulos de libros diferentes
#define MAX_UNIDADES_PEDIDO 10     // Unidades m�ximas que se pueden solicitar en un pedido
#define NUM_LIBRERIAS 3            // N�mero de librer�as diferentes

#define ESTADO_INICIADO "Iniciado"
#define ESTADO_ALMACEN "Almac�n"
#define ESTADO_IMPRENTA "Imprenta" // C�digos de estado del pedido
#define ESTADO_LISTO "Listo"
#define ESTADO_CAJA "Caja"


using namespace std;


// ===================================
//              PEDIDO
// ===================================

struct Pedido {
    int id_editorial;
    std::string id_pedido;
    std::string cod_libro;
    std::string materia;
    int unidades;
    std::string estado;
};


// ===================================
//          NODO, PILA Y COLA
// ===================================

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
    Nodo *cima; // Usamos nuestro Nodo gen�rico
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
    Nodo *primero; // Usamos nuestro Nodo gen�rico
    Nodo *ultimo;
public:
    Cola();
    ~Cola();
    void encolar(Pedido p); // Recibe un Pedido
    Pedido desencolar(); // Devuelve un Pedido
    bool esVacia(); // Renombrado de 'es_vacia' para consistencia
    void mostrar();
};


// Cola global
extern std::queue<Pedido> cola_pedidos;


// ===================================
//        FUNCIONES AUXILIARES
// ===================================

// Muestra el men� al usuario
void mostrar_menu();

// Genera pedidos aleatorios en la Opci�n 1
void generar_pedidos(int n_pedidos);

// Muestra el estado del sistema en la Opci�n 3
void mostrar_estado_sistema(queue<Pedido> cola_pedidos);




#endif // EDITORIAL_H
