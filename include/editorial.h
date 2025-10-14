#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// ===================================
// 1. CONSTANTES DE CONFIGURACIÓN (#define)
// ===================================

#define MAX_PEDIDOS_CAJA 5         // Número máximo de pedidos que admite una caja [cite: 23]
#define MAX_LIBROS_STOCK 50        // Stock inicial máximo para generar aleatoriamente
#define NUM_TIPOS_LIBROS 5         // Número de títulos de libros diferentes
#define MAX_UNIDADES_PEDIDO 10     // Unidades máximas que se pueden solicitar en un pedido [cite: 14]
#define NUM_LIBRERIAS 3            // Número de librerías diferentes

// Códigos de estado del pedido [cite: 15]
#define ESTADO_INICIADO "Iniciado"
#define ESTADO_ALMACEN "Almacén"
#define ESTADO_IMPRENTA "Imprenta"
#define ESTADO_LISTO "Listo"
#define ESTADO_CAJA "Caja"


// ===================================
// 2. ESTRUCTURA DE DATOS PARA EL PEDIDO
// ===================================

/**
 * @brief Representa un pedido realizado por una librería a la editorial.
 * Campos: id_editorial, id_pedido, cod_libro, materia, unidades y estado.
 */
struct Pedido {
    int id_editorial;
    int id_pedido;
    std::string cod_libro;
    std::string materia;
    int unidades;
    std::string estado; // Puede ser: Iniciado, Almacén, Imprenta, Listo, Caja [cite: 15]
};


// ===================================
// 3. ESTRUCTURAS DINÁMICAS (NODO, COLA, PILA)
// ===================================

/**
 * @brief Nodo genérico para las estructuras enlazadas (Cola y Pila).
 */
struct Nodo {
    Pedido datos;
    Nodo* siguiente;
};

/**
 * @brief TAD Cola (Queue) implementado dinámicamente.
 * Usado para las fases del flujo de pedidos. [cite: 35]
 */
struct Cola {
    Nodo* frente;
    Nodo* final;
};

/**
 * @brief TAD Pila (Stack) implementado dinámicamente.
 * Usado para modelar el contenido de las cajas de pedidos. [cite: 35]
 */
struct Pila {
    Nodo* cima;
    int contador; // Para llevar el control de MAX_PEDIDOS_CAJA
};

/**
 * @brief Estructura para el control de stock (Elección del alumno ).
 * Se usará un array simple de structs para este ejemplo.
 */
struct StockLibro {
    std::string cod_libro;
    int stock_actual;
};


// ===================================
// 4. CLASE PRINCIPAL DE SIMULACIÓN (EDITORIAL)
// ===================================

class Editorial {
private:
    // Colas de las FASES de procesamiento [cite: 35]
    Cola cola_iniciado;
    Cola cola_almacen;
    Cola cola_imprenta;
    Cola cola_listo;

    // Pilas de Cajas (Una por librería) [cite: 22, 23, 35]
    // Se usa un array de pilas para las librerías
    Pila cajas_librerias[NUM_LIBRERIAS];

    // Estructura de control de Stock
    StockLibro stock[NUM_TIPOS_LIBROS];

    // Contadores y IDs
    int id_pedido_global;

    // Prototipos de funciones privadas (Gestión de TADs)
    void inicializar_cola(Cola& c);
    void encolar(Cola& c, Pedido p);
    Pedido desencolar(Cola& c);
    bool cola_vacia(const Cola& c) const;

    void inicializar_pila(Pila& p);
    void apilar(Pila& p, Pedido pd);
    Pedido desapilar(Pila& p);
    bool pila_llena(const Pila& p) const;
    bool pila_vacia(const Pila& p) const;

    // Función para generar un pedido con datos aleatorios [cite: 39]
    Pedido generar_pedido_aleatorio();

    // Función para simular la comprobación de stock y el paso de fase
    void procesar_almacen(Pedido& pedido);

    // Función para simular la impresión
    void procesar_imprenta(Pedido& pedido);

public:
    Editorial();
    ~Editorial();

    // Funciones del Menú del Simulador [cite: 27, 28, 29, 30]
    void generar_pedidos(int n);
    void ejecutar_paso_simulacion();
    void mostrar_estado_sistema() const;
    void ver_contenido_caja(int id_libreria) const;
    void mostrar_menu() const;
};

#endif // EDITORIAL_H
