#ifndef INTENSIDAD_H
#define INTENSIDAD_H
class Intensidad{
private:
  int valor;
  int frecuencia;
public:
  Intensidad();
  Intensidad(int pValor, int pFrecuencia);
  int getValor();
  void setValor(int nuevo);
  int getFrecuencia();
  void setFrecuencia(int valor);
  bool operator <(const Intensidad& in)const{
  
  
  int a=frecuencia;
  int b=in.getFrecuencia();
    
   return a<b;
  }
  bool operator ==(const Intensidad& i)const{
    return getValor()==i.getValor();
  }
};
#include "Intensidad.hxx"
#endif
