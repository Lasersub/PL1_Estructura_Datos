#include "editorial.h"

// Usamos el namespace std para evitar prefijar cout, endl, string, etc.
using namespace std;

// Variables est�ticas para los datos de ejemplo
static const string CODIGOS_LIBRO[] = {"MAT1ESO", "LEN2ESO", "FIS3ESO", "QUI4ESO", "BIO4ESO"};
static const string MATERIAS[] = {"Matematicas", "Lengua", "Fisica", "Quimica", "Biologia"};


// ===================================
// 1. GESTI�N DE COLAS (TAD)
// ===================================

void Editorial::inicializar_cola(Cola& c) {
    c.frente = nullptr;
    c.final = nullptr;
}

bool Editorial::cola_vacia(const Cola& c) const {
    return c.frente == nullptr;
}

void Editorial::encolar(Cola& c, Pedido p) {
    Nodo* nuevo = new Nodo;
    nuevo->datos = p;
    nuevo->siguiente = nullptr;

    if (cola_vacia(c)) {
        c.frente = nuevo;
    } else {
        c.final->siguiente = nuevo;
    }
    c.final = nuevo;
}

Pedido Editorial::desencolar(Cola& c) {
    if (cola_vacia(c)) {
        // Devolver un Pedido vac�o en caso de error
        return Pedido();
    }

    Nodo* a_borrar = c.frente;
    Pedido pedido_desencolado = a_borrar->datos;
    c.frente = c.frente->siguiente;

    if (c.frente == nullptr) {
        c.final = nullptr;
    }
    delete a_borrar;
    return pedido_desencolado;
}


// ===================================
// 2. GESTI�N DE PILAS (TAD)
// ===================================

void Editorial::inicializar_pila(Pila& p) {
    p.cima = nullptr;
    p.contador = 0;
}

bool Editorial::pila_vacia(const Pila& p) const {
    return p.cima == nullptr;
}

bool Editorial::pila_llena(const Pila& p) const {
    return p.contador >= MAX_PEDIDOS_CAJA;
}

void Editorial::apilar(Pila& p, Pedido pd) {
    if (pila_llena(p)) {
        cout << "[ERROR] La caja de la librer�a est� llena. No se apila el pedido " << pd.id_pedido << "." << endl;
        return;
    }

    Nodo* nuevo = new Nodo;
    nuevo->datos = pd;
    nuevo->siguiente = p.cima;
    p.cima = nuevo;
    p.contador++;
}

Pedido Editorial::desapilar(Pila& p) {
    if (pila_vacia(p)) {
        return Pedido();
    }

    Nodo* a_borrar = p.cima;
    Pedido pedido_desapilado = a_borrar->datos;
    p.cima = p.cima->siguiente;
    p.contador--;
    delete a_borrar;
    return pedido_desapilado;
}


// ===================================
// 3. L�GICA DE LA EDITORIAL
// ===================================

Editorial::Editorial() : id_pedido_global(1) {
    // Inicializar seed para n�meros aleatorios
    srand(time(0));

    // Inicializar Colas
    inicializar_cola(cola_iniciado);
    inicializar_cola(cola_almacen);
    inicializar_cola(cola_imprenta);
    inicializar_cola(cola_listo);

    // Inicializar Pilas (Cajas)
    for (int i = 0; i < NUM_LIBRERIAS; ++i) {
        inicializar_pila(cajas_librerias[i]);
    }

    // Inicializar Stock (inventario inicial)
    for (int i = 0; i < NUM_TIPOS_LIBROS; ++i) {
        stock[i].cod_libro = CODIGOS_LIBRO[i];
        stock[i].stock_actual = rand() % MAX_LIBROS_STOCK + 10;
    }
}

Editorial::~Editorial() {
    // Implementaci�n pendiente: Liberar memoria din�mica
    cout << "Sistema de pedidos finalizado." << endl;
}

/**
 * @brief Genera un pedido con datos aleatorios.
 */
Pedido Editorial::generar_pedido_aleatorio() {
    Pedido p;
    p.id_editorial = rand() % NUM_LIBRERIAS + 1;
    p.id_pedido = id_pedido_global++;

    int idx = rand() % NUM_TIPOS_LIBROS;
    p.cod_libro = CODIGOS_LIBRO[idx];
    p.materia = MATERIAS[idx];
    p.unidades = rand() % MAX_UNIDADES_PEDIDO + 1;
    p.estado = ESTADO_INICIADO;

    return p;
}

/**
 * @brief Funci�n del Men�: Genera N pedidos aleatorios.
 */
void Editorial::generar_pedidos(int n) {
    cout << "\n--- Generando " << n << " pedidos aleatorios ---" << endl;
    for (int i = 0; i < n; ++i) {
        Pedido nuevo = generar_pedido_aleatorio();
        encolar(cola_iniciado, nuevo);
        cout << "  Pedido #" << nuevo.id_pedido << " de Librer�a " << nuevo.id_editorial
                  << " (" << nuevo.cod_libro << ", " << nuevo.unidades << "u) generado en: "
                  << nuevo.estado << "" << endl;
    }
}

/**
 * @brief Simula la comprobaci�n de stock y el paso de fase.
 */
void Editorial::procesar_almacen(Pedido& pedido) {
    bool stock_suficiente = false;
    for (int i = 0; i < NUM_TIPOS_LIBROS; ++i) {
        if (stock[i].cod_libro == pedido.cod_libro) {
            if (stock[i].stock_actual >= pedido.unidades) {
                stock[i].stock_actual -= pedido.unidades;
                stock_suficiente = true;
            }
            break;
        }
    }

    if (stock_suficiente) {
        pedido.estado = ESTADO_LISTO;
        encolar(cola_listo, pedido);
        cout << "  -> Stock SUFICIENTE. Pedido #" << pedido.id_pedido << " pasa a: " << pedido.estado << "" << endl;
    } else {
        pedido.estado = ESTADO_IMPRENTA;
        encolar(cola_imprenta, pedido);
        cout << "  -> Stock INSUFICIENTE. Pedido #" << pedido.id_pedido << " pasa a: " << pedido.estado << "" << endl;
    }
}

/**
 * @brief Simula el proceso de impresi�n.
 */
void Editorial::procesar_imprenta(Pedido& pedido) {
    // Simulaci�n: Imprimir un lote para cubrir la demanda
    for (int i = 0; i < NUM_TIPOS_LIBROS; ++i) {
        if (stock[i].cod_libro == pedido.cod_libro) {
            stock[i].stock_actual += 50 - pedido.unidades; // Lote de 50 - unidades solicitadas
            break;
        }
    }

    pedido.estado = ESTADO_LISTO;
    encolar(cola_listo, pedido);
    cout << "  -> Impresi�n FINALIZADA. Pedido #" << pedido.id_pedido << " pasa a: " << pedido.estado << "" << endl;
}


/**
 * @brief Funci�n del Men�: Ejecuta un paso de simulaci�n (una fase).
 */
void Editorial::ejecutar_paso_simulacion() {
    cout << "\n--- EJECUTANDO PASO DE SIMULACI�N ---" << endl;

    // FASE 1: Iniciado -> Almac�n
    if (!cola_vacia(cola_iniciado)) {
        Pedido p = desencolar(cola_iniciado);
        p.estado = ESTADO_ALMACEN;
        encolar(cola_almacen, p);
        cout << "  Pedido #" << p.id_pedido << " pasa de: Iniciado a: " << p.estado << "" << endl;
    }
    // FASE 2: Almac�n -> Listo o Almac�n -> Imprenta
    else if (!cola_vacia(cola_almacen)) {
        Pedido p = desencolar(cola_almacen);
        cout << "  Pedido #" << p.id_pedido << " en Almac�n. Comprobando stock..." << endl;
        procesar_almacen(p);
    }
    // FASE 3: Imprenta -> Listo
    else if (!cola_vacia(cola_imprenta)) {
        Pedido p = desencolar(cola_imprenta);
        cout << "  Pedido #" << p.id_pedido << " en Imprenta. Simulaci�n de impresi�n..." << endl;
        procesar_imprenta(p);
    }
    // FASE 4: Listo -> Caja
    else if (!cola_vacia(cola_listo)) {
        Pedido p = desencolar(cola_listo);
        int id_lib = p.id_editorial - 1;

        if (!pila_llena(cajas_librerias[id_lib])) {
            p.estado = ESTADO_CAJA;
            apilar(cajas_librerias[id_lib], p);
            cout << "  Pedido #" << p.id_pedido << " pasa de: Listo a: " << p.estado
                      << " (Caja Librer�a " << p.id_editorial << ")" << endl;
        } else {
            // La caja est� llena, simular env�o vaciando la pila
            cout << "  Caja de Librer�a " << p.id_editorial << " llena (" << MAX_PEDIDOS_CAJA << " pedidos)." << endl;
            // Primero, vaciamos la caja para simular el env�o
            while(!pila_vacia(cajas_librerias[id_lib])) {
                desapilar(cajas_librerias[id_lib]);
            }
            cout << "  *** Caja de Librer�a " << p.id_editorial << " ENVIADA y vac�a. ***" << endl;

            // Luego, el pedido actual pasa a la nueva caja (pila reci�n vaciada)
            p.estado = ESTADO_CAJA;
            apilar(cajas_librerias[id_lib], p);
            cout << "  Pedido #" << p.id_pedido << " pasa a la nueva caja (" << p.id_editorial << ")." << endl;
        }
    }
    else {
        cout << "  No hay pedidos en ninguna fase para procesar." << endl;
    }
}

/**
 * @brief Funci�n del Men�: Muestra el estado actual del sistema (colas y stock).
 */
void Editorial::mostrar_estado_sistema() const {
    cout << "\n--- ESTADO ACTUAL DEL SISTEMA ---" << endl;

    // Estado de las Colas
    cout << ">> Colas de Procesamiento:" << endl;
    cout << "  - Iniciado: " << (cola_vacia(cola_iniciado) ? "Vacia" : "Con pedidos") << endl;
    cout << "  - Almac�n: " << (cola_vacia(cola_almacen) ? "Vacia" : "Con pedidos") << endl;
    cout << "  - Imprenta: " << (cola_vacia(cola_imprenta) ? "Vacia" : "Con pedidos") << endl;
    cout << "  - Listo: " << (cola_vacia(cola_listo) ? "Vacia" : "Con pedidos") << endl;

    // Estado de las Cajas (Pilas)
    cout << "\n>> Cajas de Env�o (Pilas):" << endl;
    for (int i = 0; i < NUM_LIBRERIAS; ++i) {
        cout << "  - Caja Librer�a " << i + 1 << ": " << cajas_librerias[i].contador << "/" << MAX_PEDIDOS_CAJA << " pedidos";
        if (pila_llena(cajas_librerias[i])) {
            cout << " (LISTA PARA ENVIAR)";
        }
        cout << endl;
    }

    // Estado del Stock
    cout << "\n>> Stock Actual (Almac�n):" << endl;
    for (int i = 0; i < NUM_TIPOS_LIBROS; ++i) {
        cout << "  - [" << stock[i].cod_libro << "]: " << stock[i].stock_actual << " unidades" << endl;
    }
}

/**
 * @brief Funci�n del Men�: Muestra el contenido de una caja (Pila) de una librer�a.
 */
void Editorial::ver_contenido_caja(int id_libreria) const {
    if (id_libreria < 1 || id_libreria > NUM_LIBRERIAS) {
        cout << "[ERROR] ID de librer�a no v�lido. Debe estar entre 1 y " << NUM_LIBRERIAS << "." << endl;
        return;
    }

    int idx = id_libreria - 1;
    const Pila& caja = cajas_librerias[idx];

    cout << "\n--- CONTENIDO DE LA CAJA DE LIBRER�A " << id_libreria << " (" << caja.contador << "/" << MAX_PEDIDOS_CAJA << ") ---" << endl;

    if (pila_vacia(caja)) {
        cout << "  La caja est� vac�a." << endl;
        return;
    }

    // Recorrer la pila sin modificarla
    Nodo* actual = caja.cima;
    int pos = caja.contador; // Mostrar la posici�n LIFO (�ltimo en entrar = 1)
    while (actual != nullptr) {
        cout << "  [" << pos-- << "] Pedido #" << actual->datos.id_pedido
                  << " (" << actual->datos.cod_libro << ", " << actual->datos.unidades << "u)" << endl;
        actual = actual->siguiente;
    }
    cout << "  (Posici�n 1 es el �ltimo pedido apilado/primero en ser enviado)" << endl;
}

/**
 * @brief Muestra el men� de la simulaci�n.
 */
void Editorial::mostrar_menu() const {
    cout << "\n=======================================================" << endl;
    cout << "  PR�CTICA 1 - SIMULACI�N DE PEDIDOS EN EDITORIAL" << endl;
    cout << "=======================================================" << endl;
    cout << "1. Generar N pedidos aleatorios." << endl;
    cout << "2. Ejecutar un paso de simulaci�n (una fase)." << endl;
    cout << "3. Mostrar el estado del sistema." << endl;
    cout << "4. Ver el contenido de una caja de una librer�a." << endl;
    cout << "0. Salir del programa." << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "Seleccione una opci�n: ";
}
// COMENTARIO
