#include "Imagen2D.h"
#include <string>
#include <list>
#include "cstring"
#include "Intensidad.h"
using namespace std;


void Imagen2D::imprimirImagen()
{

    for (int i=0; i<(*(imagen)).size (); i++)
    {


        for (int j=0; j<(*(imagen))[i].size (); j++)
        {

            cout<<(*(imagen))[i][j]<<" ";
        }
        cout<<endl;
    }

}

Imagen2D::Imagen2D()
{

    imagen= new std::vector<std::vector<int> >();
}
vector<vector<int> >* Imagen2D::getImagen()
{
    return imagen;
}
void Imagen2D::setFormato(std:: string nuevo)
{
    formato=nuevo;

}
void Imagen2D::setImagen(std::vector<std::vector<int> >* nuevo)
{
    imagen=nuevo;

}
std::string Imagen2D::getFormato()
{
    return formato;
}

Imagen2D::Imagen2D(char * nombre)
{
    strcat(nombre,".pgm");

    Imagen2D* nueva= new Imagen2D();
    fstream archivo(nombre);
    if(archivo)
    {

        char* codigo;
        codigo= new char[50];
        archivo.getline(codigo,50);
        int width, height, x;


        archivo>>width;
        archivo>>height;
        archivo>>x;
        vector< vector<int > >* duracion= new vector< vector<int > > (width, vector<int> (height));
//	vector< vector<int > > duracion(width, vector<int> (height));


        for(int i=0; i<height; i++)
        {



            for(int j=0; j<width; j++)
            {

                int temp;
                archivo>>temp;
                (*(duracion))[i][j]=temp;
            }
        }

        vector< vector<int> >* temporal= duracion;
        setImagen(temporal);
        setFila(height);
        setColumna(width);
        std::string p(codigo);
        setFormato(p);




    }
   // cout<<"Archivo "<<nombre<< " cargado satisfactoriamente"<<endl:
    else
    {
        cout<<"El volumen no ha sido cargado en memoria "<<nombre<<endl;

    }
}

int Imagen2D::getFila()
{
    return fila;
}
void Imagen2D::setFila(int tam)
{
    fila=tam;
}
int Imagen2D::getColumna()
{
    return columna;
}
void Imagen2D::setColumna(int tam)
{
    columna=tam;
}
void Imagen2D::exportarImagen(char* nom_arch)
{
    ofstream arch(nom_arch);
    if(arch){
    arch<<"P2"<<endl;
    arch<<fila<<" "<<columna<<endl;
    arch<<"255"<<endl;
    for (int i=0; i<(*(imagen)).size (); i++)
    {

        for (int j=0; j<(*(imagen))[i].size (); j++)
        {

            arch<<(*(imagen))[i][j]<<" ";
        }
        arch<<endl;
    }
        cout<<"La proyeccion 2D del volumen en memoria ha sido generada"<<endl;

    }else{
    cout<<"La proyeccion 2D del volumen en memoria no ha podido ser generada"<<endl;
    }
    arch.close();
}

std::list<Intensidad>* Imagen2D::calcularListaIntensidades(){
  list<Intensidad>* retorno= new list<Intensidad>();
  for(int i=0; i<fila;i++){
    for(int j=0; j<columna;j++){
         int valor=(*(imagen))[i][j];
         Intensidad* temporal= new Intensidad(valor,1);
         Intensidad* busqueda=buscarIntensidad(temporal,retorno);
         if(busqueda!=NULL){
           busqueda->setFrecuencia(busqueda->getFrecuencia()+1);
         }else{
           retorno->push_back(*(temporal));
         }
    }
  }
}

Intensidad* Imagen2D::buscarIntensidad(Intensidad* intensidad, std::list<Intensidad>* lista){
  for(std::list<Intensidad>::iterator i=lista->begin();i!=lista->end();i++){
    if(*i==*intensidad){
      return &(*i);
    }
  }
  return NULL;
}
