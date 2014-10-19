#include "Imagen2D.h"
#include <string>
#include <algorithm>
#include <list>
#include <deque>
#include "cstring"
#include "Arbol.h"
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
        cout<<"la altura es: "<<height<<endl;
         cout<<"el ancho  es: "<<width<<endl;

        vector< vector<int > >* duracion= new vector< vector<int > > (height, vector<int> (width));



        for(int i=0; i<height; i++)
        {



            for(int j=0; j<width; j++)
            {

                int temp;
                archivo>>temp;
                (*(duracion))[i][j]=temp;

            }
        }
   cout<<"llega"<<endl;
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
bool comparadora( Intensidad& i, Intensidad& i2){
  return i.getFrecuencia()<i2.getFrecuencia();
}

std::vector<Arbol<Intensidad> >* Imagen2D::calcularListaIntensidades(){
  deque<Intensidad>* retorno= new deque<Intensidad>();
  for(int i=0; i<fila;i++){
    for(int j=0; j<columna;j++){
         int valor=(*(imagen))[i][j];
         Intensidad* temporal= new Intensidad();
         temporal->setValor(valor);
         temporal->setFrecuencia(1);


         Intensidad* busqueda=buscarIntensidad(temporal,retorno);
         if(busqueda!=NULL){
           busqueda->setFrecuencia(busqueda->getFrecuencia()+1);
           /* cout<<" se encuentra la frecuencia de "<<busqueda->getValor()<<" es "<<busqueda->getFrecuencia()<<endl;
            system("pause");
            */
            }else{

           retorno->push_back(*(temporal));
         }
    }
  }
  sort(retorno->begin(), retorno->end());
  //retorno->sort();

  vector<Arbol<Intensidad> >* lista= new vector<Arbol<Intensidad> >();
  int contador=0;
  for(deque<Intensidad>::iterator i=retorno->begin();i!=retorno->end();i++){

    Arbol<Intensidad>* miArbolito= new Arbol<Intensidad>();
 //cout<<"la intensidad es: "<<(*i).getValor()<<" frecuencia: "<<(*i).getFrecuencia()<<endl;
    contador+=(*i).getFrecuencia();
    Nodo<Intensidad>* nodo= new Nodo<Intensidad>(*i);
    miArbolito->setCabeza(nodo);
    lista->push_back(*miArbolito);
  }


  return lista;
}

Arbol<Intensidad>* hoffman(vector<Arbol<Intensidad> >* lista){
 // cout<<"paso tam= "<<lista->size()<<endl;
 //cout<<"el primer elemento es: "<<(*lista)[0].getCabeza()->getContenido().getFrecuencia()<<endl;
  //system("pause");
  while(lista->size()>1){
        sort(lista->begin(), lista->end());
// saco el primero y el segundo
Arbol<Intensidad>* primero= &((*lista)[0]);
Arbol<Intensidad>* segundo=&((*lista)[1]);
Arbol<Intensidad>* nuevon= new Arbol<Intensidad>();
int suma= primero->getCabeza()->getContenido().getFrecuencia()+segundo->getCabeza()->getContenido().getFrecuencia();
Intensidad* nueva= new Intensidad(-1,suma);
Nodo<Intensidad>* nodo= new Nodo<Intensidad>(*nueva);
nuevon->setCabeza(nodo);
nodo->setHijoDerecho(segundo->getCabeza());
nodo->setHijoIzquierdo(primero->getCabeza());
lista->erase(lista->begin());
lista->erase(lista->begin());
lista->push_back(*nuevon);

//cout<<"ahora el tam es: "<<lista->size()<<endl;
  }
  return  &((*lista)[0]);
}

Intensidad* Imagen2D::buscarIntensidad(Intensidad* intensidad, std::deque<Intensidad>* lista){
  for(std::deque<Intensidad>::iterator i=lista->begin();i!=lista->end();i++){
    if((*i).getValor()==(*intensidad).getValor()){
          //  cout<<"se encontro a "<<(*i).getValor()<<" con frecuencia "<<(*i).getFrecuencia()<<endl;
            // system("pause");
      return &(*i);
    }
  }
  return NULL;
}
std::string codificarHoffman(Nodo<Intensidad>* nodo, int valor, std::string cadena){
    if(nodo==NULL){
      return "";
    }
    if(nodo!=NULL&&nodo->getContenido().getValor()==valor){
        return cadena;
    }
     if(nodo!=NULL&&nodo->getHijoIzquierdo()==NULL&&nodo->getHijoIzquierdo()==NULL&&nodo->getContenido().getValor()!=valor){
        return "";
    }
    std::string derecha= codificarHoffman(nodo->getHijoDerecho(),valor,(cadena+"1"));
      std::string izquierda= codificarHoffman(nodo->getHijoIzquierdo(),valor,(cadena+"0"));
    if(derecha!=""){
        return derecha;
    }else{
    return izquierda;
    }
}

void decodificarHuffman(Nodo<Intensidad>* nodo, ifstream& lectura)
{
    int valor;
    int frecuencia;
    lectura>>valor;
    lectura>>frecuencia;
    Intensidad* nueva= new Intensidad(valor, frecuencia);
    nodo->setContenido(*nueva);
    if(valor==-1)
    {
        if(nodo->getHijoIzquierdo()==NULL)
        {
            Nodo<Intensidad>* izq= new Nodo<Intensidad>(*nueva);
            nodo->setHijoIzquierdo(izq);
        }
        decodificarHuffman(nodo->getHijoIzquierdo(),lectura);

        if(nodo->getHijoDerecho()==NULL)
        {
            Nodo<Intensidad>* der= new Nodo<Intensidad>(*nueva);
            nodo->setHijoDerecho(der);

            decodificarHuffman(nodo->getHijoDerecho(),lectura);
        }
    }
}
int decodificarValor(Nodo<Intensidad>* nodo, string codificacion){
    if(codificacion==""){
        return nodo->getContenido().getValor();
    }else{
    if(codificacion[0]=='1'){
            string cpy=codificacion;
    cpy.erase(0,1);
    return decodificarValor(nodo->getHijoDerecho(),cpy);
    }else{
            string cpy=codificacion;
    cpy.erase(0,1);
    return decodificarValor(nodo->getHijoIzquierdo(),cpy);
    }
    }


}
bool Imagen2D::cargarHuffman(char* nombreArchivo){

strcat(nombreArchivo,".huffman");

    Imagen2D* nueva= new Imagen2D();
    ifstream lectura(nombreArchivo);

    if(lectura)
    {

        char* codigo;
        //codigo= new char[50];
        //lectura.getline(codigo,50);
        int width, height, x;



        lectura>>height;
        lectura>>width;
        lectura>>x;
        cout<<"la altura es: "<<height<<endl;
         cout<<"el ancho  es: "<<width<<endl;

         Arbol<Intensidad>* arbol= new Arbol<Intensidad>();
Nodo<Intensidad>* nodo= new Nodo<Intensidad>();
arbol->setCabeza(nodo);

decodificarHuffman(arbol->getCabeza(),lectura);


        vector< vector<int > >* duracion= new vector< vector<int > > (height, vector<int> (width));



        for(int i=0; i<height; i++)
        {



            for(int j=0; j<width; j++)
            {

                string temp;
                lectura>>temp;
                 int val=decodificarValor(arbol->getCabeza(), temp);
                 //cout<<"guardo a "<<temp<<" con deco "<<val<<endl;
                // system("pause");
                (*(duracion))[i][j]= val;

            }
        }

        vector< vector<int> >* temporal= duracion;
           cout<<"meto en la  matriz"<<endl;
        setImagen(temporal);
         cout<<"meto en la  matriz"<<endl;
        setFila(height);
         cout<<"meto en la  matriz"<<endl;
        setColumna(width);
         cout<<"meto en la  matriz"<<endl;
       // std::string p(codigo);
         cout<<"meto en la  matriz"<<endl;
        setFormato("P2");
         cout<<"meto en la  matriz"<<endl;

return true;

}
return false;
}
