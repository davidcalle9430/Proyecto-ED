#include "Arbol.h"
#include <fstream>
#include "Nodo.h"
using namespace std;
template<class T>
Arbol<T>::Arbol()
{
    cabeza=NULL;
}
template<class T>
Nodo<T>* Arbol<T>::getCabeza()const
{
    return cabeza;
}
template<class T>
void Arbol<T>::setCabeza(Nodo<T>* nuevo)
{
    cabeza=nuevo;
}

template<class T>
void Arbol<T>::eliminarArbol(Nodo<T>* cabez)
{
    if(cabez!=NULL)
    {
        if(cabez->getHijoDerecho()!=NULL)
        {
            eliminarArbol(cabez->getHijoDerecho());
        }
        if(cabez->getHijoIzquierdo()!=NULL)
        {
            eliminarArbol(cabez->getHijoIzquierdo());
        }
        delete cabez;
    }
}
template<class T>
void Arbol<T>::eliminar(){
if(cabeza!=NULL){
cabeza->eliminar();
}
}

template<class T>
bool Arbol<T>::operator<(const Arbol<T>& arbol)const{
          if(cabeza->getContenido()<(arbol.getCabeza()->getContenido())){
            return true;
          }
          return false;
        }

