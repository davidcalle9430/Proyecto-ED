#include "Imagen2D.h"
#include <string>
#include <algorithm>
#include <list>
#include <deque>
#include "cstring"
#include "Grafo.h"

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
bool Imagen2D::cargarArchivo(char* nombre)
{
//strcat(nombre,".pgm");

    Imagen2D* nueva= new Imagen2D();
    fstream archivo(nombre);

    if(archivo)
    {

        char* codigo;
        codigo= new char[50];
        archivo.getline(codigo,50);
        int width, height, x;



        archivo>>height;
         archivo>>width;
        archivo>>x;


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

        vector< vector<int> >* temporal= duracion;
        setImagen(temporal);
        setFila(height);
        setColumna(width);
        std::string p(codigo);
        setFormato(p);



        archivo.close();

        return true;
    }
    else
    {

        setFila(-1);
        setColumna(-1);
        return false;

    }

}
bool validarColores(Grafo<Region>* grafo, vector<int>* colores){

/* para cada uno de los vertices verifico si no hay adyacentes con colores iguales */

    for(int i=0; i<grafo->getListaAristas()->size();i++){
        vector<Arista<Region>* >* adyacentes= grafo->buscarAdyacentes((*grafo->getListaAristas())[i][0]->getFinArista());

        for(int j=1; j<adyacentes->size();j++){
          int pos=grafo->darPosicionVertice((*adyacentes)[j]->getFinArista());
          //cout<<"la posicion del adyancente es"<<pos<<endl;
          if(i!=pos&&(*grafo->getListaAristas())[pos][0]->getFinArista()->getContenido().getColorNuevo()==(*grafo->getListaAristas())[i][0]->getFinArista()->getContenido().getColorNuevo()){

            // cout<<"fin para i: "<<i<<" pos: "<<pos<<" repetido:"<<(*grafo->getListaAristas())[pos][0]->getFinArista()->getContenido().getColorNuevo()<<endl;
            return false;
          }
        }

    }
  /* falta validar que estén todos los colores*/
    bool encontrado=true;
    for(int i=0; i<colores->size()&&encontrado;i++){
        bool pepito=false;
        for(int j=0; j<grafo->getListaAristas()->size();j++){
            if((*colores)[i]==(*grafo->getListaAristas())[j][0]->getFinArista()->getContenido().getColorNuevo()){
                pepito=true;
                j=grafo->getListaAristas()->size();
            }
        }
        if(!pepito){
            return false;
        }
    }

return true;
}
void combinatorioColores(int posicion, bool &valor, Grafo<Region>* grafito, vector<int>* colores){
    if(posicion==grafito->getListaAristas()->size()){

       if(validarColores(grafito,colores)){
        valor=false;
       }

    }else{

     for(int i=0; i<colores->size()&&valor;i++){
       (*grafito->getListaAristas())[posicion][0]->getFinArista()->getContenido().setColorNuevo((*colores)[i]);
       Region r=  (*grafito->getListaAristas())[posicion][0]->getFinArista()->getContenido();
       r.setColorNuevo((*colores)[i]);
       (*grafito->getListaAristas())[posicion][0]->getFinArista()->setContenido(r);
       //cout<<"deberia cambiar a"<<(*colores)[i]<<endl;
       //cout<<"cambio de colores a"<<    (*grafito->getListaAristas())[posicion][0]->getFinArista()->getContenido().getColorNuevo()<<endl;
       combinatorioColores(posicion+1, valor, grafito,colores);
     }
    }

    }
bool colorearGrafo(Grafo <Region> *grafito,int numColores)
{
    int color=255/numColores;
    vector<int>* colores= new vector<int>();
    int contColores=0;
    int conti=0;
    for (int i=color; i<255; i+=color)
    {    int pepito= conti*color;
        int pepito2=pepito+color;
        colores->push_back((pepito2+pepito)/2);
        conti++;
    }

    if(colores->size()<=grafito->getListaAristas()->size()){
        bool retorno=true;
        combinatorioColores(0,retorno, grafito,colores);
        return !retorno;
    }

    else
    {
        return false;
    }
}
void colorearImagen(Grafo<Region>* grafo, Imagen2D* img){
/* Lo que hay que hacer es recorre la imagen, una vez recorrida esta*/
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


        archivo>>height;

        archivo>>width;
        archivo>>x;


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

        vector< vector<int> >* temporal= duracion;
        setImagen(temporal);
        setFila(height);
        setColumna(width);
        std::string p(codigo);
        setFormato(p);



        archivo.close();

        cout<<" Archivo "<<nombre<< " cargado satisfactoriamente"<<endl;

    }
    else
    {

        setFila(-1);
        setColumna(-1);
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
    if(arch)
    {
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

    }
    else
    {
        cout<<"La proyeccion 2D del volumen en memoria no ha podido ser generada"<<endl;
    }
    arch.close();
}
bool comparadora( Intensidad& i, Intensidad& i2)
{
    return i.getFrecuencia()<i2.getFrecuencia();
}

std::vector<Arbol<Intensidad> >* Imagen2D::calcularListaIntensidades()
{
    deque<Intensidad>* retorno= new deque<Intensidad>();
    for(int i=0; i<fila; i++)
    {
        for(int j=0; j<columna; j++)
        {
            int valor=(*(imagen))[i][j];
            Intensidad* temporal= new Intensidad();
            temporal->setValor(valor);
            temporal->setFrecuencia(1);


            Intensidad* busqueda=buscarIntensidad(temporal,retorno);
            if(busqueda!=NULL)
            {
                busqueda->setFrecuencia(busqueda->getFrecuencia()+1);
            }
            else
            {

                retorno->push_back(*(temporal));
            }
        }
    }
    sort(retorno->begin(), retorno->end());


    vector<Arbol<Intensidad> >* lista= new vector<Arbol<Intensidad> >();
    int contador=0;
    for(deque<Intensidad>::iterator i=retorno->begin(); i!=retorno->end(); i++)
    {

        Arbol<Intensidad>* miArbolito= new Arbol<Intensidad>();

        contador+=(*i).getFrecuencia();
        Nodo<Intensidad>* nodo= new Nodo<Intensidad>(*i);
        miArbolito->setCabeza(nodo);
        lista->push_back(*miArbolito);
    }


    return lista;
}

Arbol<Intensidad>* hoffman(vector<Arbol<Intensidad> >* lista)
{


    while(lista->size()>1)
    {
        sort(lista->begin(), lista->end());

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


    }
    return  &((*lista)[0]);
}

Intensidad* Imagen2D::buscarIntensidad(Intensidad* intensidad, std::deque<Intensidad>* lista)
{
    for(std::deque<Intensidad>::iterator i=lista->begin(); i!=lista->end(); i++)
    {
        if((*i).getValor()==(*intensidad).getValor())
        {

            return &(*i);
        }
    }
    return NULL;
}
std::string codificarHoffman(Nodo<Intensidad>* nodo, int valor, std::string cadena)
{
    if(nodo==NULL)
    {
        return "";
    }
    if(nodo!=NULL&&nodo->getContenido().getValor()==valor)
    {
        return cadena;
    }
    if(nodo!=NULL&&nodo->getHijoIzquierdo()==NULL&&nodo->getHijoIzquierdo()==NULL&&nodo->getContenido().getValor()!=valor)
    {
        return "";
    }
    std::string derecha= codificarHoffman(nodo->getHijoDerecho(),valor,(cadena+"1"));
    std::string izquierda= codificarHoffman(nodo->getHijoIzquierdo(),valor,(cadena+"0"));
    if(derecha!="")
    {
        return derecha;
    }
    else
    {
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
int decodificarValor(Nodo<Intensidad>* nodo, string codificacion)
{
    if(codificacion=="")
    {
        return nodo->getContenido().getValor();
    }
    else
    {
        if(codificacion[0]=='1')
        {
            string cpy=codificacion;
            cpy.erase(0,1);
            return decodificarValor(nodo->getHijoDerecho(),cpy);
        }
        else
        {
            string cpy=codificacion;
            cpy.erase(0,1);
            return decodificarValor(nodo->getHijoIzquierdo(),cpy);
        }
    }


}
bool Imagen2D::cargarHuffman(char* nombreArchivo)
{

    // strcat(nombreArchivo,".huffman");

    Imagen2D* nueva= new Imagen2D();

    ifstream lectura(nombreArchivo);

    if(lectura)
    {

        char* codigo;

        int width, height, x;



        lectura>>height;
        lectura>>width;
        lectura>>x;


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

                (*(duracion))[i][j]= val;

            }
        }
        lectura.close();
        vector< vector<int> >* temporal= duracion;

        setImagen(temporal);

        setFila(height);

        setColumna(width);

        // std::string p(codigo);

        setFormato("P2");
        arbol->eliminar();

        return true;

    }



    return false;
}

void preOrden(Nodo<Intensidad>* nodo, ofstream& salida)
{

    if(nodo!=NULL)
    {
        salida<<nodo->getContenido().getValor()<<" "<<nodo->getContenido().getFrecuencia()<<" ";

        preOrden(nodo->getHijoIzquierdo(),salida);
        preOrden(nodo->getHijoDerecho(),salida);

    }

}

std::string codificarValor(Nodo<Intensidad>* nodo, int valor, string retorno)
{
    if(nodo==NULL)
    {
        return "";
    }

    if(nodo!=NULL&&nodo->getContenido().getValor()==valor)
    {
        return retorno;
    }
    else
    {
        std::string izq= retorno+"0";
        std::string der= retorno+"1";
        string izquierdo=codificarValor(nodo->getHijoIzquierdo(), valor, izq);
        string derecho=codificarValor(nodo->getHijoDerecho(), valor, der);
        if(izquierdo!="")
        {
            return izquierdo;
        }
        else
        {
            return derecho;
        }
    }



    return "";
}
bool Imagen2D::exportarHuffman(char *nombre)
{

    Arbol<Intensidad>* arbol=hoffman(calcularListaIntensidades());

//strcat(nombre, ".huffman");
    ofstream salida(nombre);
    if(salida)
    {
        salida<<getColumna()<<" "<<getFila()<<" "<<255<<endl;
        preOrden(arbol->getCabeza(),salida);
//reocorrer el vector

        for (int i=0; i<fila; i++)
        {


            for (int j=0; j<columna; j++)
            {

                string valor=codificarValor(arbol->getCabeza(),(*(imagen))[i][j],"");
                salida<<valor<<endl;
            }

        }
        arbol->eliminar();
        salida.close();
        return true;
    }
    else
    {
        return false;
//cout<<"La imagen: "<<nombre<<"No ha podido ser codificada"<<endl;
    }
}
