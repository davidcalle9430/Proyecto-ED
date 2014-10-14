#ifndef __IMAGEN2D_H
#define __IMAGEN2D_H
#include <vector>
#include <list>
#include "Intensidad.h"
class Imagen2D
{
private:
    std::vector<std::vector<int> >* imagen;
    std::string formato;
    int fila;
    int columna;
public:
    Imagen2D();
    Imagen2D(char* nombre);
    int getFila();
    void setFila(int tam);
    int getColumna();
    void setColumna(int tam);
    std::vector<std::vector<int> >* getImagen();
    void setImagen(std::vector<std::vector<int> >* nuevo);
    std::string getFormato();
    void setFormato(std::string nuevo);
    void imprimirImagen();
    void exportarImagen(char* nom_arch);
    std::list<Intensidad>* calcularListaIntensidades();
    Intensidad* buscarIntensidad(Intensidad* intensidad, std::list<Intensidad>* lista);

};
#include "Imagen2D.hxx"
#endif
