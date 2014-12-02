#ifndef __IMAGEN2D_H
#define __IMAGEN2D_H
#include <vector>
#include <deque>
#include <list>
#include "Intensidad.h"
#include "Arbol.h"

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
    int getColumna();
    std::vector<std::vector<int> >* getImagen();
    void setFila(int tam);
    void setColumna(int tam);
    void setImagen(std::vector<std::vector<int> >* nuevo);
    std::string getFormato();
    void setFormato(std::string nuevo);
    void imprimirImagen();
    void exportarImagen(char* nom_arch);
    bool exportarHuffman(char* nom_arch);
    std::vector<Arbol<Intensidad> >* calcularListaIntensidades();
    Intensidad* buscarIntensidad(Intensidad* intensidad, std::deque<Intensidad>* lista);
    bool cargarHuffman(char* nombreArchivo);
    bool cargarArchivo(char* nombre);
};
#include "Imagen2D.hxx"
#endif
