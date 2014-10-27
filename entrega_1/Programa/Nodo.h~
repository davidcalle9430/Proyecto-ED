#ifndef NODO_H
#define NODO_H

template<class T>
class Nodo
{   private:
    T contenido;
    Nodo<T>* hijoIzquierdo;
    Nodo<T>* hijoDerecho;

    public:
        Nodo();

        T getContenido()const;
       void setContenido(T nuevo);
       Nodo(T variable);
       Nodo<T>* getHijoIzquierdo();
       Nodo<T>* getHijoDerecho();
       void setHijoIzquierdo(Nodo<T>* nuevo);
       void setHijoDerecho(Nodo<T>* nuevo);
       bool esHoja();


};
#include "Nodo.hxx"
#endif // NODO_H
