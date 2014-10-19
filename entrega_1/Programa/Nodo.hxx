#include "Nodo.h"
template<class T>
Nodo<T>::Nodo()
{
 hijoDerecho=NULL;
 hijoIzquierdo=NULL;
}
template<class T>
Nodo<T>::Nodo(T variable)
{
  contenido=variable;
 hijoDerecho=NULL;
 hijoIzquierdo=NULL;
}

template<class T>
T Nodo<T>::getContenido()const{
   
return contenido;
}
template<class T>
bool Nodo<T>::esHoja(){
return (getHijoIzquierdo()==NULL&&getHijoDerecho()==NULL);
}

template<class T>
void Nodo<T>::setContenido(T nuevo){
 contenido=nuevo;
}

template<class T>
void Nodo<T>::setHijoIzquierdo(Nodo<T>* nuevo){
 hijoIzquierdo=nuevo;
}

template<class T>
void Nodo<T>::setHijoDerecho(Nodo<T>* nuevo){
 hijoDerecho=nuevo;
}
template<class T>
Nodo<T>* Nodo<T>::getHijoIzquierdo(){
return  hijoIzquierdo;
}
template<class T>
Nodo<T>* Nodo<T>::getHijoDerecho(){
return  hijoDerecho;
}
