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

// Array del catalogo de libros disponibles
void Editorial::inicializarCatalogo() {

    // MATEMÁTICAS (2 libros)
    catalogo[0] = {"101A23", "Matematicas", 120};
    catalogo[1] = {"102B24", "Matematicas", 90};

    // FÍSICA (1 libro)
    catalogo[2] = {"211C15", "Fisica", 80};

    // TECNOLOGÍA (2 libros)
    catalogo[3] = {"341D99", "Tecnologia", 75};
    catalogo[4] = {"342E01", "Tecnologia", 100};

    // MÚSICA (1 libro)
    catalogo[5] = {"401F45", "Musica", 60};

    // HISTORIA (3 libros)
    catalogo[6] = {"511G76", "Historia", 150};
    catalogo[7] = {"512H88", "Historia", 110};
    catalogo[8] = {"513I91", "Historia", 95};

    // LENGUA (3 libros)
    catalogo[9] = {"601J10", "Lengua", 200};
    catalogo[10] = {"602K11", "Lengua", 180};
    catalogo[11] = {"603L12", "Lengua", 160};
}

int Editorial::buscarLibro(std::string cod_libro) {
    for (int i = 0; i < MAX_TITULOS; i++) {
        if (catalogo[i].cod_libro == cod_libro) {
            return i; // Devuelve el índice si lo encuentra
        }
    }
    return -1; // Devuelve -1 si no lo encuentra
}

// Vacía una caja cuando se llena (simula el envío)
void Editorial::procesarCaja(int id_libreria) {
    std::cout << "\n==> ¡Caja para libreria " << id_libreria << " llena! Se envia y se vacia. <==" << std::endl;
    while (!cajas[id_libreria].esVacia()) {
        cajas[id_libreria].desapilar();
    }
}


void Editorial::generarPedidos(int n) {
    for (int i = 0; i < n; i++) {
        Pedido p;

        // 1. ID de librería: aleatorio entre 0 y LIBRERIAS-1.
        p.id_editorial = rand() % LIBRERIAS;

        // 2. ID de pedido: Único y secuencial, no aleatorio.
        p.id_pedido = "P" + std::to_string(ultimoIdPedido++);

        // 3. Libro: Se elige uno aleatorio del catálogo existente.
        int libro_idx = rand() % MAX_TITULOS; // MAX_TITULOS es 12 en nuestro caso
        p.cod_libro = catalogo[libro_idx].cod_libro;
        p.materia   = catalogo[libro_idx].materia;

        // 4. Unidades: Un número aleatorio.
        p.unidades = rand() % 30 + 5; // Por ejemplo, entre 5 y 34 libros

        // 5. Estado: Siempre "Iniciado" al crearse.
        p.estado = "Iniciado";

        // 6. Encolar el pedido en la primera cola del sistema.
        colaIniciado.encolar(p);
    }

    // (Opcional) Mensaje de confirmación al usuario.
    std::cout << n << " Pedidos nuevos generados y en la cola 'Iniciado'." << std::endl;
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
        // Colas para clasificar los pedidos por estado
        queue<Pedido> q_iniciado;
        queue<Pedido> q_almacen;
        queue<Pedido> q_imprenta;
        queue<Pedido> q_listo;

        // Clasificar los pedidos según su estado
        while (!cola_original.empty())
        {
            Pedido p = cola_original.front();
            cola_original.pop();

            if (p.estado == "Iniciado")
                q_iniciado.push(p);
            else if (p.estado == "Almacen")
                q_almacen.push(p);
            else if (p.estado == "Imprenta")
                q_imprenta.push(p);
            else if (p.estado == "Listo")
                q_listo.push(p);
        }

        cout << "\n\nQIniciado" << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << left << setw(6) << "Lib"
             << setw(10) << "Id"
             << setw(10) << "Codigo"
             << setw(15) << "Materia"
             << setw(5) << "U"
             << setw(10) << "Estado     |" << endl;
        cout << "----------------------------------------------------------" << endl;

        if (q_iniciado.empty())
        {
            cout << "(Vacia)" << endl;
        }

        while (!q_iniciado.empty())
        {
            Pedido p = q_iniciado.front();
            q_iniciado.pop();
            cout << left << setw(6) << p.id_editorial
                 << setw(10) << p.id_pedido
                 << setw(10) << p.cod_libro
                 << setw(15) << p.materia
                 << setw(5) << p.unidades
                 << setw(10) << p.estado << " |" << endl;
        }

        cout << "\n\nQAlmacen" << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << left << setw(6) << "Lib"
             << setw(10) << "Id"
             << setw(10) << "Codigo"
             << setw(15) << "Materia"
             << setw(5) << "U"
             << setw(10) << "Estado     |" << endl;
        cout << "----------------------------------------------------------" << endl;

        if (q_almacen.empty())
        {
            cout << "(Vacia)" << endl;
        }

        while (!q_almacen.empty())
        {
            Pedido p = q_almacen.front();
            q_almacen.pop();
            cout << left << setw(6) << p.id_editorial
                 << setw(10) << p.id_pedido
                 << setw(10) << p.cod_libro
                 << setw(15) << p.materia
                 << setw(5) << p.unidades
                 << setw(10) << p.estado << " |" << endl;
        }

        cout << "\n\nQImprenta" << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << left << setw(6) << "Lib"
             << setw(10) << "Id"
             << setw(10) << "Codigo"
             << setw(15) << "Materia"
             << setw(5) << "U"
             << setw(10) << "Estado     |" << endl;
        cout << "----------------------------------------------------------" << endl;

        if (q_imprenta.empty())
        {
            cout << "(Vacia)" << endl;
        }

        while (!q_imprenta.empty())
        {
            Pedido p = q_imprenta.front();
            q_imprenta.pop();
            cout << left << setw(6) << p.id_editorial
                 << setw(10) << p.id_pedido
                 << setw(10) << p.cod_libro
                 << setw(15) << p.materia
                 << setw(5) << p.unidades
                 << setw(10) << p.estado << " |" << endl;
        }

        cout << "\n\nQListo" << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << left << setw(6) << "Lib"
             << setw(10) << "Id"
             << setw(10) << "Codigo"
             << setw(15) << "Materia"
             << setw(5) << "U"
             << setw(10) << "Estado     |" << endl;
        cout << "----------------------------------------------------------" << endl;

        if (q_listo.empty())
        {
            cout << "(Vacia)" << endl;
        }

        while (!q_listo.empty())
        {
            Pedido p = q_listo.front();
            q_listo.pop();
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

