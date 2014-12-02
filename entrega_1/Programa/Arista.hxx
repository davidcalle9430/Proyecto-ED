#include "Arista.h"
#include <iostream>
using namespace std;
template<class T>
bool Arista<T>::operator<(Arista<T>const a)const
     {

     return ((*getFinArista())<*(a.getFinArista()));
     }


template<class T>
Arista<T>::Arista()
{
     finArista= NULL;
     valor=0;
}

template<class T>
Arista<T>::Arista(int pContenido, Vertice<T>* nuevo)
{
    valor= pContenido;
    finArista=nuevo;
}
template<class T>
Vertice<T>* Arista<T>::getFinArista()const
{
    return finArista;
}
template<class T>
 void Arista<T>::setFinArista(Vertice<T>* vertice)
 {
     finArista=vertice;
 }

template<class T>
int Arista<T>::getValor(){
return valor;
}

template<class T>
void Arista<T>::setValor(int val){
 valor=val;
}
