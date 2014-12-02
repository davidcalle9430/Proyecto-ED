#ifndef __VERTICE_H
#define __VERTICE_H
template<class T>
class Vertice
{
private:
    T contenido;
    //T peso;
public:
    Vertice();
    Vertice(T pContenido);
    T getContenido()const;
    void setContenido(T nuevo);
    T getPeso();
    void setPeso(T nuevo);
    bool operator<(Vertice<T>const &a)const;
  };
#include "Vertice.hxx"
#endif
