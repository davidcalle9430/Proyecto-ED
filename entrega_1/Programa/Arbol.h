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
        Nodo<T>* getCabeza();
        void setCabeza(Nodo<T>* nuevo);
        void eliminarArbol(Nodo<T>* cabeza);




};
#include "Arbol.hxx"
#endif // ARBOL_H
