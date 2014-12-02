#ifndef __Casa_H
#define __Casa_H
#include <math.h>
class Casa{
private:
int identificador;
int x;
int y;
public:
	Casa();
	Casa(int pX, int pY, int pId);
	int getX();
	int getY();
	int getIdentificador()const;
	void setX(int pX);
    void setY(int pY);
    void setIdentificador(int pId);
    int calcularDistancia(Casa casa);
    bool operator==(Casa const &casa)const;
    bool operator<(Casa const &casa)const;

};
#include "Casa.hxx"
#endif
