#ifndef __ARISTA_H
#define __ARISTA_H
#include <vector>
#include "Vertice.h"
template<class T>
class Arista{

private:
    //hubiera sido mejor poner un vertice
    int valor;
    /* falta cambiar el valor por un vertice*/
    Vertice<T>* finArista;
public:
     Arista();
     Arista(int contenido, Vertice<T>* nuevo);
     Vertice<T>* getFinArista()const;
     int getValor();
     void agregarArista(Vertice<T>* vertice);
     void setValor(int val);
     void setFinArista(Vertice<T>* vertice);
     bool operator<(Arista<T>const a)const;


};
#include "Arista.hxx"
#endif

