#include "editorial.h"


using namespace std;


//========================
//    GESTIÓN DE PILAS
//========================

NodoPila::NodoPila()
{
    valor=0;
    siguiente=NULL;
    //ctor
}

NodoPila::NodoPila(int v, NodoPila *sig)
{
    valor = v;
    siguiente = sig;
}

NodoPila::~NodoPila()
{
    //dtor
}


Pila::Pila()
{
    cima = NULL;
}

Pila::~Pila()
{
    while(cima) desapilar();
}

bool Pila::esVacia()
{
    return cima == NULL;
}

void Pila::apilar(int v)
{
    pnodo nuevo = new NodoPila(v,cima);
    //comienzo de la pila nevo nodo
    cima = nuevo;
}

void Pila::desapilar()
{
    pnodo nodo; //puntero aux para manipular el nodo
    if(cima)
    {
        nodo = cima;
        cima = nodo->siguiente;
        delete nodo;
    }
}

int Pila::mostrar()
{
    if(esVacia())
    {
        cout << "Pila vacia"<<endl;
    }
    else
    {
        cout << "Cima pila: "<< cima->valor<<endl;
    }
    return 0;
}


//========================
//    GESTIÓN DE COLAS
//========================

NodoCola::NodoCola()
{
    elemento='0';
    siguiente=NULL;
//constructor por defecto
}
NodoCola::NodoCola(char e, NodoCola*sig )
{
    elemento = e;
    siguiente = sig;
}
NodoCola::~NodoCola()
{
//dtor
}


Cola::Cola()
{
    primero = NULL;
    ultimo = NULL;
    longitud = 0;
}
Cola::~Cola() { }
void Cola::encolar(char elemento)
{
    NodoCola *nuevo_nodo = new
    NodoCola(elemento);
    if(es_vacia())
    {
        primero = nuevo_nodo;
        ultimo = nuevo_nodo;
    }
    else
    {
        ultimo->siguiente = nuevo_nodo;
        ultimo = nuevo_nodo;
    }
    longitud++;
}

char Cola::desencolar()
{
    if(!es_vacia())
    {
        char elemento = primero->elemento;
        NodoCola *aux = primero;
        if((primero == ultimo) && (primero->siguiente == NULL))
        {
            primero = NULL;
            ultimo = NULL;
            aux->siguiente = NULL;
            delete(aux);
        }
        else
        {
            primero = primero->siguiente;
            aux->siguiente = NULL;
            delete(aux);
        }
        longitud--;
        return elemento;
    }
}
char Cola::inicio()
{
    if(!es_vacia())
    {
        return primero->elemento;
    }
}
char Cola::fin()
{
    if(!es_vacia())
    {
        return ultimo->elemento;
    }
}
int Cola::get_longitud()
{
    return longitud;
}
bool Cola::es_vacia()
{
    return ((primero == NULL) && (ultimo ==
                                  NULL));
}
void Cola::mostrarCola()
{
    NodoCola *aux = primero;
    if (es_vacia())
    {
        cout<<"Cola Vacía: "<<endl;
    }
    else
    {
        cout<<"Datos de la Cola: "<<endl;
        while (aux)
        {
            cout << aux->elemento<<endl;
            aux = aux->siguiente;
        }
    }
}

// COMENTARIO
