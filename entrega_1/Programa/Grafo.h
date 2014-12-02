#ifndef __GRAFO_H
#define __GRAFO_H
#include <vector>
#include "Vertice.h"
#include "Arista.h"
template<class T>
class Grafo
{
private:
   // vector<Vertice<T>*> vertices;
    vector< vector<Arista <T> * > > *listaAristas;
public:
    Grafo();
    vector< vector<Arista <T> * > >* getListaAristas();
    bool agregarVertice(Vertice<T>* fin);
    bool agregarArista(Vertice<T>* inicio, Vertice<T>* fin, int peso);
    bool eliminarArista(Vertice<T>* inicio, Vertice<T>* fin);
    bool eliminarVertice (Vertice<T>* nuevo);
    int tamanio();
    bool eliminarGrafo();
    bool esTrivial();
    bool esRegular();
    bool esVacio();
    Vertice<T>* encontrarVertice(Vertice<T>* vertice);
    bool buscarVertice(Vertice<T>* nuevo);
    int orden();
    void dfs(Vertice<T>* origen, vector<Vertice<T> *>* visitados);
    bool visitarNodos(Vertice<T>* origen, vector<Vertice<T> *>* visitados,vector<Vertice<T> *>* camino, int* p);
    void bfs(Vertice<T>* origen);
    int numeroVerticesImpar();
    bool caminoEuleriano( vector<Vertice<T> *>* visitados);
    bool visitarLosNodos( vector<Vertice<T> *>* visitados);
    vector<vector<Arista<T>*> >* crearMatrizAdyacencia();
    vector<vector<int> >* darCaminosLongitud(int longitud);
    vector<Arista<T>* >* buscarAdyacentes(Vertice<T> *origen);
    vector<vector<int> >*  floydWarshall();
};
#include "Grafo.hxx"
#endif
