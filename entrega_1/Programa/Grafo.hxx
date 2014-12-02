#include "Grafo.h"
#include "Region.h"
#include <queue>
#include <algorithm>
#include <iostream>
#include <utility>
#include <math.h>
using namespace std;
int const infinite=9999;
template<class T>
Grafo<T>::Grafo()
{
    listaAristas= new vector< vector< Arista<T>* > > ();
}

void cargarGrafo(Imagen2D* imagen, Grafo<Region>* grafo){


vector<int> regiones;
/* hay que encontrar las regiones*/
// recorrer la img en busca de regions

for(int i=0; i<imagen->getFila(); i++)
{
    for(int j=0; j<imagen->getColumna(); j++)
    {
        bool esta=false;
        for(int k=0; k<regiones.size();k++)
        {
           if((*imagen->getImagen())[i][j]==regiones[k]){
            esta=true;
           }
        }
        if(!esta){
            regiones.push_back((*imagen->getImagen())[i][j]);
        }

    }

}
    /* ya están todas las diferentes regiones*/
    for(int k=0; k<regiones.size(); k++)
    {
        int x=0;
        int y=0;
        int cont=0;
        for(int i=0; i<imagen->getImagen()->size(); i++)
        {
            for(int j=0; j<imagen->getColumna(); j++)
            {
                if((*imagen->getImagen())[i][j]==regiones[k])
                {
                    x+=i;
                    y+=j;
                    cont++;
                }

            }

        }
        // crear la region
        if(cont>200)
        {
            x=x/cont;
            y=y/cont;
            Region region (x,y,regiones[k],k);
            //cout<<"Se agrego la region con x:"<<x<<" y:"<<y<<" y color "<<regiones[k]<<" que se repite "<<cont<<endl;
            Vertice<Region> *vertice= new Vertice<Region> (region);
            grafo->agregarVertice(vertice);
        }
    }
    //cout<<"contador "<<regiones.size()<<endl;
    //cout<<"--SUAVE--"<<endl;
    cout<<"Si desea salir presione -1 de lo contrario ingrese 0 "<<endl;
    string op;
    cin>>op;
    int numero1,numero2;
    while (op!="-1")

    {

        cout<<"Ingrese el numero del vertice que desea: "<<endl;
        cout<<"--Vertice numero-- "<<"--Coordenada X--"<<"--Coordenada Y--"<<"--Color--"<<endl;

        for (int i=0; i<grafo->getListaAristas()->size(); i++)
        {
            cout<<"         "<<i<<"             "<<(*grafo->getListaAristas())[i][0]->getFinArista()->getContenido().getX()<<"           "<<(*grafo->getListaAristas())[i][0]->getFinArista()->getContenido().getY()<<"             "<<(*grafo->getListaAristas())[i][0]->getFinArista()->getContenido().getColor()<<endl;
        }
        cout<<endl;
        cout<<"Vertice de Inicio"<<endl;
        cin>>numero1;
        cout<<"Vertice de Final"<<endl;
        cin>>numero2;
        cout<<endl;
        Region r1, r2;
        for (int i=0; i<grafo->getListaAristas()->size(); i++)
        {
            if (i==numero1)
            {
                r1=(*grafo->getListaAristas())[i][0]->getFinArista()->getContenido();
            }
            if (i==numero2)
            {
                r2=(*grafo->getListaAristas())[i][0]->getFinArista()->getContenido();
            }

        }

        Vertice<Region> *vertice1= new Vertice<Region>(r1);
        Vertice<Region> *vertice2= new Vertice<Region>(r2);

        int xMax,xMin,yMin,yMax;
        xMax=max(r1.getX(),r2.getX());
        xMin=min(r1.getX(),r2.getX());
        yMax=max(r1.getY(),r2.getY());
        yMin=min(r1.getY(),r2.getY());
        int x= xMax-xMin;
        int y= yMax-yMin;
        int peso=(int)sqrt((x*x)+(y*y));

        grafo->agregarArista(vertice1,vertice2,peso);
          grafo->agregarArista(vertice2,vertice1,peso);
        //system("cls");
        cout<<"Arista aniadida satisfactoriamente con peso: "<<peso<<endl;
      cout<<"Si desea salir presione -1 de lo contrario ingrese 0 "<<endl;
    cin>>op;

    }
}

template<class T>
vector<vector<Arista<T>*> >* Grafo<T>::crearMatrizAdyacencia(){
vector<vector<Arista<T>*> >* retorno= new vector<vector<Arista<T>*> >(listaAristas->size(),vector<Arista<int>* >(listaAristas->size()));
for(int i=0;i<listaAristas->size();i++){
 for (int j = 0; j< listaAristas->size(); j++)
 {
     Vertice<T>* v= (*listaAristas)[0][0]->getFinArista();
     Arista<T>* a= new Arista<T>(infinite,v);
     (*retorno)[i][j]=a;
 }
}
/* ahora  buscar en la lista de aristas y actualizar los pesos */

for(int i=0;i<listaAristas->size();i++){
 for (int j = 0; j< (*listaAristas)[0].size(); j++)
 {
    Vertice<T>* v= (*listaAristas)[i][j]->getFinArista();
    int pos=0;
    //ahora se busca la posicion de ese vertice en la lista de aristas
    for(int t=0;t<listaAristas->size();t++){
      if(*v==*(listaAristas)[t][0]){
       pos=t;

      }
    }
   (*retorno)[i][pos]->setValor( (*listaAristas)[i][j]->getValor());
 }
}
return retorno;
}




template<class T>
bool Grafo<T>::visitarNodos(Vertice<T>* origen, vector<Vertice<T> *>* visitados,vector<Vertice<T> *>* camino, int* total){
 bool esta=false;
    for(int i=0; i<visitados->size(); i++)
    {
        if((*visitados)[i]->getContenido()==origen->getContenido())
        {
            esta=true;
        }

    }
    if(!esta)
    {
    vector<Arista<T> *>* temporal2= buscarAdyacentes(origen);
    vector<Arista<T> > *temporal= new vector<Arista<T> >();
    for(int i=0;i<temporal2->size();i++){
      temporal->push_back(*(*temporal2)[i]);
    }
    sort (temporal->begin()+1, temporal->end());
    visitados->push_back(origen);
    camino->push_back(origen);

    for(int i=1; i<temporal->size(); i++)
    {
       // camino->push_back(origen);
        int antes=visitados->size();
        *(total)=*(total)+(*temporal)[i].getValor();
        visitarNodos((*temporal)[i].getFinArista(),visitados,camino,total);
        int despues=visitados->size();

        if(antes==despues){
             *(total)=*(total)-(*temporal)[i].getValor();
         }

        if(i>0&&visitados->size()!=listaAristas->size()&&antes!=despues){
          camino->push_back(origen);

         }
    }


}
}








template <class T>
Vertice<T>*  Grafo<T>::encontrarVertice(Vertice<T>* vertice){
    //cout<<"tam lista aristas es: "<<listaAristas->size()<<endl;
  for (int i=0; i<listaAristas->size(); i++)
    {
           // cout<<"tam de los vertices es: "<<(*listaAristas)[i].size()<<endl;

        if((*listaAristas)[i][0]->getFinArista()->getContenido()==vertice->getContenido())
        {


            return (*listaAristas)[i][0]->getFinArista();
        }
    }
  //cout<<"vertice no encontrado"<<endl;
    return NULL;

}
template <class T>
vector< vector<Arista <T> * > >* Grafo<T>::getListaAristas(){
return listaAristas;
}

template <class T>
bool Grafo<T>::caminoEuleriano( vector<Vertice<T> *> * visitados)
{
    int verticesImpares=numeroVerticesImpar();

    vector< vector<Arista <T> * > >*copia= new vector< vector<Arista <T> * > >(*listaAristas);

    if(verticesImpares==0||verticesImpares==2)
    {

            Vertice<T>* actual=(*listaAristas)[0][0]->getFinArista();
            if(verticesImpares==2){
                //empezar por un impar
                for(int i=0; i<listaAristas->size(); i++)
                {
                    if ((*listaAristas)[i].size()%2==0)
                    {
                        actual=(*listaAristas)[i][0]->getFinArista();
                    }
                }
            }

            visitados->push_back(actual);
            //buscar en su lista de adyacencia, vertices adyancentes que no  sean puentes
            bool condicion =true;

            while(condicion)
            {


                vector<Arista<T>* >* adyacentes= buscarAdyacentes(actual);
                bool entra=false;
                for(int i=1; i<adyacentes->size(); i++)
                {

                    Arista<T>* fin=(*adyacentes)[i];
                    (*adyacentes).erase((*adyacentes).begin()+i);
                    vector<Vertice<T> *>* recorrido= new vector<Vertice<T> *>();
                    dfs(actual, recorrido);
                    bool esPuente=false;
                    if(recorrido->size()==listaAristas->size())
                    {
                        esPuente=!esPuente;
                    }



                    if(!esPuente)
                    {
                        vector<Arista<T> *>* listaAd= new vector<Arista<T> *>();
                        listaAd=buscarAdyacentes(fin->getFinArista());


                        for(int j=0; j<listaAd->size(); j++)
                        {
                            if((*listaAd)[j]->getFinArista()->getContenido()==(actual)->getContenido())
                            {
                                listaAd->erase(listaAd->begin()+j);
                            }
                        }
                        actual=fin->getFinArista();
                        i=adyacentes->size();
                        entra=!entra;
                        //


                        visitados->push_back(actual);
                    }
                    else
                    {
                        (*adyacentes).push_back(fin);
                    }
                }
                if(!entra)
                {
                    for(int i=1; i<adyacentes->size(); i++)
                    {
                        Arista<T>* fin=(*adyacentes)[i];
                        vector<Arista<T> *>* listaAd= new vector<Arista<T> *>();
                        listaAd=buscarAdyacentes(fin->getFinArista());


                        for(int j=0; j<listaAd->size(); j++)
                        {
                            if((*listaAd)[j]->getFinArista()->getContenido()==(actual)->getContenido())
                            {
                                //cout<<"elimina"<<endl;
                                listaAd->erase(listaAd->begin()+j);
                            }
                        }
                        (*adyacentes).erase((*adyacentes).begin()+i);
                        actual=fin->getFinArista();
                        i=adyacentes->size();
                        visitados->push_back(actual);
                        //

                    }
                }
                bool pepito= false;
                for(int i=0; i<listaAristas->size(); i++)
                {
                    if((*listaAristas)[i].size()!=1)
                    {
                        pepito=true;
                    }

                }
                if(!pepito)
                {
                    condicion=false;
                }
            }
           listaAristas=copia;
        return true;
    }

    return false;

}




template <class T>
int Grafo<T>::numeroVerticesImpar(){
  int contador=0;
  for (int i=0; i<listaAristas->size(); i++)
    {
       if((*listaAristas)[i].size()%2==0){
        contador++;
       }
    }
  return contador;
}

template <class T>
bool Grafo<T>::agregarVertice(Vertice<T>* fin)
{
    /*
     * falta verificar que no exista
     */
    //vertices->push_back(fin);
    vector<Arista<T> *>* aristaNueva= new vector<Arista<T> *>();
    //vector<Arista<T> *>* aristaOrdenada= new vector<Arista<T> *>();
    Arista<T>* nueva= new Arista<T>();
    nueva->setValor(0);
    nueva->setFinArista(fin);

    aristaNueva->push_back(nueva);


        listaAristas->push_back((*aristaNueva));
       // cout<<"tam de lista aristas es "<<listaAristas->size()<<endl;
      //agregar a la lista de adyacencias el nuevo espacio




    if(listaAristas==NULL)
    {
        return false;
    }
    else
        return true;
}
template<class T>
bool Grafo<T>::agregarArista(Vertice<T>* inicio, Vertice<T>* fin, int peso)
{
//primero busco el vertice fin en la lista de vertices del grafo.
//buscar lista de adyaencia en la matriz de adyacencia igual a inicio
//agregar el vertice a la lista de adyacencia.
    /*
        * falta verificar que n void bfs(Vertice<T>* origen);o exista
        */

    Arista<T>* nueva= new Arista<T>();
    nueva->setValor(peso);
    nueva->setFinArista(fin);
    for (int i=0; i<listaAristas->size(); i++)
    {
        if((*listaAristas)[i][0]->getFinArista()->getContenido()==inicio->getContenido())
        {
            (*listaAristas)[i].push_back(nueva);
            //sort ((*listaAristas)[i].begin()+1,(*listaAristas)[i].end());
            return true;
        }
    }

    return false;
}
template<class T>
bool Grafo<T>::eliminarArista(Vertice<T>* inicio, Vertice<T>* fin)
{
    for (int i=0; i<listaAristas->size(); i++)
    {
        if((*listaAristas)[i]->getFinArista()->getContenido()==inicio->getContenido())
        {
            for (int j=0; j<listaAristas[i].size(); j++)
            {
                if((*listaAristas)[i][j]->getFinArista()->getContenido()==inicio->getContenido())
                {
                    (*listaAristas)[i].erase((*listaAristas)[i].begin()+j);
                    return true;
                }

            }
        }
    }
    return false;


}
template<class T>
bool Grafo<T>::eliminarVertice (Vertice<T>* nuevo)
{
    for (int i=0; i<listaAristas.size(); i++)
    {
        if((*listaAristas)[i]->getFinArista()->getContenido()==nuevo->getContenido())
        {
            for (int j=0; j<listaAristas[i].size(); j++)
            {
                if((*listaAristas)[i][j]->getFinArista()->getContenido()==nuevo->getContenido())
                {
                    (*listaAristas)[i].erase((*listaAristas)[i].begin()+j);
                    return true;
                }

            }
        }
    }
    return false;

}
template<class T>
void  Grafo<T>::dfs(Vertice<T>* origen, vector<Vertice<T> *>* visitados)
{
    // vamos a buscae los adyacentes a ese vertice  y recorrer por prfundidad
    bool esta=false;

    for(int i=0; i<visitados->size(); i++)
    {
        if((*visitados)[i]->getContenido()==origen->getContenido())
        {
            esta=true;
        }

    }

    if(!esta)
    {
    vector<Arista<T> *>* temporal2= buscarAdyacentes(origen);
    vector<Arista<T> > *temporal= new vector<Arista<T> >();

//hay que pasar eso a una lista de aristas
    for(int i=0;i<temporal2->size();i++){
      temporal->push_back(*(*temporal2)[i]);
    }



         sort (temporal->begin()+1, temporal->end());
        visitados->push_back(origen);
        for(int i=0; i<temporal->size(); i++)
        {
           // cout<<(*temporal)[i]->getValor()<<endl;

            //cout<<"Se llama para "<<(*temporal)[i].getFinArista()->getContenido()<<endl;
            dfs((*temporal)[i].getFinArista(),visitados);

        }
    }







}
template<class T>
vector<Arista<T>* >*  Grafo<T>:: buscarAdyacentes(Vertice<T> *origen)
{
//cout<<"entra al metodo"<<endl;
    for (int i=0; i<listaAristas->size(); i++)
    {
  //      cout<<"entra al for"<<endl;
        if((*listaAristas)[i][0]->getFinArista()->getContenido()==origen->getContenido())
        {
    //       cout<<"llega buscar y encuentra"<<endl;
         vector<Arista<T>* > *ap;


      //     cout<< "antes de el tam es de "<<(*listaAristas)[i].size()<<endl;
            return &(((*listaAristas)[i]));;
        }

    }
}

template<class T>
 void Grafo<T>::bfs(Vertice<T>* origen){

 queue<Vertice<T> > *cola=new queue<Vertice<T> >();
 vector<Vertice<T> > *visitados= new vector<Vertice<T> >();
 cola->push(*origen);
 visitados->push_back(*origen);

 while(cola->size()>=1){

    // saco la lista de ayacentes
    Vertice<T> tempora= cola->front();
    Vertice<T>* t=&tempora;
    cout<<tempora.getContenido()<<endl;
   // cout<<"llega"<<endl;
    vector<Arista<T>* > *temporal2= buscarAdyacentes(t);
     // cout<<"llega"<<endl;
    vector<Arista<T> > *temporal= new vector<Arista<T> >();
      //cout<<"llega"<<endl;

//hay que pasar eso a una lista de aristas
int tam=temporal2->size();
//cout<<"llega"<<endl;
    for(int i=0;i<tam;i++){

      temporal->push_back(*(*temporal2)[i]);
    }



     sort (temporal->begin()+1, temporal->end());
     bool esta=false;
     for(int i=0; i<temporal->size();i++){
         //   cout<<"para  "<<(*temporal)[i]->getFinArista()->getContenido()<<endl;
        bool encuentro=false;
        for(int j=0; j<visitados->size();j++){

            if((*temporal)[i].getFinArista()->getContenido()==((*visitados)[j].getContenido()))
               {
                   encuentro=true;
               }
        }
        if(!encuentro)
        {  // cout<<"Mete a "<<(*temporal)[i].getFinArista()->getContenido()<<endl;
            cola->push(*(*temporal)[i].getFinArista());
            visitados->push_back(*(*temporal)[i].getFinArista());
        }

     }
 //cout<<"fin busqueda adyancetes vertice"<<endl;
  //cout<<"antes "<<cola->size()<<endl;
    cola->pop();

//cout<<"despues "<<cola->size()<<endl;
//system("pause");


 }



 delete cola;
 }
template<class T>
bool Grafo<T>::visitarLosNodos( vector<Vertice<T> *>* visitados)
{    bool aplica=false;

    for(int i=0; i<listaAristas->size(); i++)
    {
        if ((*listaAristas)[i].size()==2)
        {
         return aplica;
        }
    }

    return (caminoEuleriano(visitados));


}
 vector<vector<int> >* multiplicarMatrices(vector<vector<int> >* a,vector<vector<int> >* b){
   vector<vector<int> >* retorno= new vector<vector<int> >();
   for(int i=0;i<a->size();i++){
    for(int j=0;i<a->size();i++){
        int valor=0;
     for(int k=0; k<a->size();k++){
        valor+= (*a)[i][k] * (*b)[k][j];
     }

     (*retorno)[i].push_back(valor);
    }
   }

    return retorno;
 }
 template<class T>
 int Grafo<T>::darPosicionVertice(Vertice<T>* vertice){
 	for(int i=0; i< listaAristas->size(); i++){
      if((*listaAristas)[i][0]->getFinArista()->getContenido()==vertice->getContenido()){
      	return i;
      }
 	}
 	return -1;
 }

/*template<class T>
vector<vector<int> >* convertirAMatrizEnteros( vector<vector<Arista<T>*> >* matriz){
  vector<vector<int> >* a=new vector<vector<int> >();
    for (int i = 0; i < matriz->size(); i++)
    {
        for (int j= 0; j < matriz->size(); j++)
        {
         (*a)[i].push_back((*matriz)[i][j]->getValor());
        }
     }



template<class T>
vector<vector<int> >* Grafo<T>::darCaminosLongitud(int longitud){
vector<vector<Arista<T>* > >* matriz=crearMatrizAdyacencia();
vector<vector<int > >* matrizEnteros=convertirAMatrizEnteros<T>(matriz);
vector<vector<int > >* primera= new vector<vector<int > >(*matrizEnteros);
while(longitud--)


matrizEnteros= multiplicarMatrices(matrizEnteros,primero);
}
return matrizEnteros;
}*/
