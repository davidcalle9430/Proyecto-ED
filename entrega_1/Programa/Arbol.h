#ifndef ARBOL_H
#define ARBOL_H
#include "Nodo.h"
#include <cstddef>
template<class T>
class Arbol
{


  private:
  Nodo<T>* cabeza;
  public:
        Arbol();
        Nodo<T>* getCabeza()const;
        void setCabeza(Nodo<T>* nuevo);
        void eliminarArbol(Nodo<T>* cabeza);
        bool operator <(const Arbol<T>& arbol)const;
        void eliminar();
};
#include "Arbol.hxx"
#endif // ARBOL_H
