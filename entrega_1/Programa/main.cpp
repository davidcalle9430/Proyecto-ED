#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include "Arbol.h"
#include "Intensidad.h"
#include <fstream>
#include "Volumen.h"

void generarTablaDistancias(char *nombre, Grafo<Region>* grafo)
{
    ofstream archivo(nombre);
    if(archivo)
    {
        for(int i=0; i<grafo->getListaAristas()->size(); i++)
        {
            for(int j=0; j<grafo->getListaAristas()->size(); j++)
            {
                Region r1=(*grafo->getListaAristas())[i][0]->getFinArista()->getContenido();
                Region r2=(*grafo->getListaAristas())[j][0]->getFinArista()->getContenido();
                int xMax,xMin,yMin,yMax;
                xMax=max(r1.getX(),r2.getX());
                xMin=min(r1.getX(),r2.getX());
                yMax=max(r1.getY(),r2.getY());
                yMin=min(r1.getY(),r2.getY());
                int x= xMax-xMin;
                int y= yMax-yMin;
                int peso=(int)sqrt((x*x)+(y*y));
                archivo<<peso<<" ";
                cout<<peso<<" ";
            }
            cout<<endl;
            archivo<<endl;
        }
    }
    else
    {
        cout<<"No se pudo generar el archivo "<<endl;
    }
}
void distanciaMaxima(Grafo<Region>* grafo)
{
    vector< vector<int> >* temporal=new vector< vector<int > > (grafo->getListaAristas()->size(), vector<int> (grafo->getListaAristas()->size()));;
    for(int i=0; i< grafo->getListaAristas()->size(); i++)
    {
        for(int j=0; j<grafo->getListaAristas()->size(); j++)
        {
            (*temporal)[i][j]=-1;
        }
    }


    for(int i=0; i< grafo->getListaAristas()->size(); i++)
    {
        for(int j=0; j<(*grafo->getListaAristas())[i].size(); j++)
        {
            Vertice<Region>* vertice=(*grafo->getListaAristas())[i][j]->getFinArista();
            int pos= grafo->darPosicionVertice(vertice);
            (*temporal)[i][pos]=(*grafo->getListaAristas())[i][j]->getValor();

        }
        cout<<endl;
    }

    for(int k=0; k<grafo->getListaAristas()->size(); k++)
    {
        for(int i=0; i< grafo->getListaAristas()->size(); i++)
        {
            for(int j=0; j<grafo->getListaAristas()->size(); j++)
            {
                if(i!=j)
                {
                    (*temporal)[i][j]=max((*temporal)[i][j],(*temporal)[i][k]+(*temporal)[k][j]);
                }
            }
        }

    }

    int iMax=-1,jMax=-1,maximo=-1;
    cout<<endl<<" --TABLA DE DISTANCIAS MINIMA --"<<endl;
    for(int i=0; i< grafo->getListaAristas()->size(); i++)
    {
        for(int j=0; j< grafo->getListaAristas()->size(); j++)
        {

            cout<<(*temporal)[i][j]<<"    ";
        }
        cout<<endl;
    }
    for(int i=0; i< grafo->getListaAristas()->size(); i++)
    {

        for(int j=0; j<grafo->getListaAristas()->size(); j++)
        {
            if(maximo<(*temporal)[i][j])
            {
                maximo=(*temporal)[i][j];
                iMax=i;
                jMax=j;

            }
        }

    }

    cout<<"--Los vertices extremos son: "<<endl;
    cout<<"--PRIMERO--"<<endl;
    cout<<"Enla coordenanda x: "<<(*grafo->getListaAristas())[iMax][0]->getFinArista()->getContenido().getX()<<endl;
    cout<<"Enla coordenanda y: "<<(*grafo->getListaAristas())[iMax][0]->getFinArista()->getContenido().getY()<<endl;
    cout<<"--SEGUNDO--"<<endl;
    cout<<"Enla coordenanda x: "<<(*grafo->getListaAristas())[jMax][0]->getFinArista()->getContenido().getX()<<endl;
    cout<<"Enla coordenanda y: "<<(*grafo->getListaAristas())[jMax][0]->getFinArista()->getContenido().getY()<<endl;




}

void distanciaMinima(Grafo<Region>* grafo)
{
    vector< vector<int> >* temporal=new vector< vector<int > > (grafo->getListaAristas()->size(), vector<int> (grafo->getListaAristas()->size()));;
    for(int i=0; i< grafo->getListaAristas()->size(); i++)
    {
        for(int j=0; j<grafo->getListaAristas()->size(); j++)
        {
            (*temporal)[i][j]=10000;
        }
    }


    for(int i=0; i< grafo->getListaAristas()->size(); i++)
    {
        for(int j=0; j<(*grafo->getListaAristas())[i].size(); j++)
        {
            Vertice<Region>* vertice=(*grafo->getListaAristas())[i][j]->getFinArista();
            int pos= grafo->darPosicionVertice(vertice);
            (*temporal)[i][pos]=(*grafo->getListaAristas())[i][j]->getValor();

        }
        cout<<endl;
    }

    for(int k=0; k<grafo->getListaAristas()->size(); k++)
    {
        for(int i=0; i< grafo->getListaAristas()->size(); i++)
        {
            for(int j=0; j<grafo->getListaAristas()->size(); j++)
            {
                if(i!=j)
                {
                (*temporal)[i][j]=min((*temporal)[i][j],(*temporal)[i][k]+(*temporal)[k][j]);
                }
            }
        }

    }

    int iMax=-1,jMax=-1,maximo=-1;
    cout<<endl<<" --TABLA DE DISTANCIAS MINIMA --"<<endl<<endl;
    for(int i=0; i< grafo->getListaAristas()->size(); i++)
    {
        for(int j=0; j< grafo->getListaAristas()->size(); j++)
        {

            cout<<(*temporal)[i][j]<<"    ";
        }
        cout<<endl;
    }
    for(int i=0; i< grafo->getListaAristas()->size(); i++)
    {

        for(int j=0; j<grafo->getListaAristas()->size(); j++)
        {
            if(maximo<(*temporal)[i][j])
            {
                maximo=(*temporal)[i][j];
                iMax=i;
                jMax=j;

            }
        }

    }

    cout<<"--Los vertices extremos son: "<<endl;
    cout<<"--PRIMERO--"<<endl;
    cout<<"Enla coordenanda x: "<<(*grafo->getListaAristas())[iMax][0]->getFinArista()->getContenido().getX()<<endl;
    cout<<"Enla coordenanda y: "<<(*grafo->getListaAristas())[iMax][0]->getFinArista()->getContenido().getY()<<endl;
    cout<<"--SEGUNDO--"<<endl;
    cout<<"Enla coordenanda x: "<<(*grafo->getListaAristas())[jMax][0]->getFinArista()->getContenido().getX()<<endl;
    cout<<"Enla coordenanda y: "<<(*grafo->getListaAristas())[jMax][0]->getFinArista()->getContenido().getY()<<endl;




}
Volumen *p;
Grafo<Region> *grafo;
Imagen2D *imag;
using namespace std;

int main(int argc, char** argv)
{


    grafo=new Grafo<Region>();

    string op;
    op="";
    p=NULL;
    //cin>>op;
    while(op!="salir")
    {
        cin>>op;


        char* nom_arch= new char[100];

        char* nombreA= new char[100];

        int tam;
        string direccion;
        string criterio;


        if (op=="cargar_volumen")
        {
            cin>>nom_arch>>tam;
            if(tam<=100&&tam>=0)
            {
                delete p;
                p= new Volumen(nom_arch,tam);
                if(p->getTamanio()==0)
                {
                    cout<<"El volumen "<<nom_arch<<" no ha podido ser cargado"<<endl;
                }
                else
                {
                    cout<<"El volumen "<<nom_arch<<" ha sido cargado"<<endl;
                }
            }
            else
            {
                cout<<"el tamanio supera el maximo permitido"<<endl;
            }

        }
        else if (op=="proyeccion2D")
        {
            cin>>direccion;


            if(p!=NULL&&p->getTamanio()>0)
            {

                //cout<<"Direccion "<<direccion<<endl;
                if(direccion=="x")
                {


                    cin>>criterio>>nombreA;
                    //cout<<"Criterio "<<criterio<<endl;
                    if(criterio=="minimo")
                    {

                        Imagen2D* imagen=p->proyeccionXMinimo();
                        imagen->exportarImagen(nombreA);


                    }
                    if(criterio=="maximo")
                    {
                        Imagen2D* imagen= p->proyeccionXMaximo();
                        imagen->exportarImagen(nombreA);
                    }
                    if(criterio=="promedio")
                    {
                        Imagen2D* imagen= p->proyeccionXPromedio();
                        imagen->exportarImagen(nombreA);
                    }
                    if(criterio=="mediana")
                    {
                        Imagen2D* imagen= p->proyeccionXMediana();
                        imagen->exportarImagen(nombreA);
                    }
                }


                if(direccion=="y")
                {

                    cin>>criterio>>nombreA;


                    if(criterio=="minimo")
                    {
                        Imagen2D* imagen= p->proyeccionYMinimo();

                        imagen->exportarImagen(nombreA);

                    }
                    if(criterio=="maximo")
                    {
                        Imagen2D* imagen= p->proyeccionYMaximo();

                        imagen->exportarImagen(nombreA);
                    }
                    if(criterio=="promedio")
                    {
                        Imagen2D* imagen= p->proyeccionYPromedio();

                        imagen->exportarImagen(nombreA);
                    }
                    if(criterio=="mediana")
                    {
                        Imagen2D* imagen= p->proyeccionYMediana();
                        imagen->exportarImagen(nombreA);
                    }
                }

                if(direccion=="z")
                {

                    cin>>criterio>>nombreA;
                    if(criterio=="minimo")
                    {
                        Imagen2D* imagen= p->proyeccionZMinimo();
                        imagen->exportarImagen(nombreA);
                    }
                    if(criterio=="maximo")
                    {
                        Imagen2D* imagen= p->proyeccionZMaximo();
                        imagen->exportarImagen(nombreA);
                    }
                    if(criterio=="promedio")
                    {
                        Imagen2D* imagen= p->proyeccionZPromedio();
                        imagen->exportarImagen(nombreA);
                    }
                    if(criterio=="mediana")
                    {
                        Imagen2D* imagen= p->proyeccionZMediana();
                        imagen->exportarImagen(nombreA);
                    }

                }


            }
            else
            {
                cout<<"el volumen aun no ha sido cargado en memoria"<<endl;
            }
        }
        else if(op=="codificar_imagen")
        {
            char* nombre= new char[100];
            cin>>nombre;
            char* salida= new char[100];
            cin>>salida;
            char* copia= new char[100];
            strcpy(copia, nombre);
            cout<<"codificando archivo por favor espere..."<<endl;
            Imagen2D* imagen= new Imagen2D();
            if(imagen->cargarArchivo(nombre))
            {
                if(imagen->exportarHuffman(salida))
                {
                    cout<<"la imagen "<<nombre<<" ha sido codificada exitosamente"<<endl;
                }
                else
                {
                    cout<<"la imagen "<<nombre<<" no ha podido ser codificada"<<endl;
                }
            }
            else
            {
                cout<<"la imagen "<<nombre<<" no ha podido ser codificada"<<endl;
            }
        }
        else if(op=="decodificar_archivo")
        {
            char* nombre= new char[100];
            cin>>nombre;
            char *salida= new char[100];
            cin>>salida;

            cout<<"decodificando archivo por favor espere..."<<endl;
            char* copia= new char[100];
            strcpy(copia, nombre);
            Imagen2D* imagen= new Imagen2D();
            if(imagen->cargarHuffman(nombre))
            {
                imagen->exportarImagen(salida);
                cout<<"El archivo "<<copia<<" ha sido decodificado extosamente"<<endl;

            }
            else
            {
                cout<<"El archivo "<<copia<<" no ha podido ser decodificado"<<endl;
            }
        }
        else if(op=="generar_grafo")
        {

            char *nombreImagen= new char [100];
            cin>>nombreImagen;
            imag= new Imagen2D();
            imag->cargarArchivo(nombreImagen);
            cargarGrafo(imag,grafo);

        }
        else if(op=="colorear_grafo")
        {
            int numColores;
            cin>>numColores;
            char* nombreSalida= new char[100];
            cin>>nombreSalida;

            if(grafo!=NULL)
            {
                if(colorearGrafo(grafo,numColores))
                {
                    //  utilzar imag para pintar
                    /*
                    for(int i=0;i<grafo->getListaAristas()->size();i++){
                    cout<<"color"<<(*grafo->getListaAristas())[i][0]->getFinArista()->getContenido().getColorNuevo()<<endl;


                    }
                    */

                    Imagen2D copia=*imag;
                    for(int i=0; i<imag->getImagen()->size(); i++)
                    {
                        for (int j=0; j<(*imag->getImagen())[i].size(); j++)
                        {
                            int pixel=(*imag->getImagen())[i][j];
                            for(int g=0; g<grafo->getListaAristas()->size(); g++)
                            {
                                if(pixel==(*grafo->getListaAristas())[g][0]->getFinArista()->getContenido().getColor())
                                {
                                    (*copia.getImagen())[i][j]=(*grafo->getListaAristas())[g][0]->getFinArista()->getContenido().getColorNuevo();

                                }
                            }
                        }
                    }
                    imag->exportarImagen(nombreSalida);
                    cout<<"El grafo ha sido coloreado exitosamente con "<<numColores<<endl;

                }
                else
                {
                    cout<<"El grafo no ha podido ser coloreado con "<<numColores<<endl;
                }
            }
            else
            {
                cout<<"El grafo de la imagen aún no ha sido cargado"<<endl;
            }
        }
        else if(op=="tabla_distancias")
        {
            char* nombreArchivo= new char[100];
            cin>>nombreArchivo;
            if(grafo!=NULL){

            generarTablaDistancias(nombreArchivo,grafo);
            cout<<"La tabla de distancias ha sido construida exitosamente"<<endl;
            distanciaMinima(grafo);
            distanciaMaxima(grafo);
            }else{
            cout<<"El grafo de la imagen aún no ha sido cargado"<<endl;
            }
        }
    }
    return 0;
}

