#include "Intensidad.h"
using namespace std;
Intensidad::Intensidad(){

}
Intensidad::Intensidad(int pValor, int pFrecuencia){
  valor=pValor;
  frecuencia=pFrecuencia;
}
int Intensidad::getValor()const{
  return valor;
}
void Intensidad::setValor(int pValor){
  valor=pValor;
}

int Intensidad::getFrecuencia() const{
  return valor;
}
void Intensidad::setFrecuencia(int pValor){
 frecuencia=pValor;
}
