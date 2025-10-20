#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <iostream>
#include <string>
#include <queue>


// ===================================
//     CONSTANTES DE CONFIGURACIÓN
// ===================================

#define MAX_TITULOS 12          // Nº de títulos diferentes en el catálogo (usamos 12 como decidimos)
#define N_PEDIDOS_PASO 12       // Nº de pedidos procesados por fase en cada paso de simulación
#define TAM_LOTE 10             // Incremento de stock desde la imprenta
#define LIBRERIAS 6             // Nº de librerías que realizan pedidos
#define CAP_CAJA 5              // Nº de pedidos por caja antes de enviar

#define ESTADO_INICIADO "Iniciado"
#define ESTADO_ALMACEN "Almacén"
#define ESTADO_IMPRENTA "Imprenta" // Códigos de estado del pedido
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
//              LIBRO
// ===================================

struct Libro {
    std::string cod_libro;
    std::string materia;
    int stock;
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
    void mostrarConFormatoDeTabla();
};

// ===================================
//     CLASE PRINCIPAL DEL SISTEMA
// ===================================

class Editorial {
private:
    // Colas para cada fase del proceso
    Cola colaIniciado;
    Cola colaAlmacen;
    Cola colaImprenta;
    Cola colaListo;

    // Un array de Pilas, donde cada pila es una caja para una librería
    Pila cajas[LIBRERIAS];

    // Almacén de libros (nuestro catálogo)
    Libro catalogo[MAX_TITULOS]; // MAX_TITULOS lo definimos en 12

    // Variable para generar IDs de pedido únicos
    int ultimoIdPedido;

    // --- Métodos privados (ayudantes internos) ---
    void inicializarCatalogo();
    int buscarLibro(std::string cod_libro);
    void procesarCaja(int id_libreria);

public:
    // --- Métodos públicos (la interfaz del programa) ---
    Editorial(); // Constructor: se ejecuta al crear el objeto
    ~Editorial(); // Destructor: se ejecuta al destruir el objeto

    // Funciones que se corresponden con el menú de opciones
    void generarPedidos(int n);
    void ejecutarPasoSimulacion();
    void mostrarEstadoSistema();
    void verContenidoCaja(int id_libreria);
    void mostrarPedidosGenerados();
};



// ===================================
//        FUNCIONES AUXILIARES
// ===================================

// Muestra el menú al usuario
void mostrar_menu();

#endif // EDITORIAL_H
