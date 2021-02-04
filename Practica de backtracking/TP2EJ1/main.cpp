#include <iostream>
#include <list>
#include "GrafoF.h"

using namespace std;
/**
    Enunciado: Se tiene un conjunto de salas comunicadas entresi atravez de puertas que se abren solamente en un sentido.
    Una de las salas se denomina entrada y la otra salida. Constrie un algoritmo que permita ir desde la entrada a la salida
    atravesano la maxima cantidad de salas.
**/

void cargarSalas(Grafo<int> & grafo, char ArrMarcas[], int cantSalas)
{
    for (int i=1; i<=cantSalas; i++)
    {
        ArrMarcas[i] = 'N';
        grafo.agregarVertice(i);
    }
    grafo.agregarArco(1,2,0);
    grafo.agregarArco(1,4,0);
    grafo.agregarArco(2,3,0);
    grafo.agregarArco(2,5,0);
    grafo.agregarArco(3,6,0);
    grafo.agregarArco(4,5,0);
    grafo.agregarArco(4,7,0);
    grafo.agregarArco(5,6,0);
    grafo.agregarArco(5,8,0);
    grafo.agregarArco(8,9,0);
    grafo.agregarArco(9,6,0);

}

void backSalas(Grafo<int> grafo, list<int> & solucion,char arrMarcas[], int cantSalas, int & longitud, int inicio, int fin)
{
    arrMarcas[inicio] = 'V';
    int longAux;
    longAux++;
    list<int> solParcial = solucion;
    solParcial.push_back(inicio);
    if ((inicio = fin) && (longAux > longitud))
        {
            longitud = longAux;
            solucion = solParcial;
        }
    list<Grafo<int>::Arco> adyacentes;
    grafo.devolverAdyacentes(inicio, adyacentes);
    typename list<Grafo<int>::Arco>::iterator itAdy = adyacentes.begin();
    while((itAdy != adyacentes.end()) && (arrMarcas[inicio] != 'V'))
    {
        typename list<int>::iterator itList = solParcial.begin();
        int longAux = 0;
        while (itList != solParcial.end())
        {
            longAux++;
            itList++;
        }
        int u =  itAdy->devolverAdyacente();
        backSalas(grafo, solucion, arrMarcas, cantSalas, longitud, u, fin);
    }
    arrMarcas[inicio] = 'N';
    longAux--;
}

int main()
{
    Grafo<int> G;
    list<int> solucion;
    int cantSalas = 9;
    char arrMarcas[cantSalas];
    int longitud =0;
    int inicio = 1;
    int fin = 6;
    backSalas(G, solucion, arrMarcas, cantSalas, longitud, inicio, fin);
    list<int>::const_iterator itSol = solucion.begin();
    while(itSol != solucion.end())
    {
        cout << *itSol << " ";
        itSol++;
    }
    return 0;
}
