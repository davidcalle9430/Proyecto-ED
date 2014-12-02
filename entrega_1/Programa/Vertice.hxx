#include "Vertice.h"
template<class T>
Vertice<T>::Vertice()
{

}
template<class T>
Vertice<T>::Vertice(T pContenido)
{
    contenido=pContenido;

}
template<class T>
T Vertice<T>::getContenido()const
{
    return contenido;
}
template<class T>
void Vertice<T>::setContenido(T pContenido)
{
    contenido=pContenido;
}
template<class T>
bool Vertice<T>::operator<(Vertice<T>const &a)const
     {

     return (getContenido()<a.getContenido());
     }

/*template<class T>
T Vertice<T>::getPeso()
{
    return peso;
}
template<class T>
void Vertice<T>::setPeso(T pContenido)
{
    peso=pContenido;
}
*/
