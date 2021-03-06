#ifndef __REGION_H
#define __REGION_H

class Region{
 private:
     int x;
     int y;
     int color;
     int identificador;
     int colorNuevo;
 public:
    
     Region(int x,int y, int color, int id);
     Region();
     int getColor();
     int getX();
     int getY();
     int getColorNuevo();
     int getIdentificador()const;
     void setColor(int pColor);
     void setColorNuevo(int pColorN);
     void setX(int pX);
     void setY(int pY);
     void setIdentificador(int pId);
     bool operator==(const Region &r)const;
};
#include "Region.hxx"
#endif

