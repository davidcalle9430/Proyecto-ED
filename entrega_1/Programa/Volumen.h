#ifndef __VOLUMEN_H
#define __VOLUMEN_H
#include <vector>
#include "Imagen2D.h"
class Volumen
{
private:
    std::vector<Imagen2D>* imagenes;
    int tamanio;

public:
    Volumen();
    Volumen(char* nombreBase, int total);
    int getTamanio();
    void setTamanio(int tam);
    vector<Imagen2D>* getImagenes();

    //PROMEDIOS
    Imagen2D* proyeccionXPromedio();
    Imagen2D* proyeccionYPromedio();
    Imagen2D* proyeccionZPromedio();
    //MEDIANAS
    Imagen2D* proyeccionXMediana();
    Imagen2D* proyeccionYMediana();
    Imagen2D* proyeccionZMediana();
    //MAXIMOS
    Imagen2D* proyeccionXMaximo();
    Imagen2D* proyeccionYMaximo();
    Imagen2D* proyeccionZMaximo();
    //MINIMO
    Imagen2D* proyeccionXMinimo();
    Imagen2D* proyeccionYMinimo();
    Imagen2D* proyeccionZMinimo();





};
#include "Volumen.hxx"
#endif
