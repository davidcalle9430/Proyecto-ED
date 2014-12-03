#include "Region.h"

Region ::Region(int Cox,int Coy, int Ccolor, int id)
{
    x=Cox;
    y=Coy;
    color=Ccolor;
    identificador=id;
    colorNuevo=-1;
}
Region::Region()
{

}
 bool Region::operator==(const Region &r)const
     {
       return r.getIdentificador()==identificador;
     }

int Region::getX()
{
    return x;
}
int Region::getY()
{
    return y;
}
int Region::getColor()
{
    return color;
}
int Region::getColorNuevo()
{
    return colorNuevo;
}
int Region::getIdentificador()const
{
    return identificador;
}
void Region::setX(int pX)
{
    x=pX;
}
void Region::setY(int pY)
{
    y=pY;
}
void Region::setColor(int pColor)
{
    color=pColor;
}
void Region::setColorNuevo(int pColorN)
{  
    colorNuevo=pColorN;
   
}
void Region::setIdentificador(int pId)
{
    identificador=pId;
}


