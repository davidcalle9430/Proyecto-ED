#include <iostream>
#include <fstream>

#include <string>
#include "Arbol.h"
#include "Intensidad.h"
#include <fstream>
#include "Volumen.h"


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
            if(tam<=100&&tam>=0){
           delete p;
            p= new Volumen(nom_arch,tam);
             if(p->getTamanio()==0){
               cout<<"El volumen "<<nom_arch<<" no ha podido ser cargado"<<endl;
             }else{
           cout<<"El volumen "<<nom_arch<<" ha sido cargado"<<endl;
             }
			 }else{
             	cout<<"el tamanio supera el maximo permitido"<<endl;
             }

        }
        else if (op=="proyeccion2D")
        {
            cin>>direccion;


            if(p!=NULL&&p->getTamanio()>0){

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


        }else{
cout<<"el volumen aun no ha sido cargado en memoria"<<endl;
}
       } else if(op=="codificar_imagen"){
            char* nombre= new char[100];
            cin>>nombre;
            char* salida= new char[100];
            cin>>salida;
            char* copia= new char[100];
            strcpy(copia, nombre);
            cout<<"codificando archivo por favor espere..."<<endl;
            Imagen2D* imagen= new Imagen2D();
             if(imagen->cargarArchivo(nombre)){
            if(imagen->exportarHuffman(salida)){
              cout<<"la imagen "<<nombre<<" ha sido codificada exitosamente"<<endl;
            }else{
                 cout<<"la imagen "<<nombre<<" no ha podido ser codificada"<<endl;
                 }
             }else{
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
            if(imagen->cargarHuffman(nombre)){
             imagen->exportarImagen(salida);
             cout<<"El archivo "<<copia<<" ha sido decodificado extosamente"<<endl;

            }else{
             cout<<"El archivo "<<copia<<" no ha podido ser decodificado"<<endl;
            }
        }else if(op=="generar_grafo"){

     char *nombreImagen= new char [100];
     cin>>nombreImagen;
     imag= new Imagen2D();
     imag->cargarArchivo(nombreImagen);
     cargarGrafo(imag,grafo);
     cout<<"fin"<<endl;
       }else if(op=="colorear_grafo"){
       	int numColores;
       	cin>>numColores;
       	char* nombreSalida= new char[100];
       	cin>>nombreSalida;
        

       	if(colorearGrafo(grafo,numColores)){
    //  utilzar imag para pintar
         /* 
    for(int i=0;i<grafo->getListaAristas()->size();i++){
        cout<<"color"<<(*grafo->getListaAristas())[i][0]->getFinArista()->getContenido().getColorNuevo()<<endl;


         }
         */
         if(grafo!=NULL){
         Imagen2D copia=*imag;
    for(int i=0; i<imag->getImagen()->size();i++)
            {
                for (int j=0;j<(*imag->getImagen())[i].size();j++)
                {
                    int pixel=(*imag->getImagen())[i][j];
                    for(int g=0;g<grafo->getListaAristas()->size();g++){
                       if(pixel==(*grafo->getListaAristas())[g][0]->getFinArista()->getContenido().getColor()){
                            (*copia.getImagen())[i][j]=(*grafo->getListaAristas())[g][0]->getFinArista()->getContenido().getColorNuevo();
                       
                    }
                }
            }

            imag->exportarImagen(nombreSalida);
            cout<<"El grafo ha sido coloreado exitosamente con "<<numColores<<endl;

     }else{
     cout<<"El grafo no ha podido ser coloreado con "<<numColores<<endl;
     }
       }else{
        cout<<"El grafo de la imagen aún no ha sio cargado"<<endl;
       }
   }
}
    return 0;
}

