#include "Intensidad.h"
using namespace std;
Intensidad::Intensidad(){

}
Intensidad::Intensidad(int pValor, int pFrecuencia){
  valor=pValor;
  frecuencia=pFrecuencia;
}
const int Intensidad::getValor()const{
  return valor;
}
void Intensidad::setValor(int pValor){
  valor=pValor;
}
const int Intensidad::getFrecuencia() const{
  return valor;
}
void Intensidad::setFrecuencia(int pValor){
 frecuencia=pValor;
}
