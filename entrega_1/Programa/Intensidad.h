#ifndef INTENSIDAD_H
#define INTENSIDAD_H
class Intensidad{
private:
  int valor;
  int frecuencia;
public:
    bool operator <(const Intensidad& in)const{
 if(frecuencia==in.getFrecuencia()){
    return valor<in.getValor();
 }
   return frecuencia<in.getFrecuencia();
  }
  Intensidad();
  Intensidad(int pValor, int pFrecuencia);
  int getValor()const;
  void setValor(int pValor);
  int getFrecuencia()const;
  void setFrecuencia(int pFrecuencia);



};
#include "Intensidad.hxx"
#endif
