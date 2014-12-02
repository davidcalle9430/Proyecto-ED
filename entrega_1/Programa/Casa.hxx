#include "Casa.h"
#include <math.h>
Casa::Casa(){


}
Casa::Casa(int pX, int pY, int pId){
 x=pX;
 y=pY;
 identificador=pId;
}
 bool Casa::operator==(Casa const &casa)const{
     // cout<<"comparando a "<<identificador<<" y "<<casa.getIdentificador()<<endl;
         return identificador==casa.getIdentificador();
    };
 bool Casa::operator<(Casa const &casa)const{
         return identificador<casa.getIdentificador();
    };
 int Casa::calcularDistancia(Casa casa){
  int xMax= max(x, casa.getX());
  int yMax= max(y, casa.getY());
  int xMin= min(x, casa.getX());
  int yMin= min(y, casa.getY());
  int cx= xMax-xMin;
  int cy= yMax-yMin;
  int xCuadrado=cx*cx;
  int yCuadrado=cy*cy;
  return (int)sqrt(xCuadrado+yCuadrado);

}
int Casa::getX(){
	return x;
}
int Casa::getY(){
	return y;
}
int Casa::getIdentificador()const{
	return identificador;
}
void Casa::setX(int pX){
 x=pX;
}
void Casa::setY(int pY){
 y=pY;
}
void Casa::setIdentificador(int pId){
 identificador=pId;
}
