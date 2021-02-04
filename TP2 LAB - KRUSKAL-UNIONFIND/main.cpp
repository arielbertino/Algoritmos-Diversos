#include <iostream>
#include "UnionFind.h"
#include "GrafoF.h"
#include "arcoOCD.h"
#include <set>
#include <list>

using namespace std;

template <typename C> ostream & operator << (ostream & salida, const Grafo<C> & grafo)
{
	// Recorremos todos los vertices
	list<int> vertices;
	grafo.devolverVertices(vertices);
	list<int>::iterator v = vertices.begin();
	while (v != vertices.end()) {
		salida << "    " << *v << "\n";
		// Recorremos todos los adyacentes de cada vertice
		list<typename Grafo<C>::Arco> adyacentes;
		grafo.devolverAdyacentes(*v, adyacentes);
		typename list<typename Grafo<C>::Arco>::iterator ady = adyacentes.begin();
		while (ady != adyacentes.end()) {
			salida << "    " << *v << "-> " << ady->devolverAdyacente() << " (" << ady->devolverCosto() << ")\n";
			ady++;
		}
		v++;
	}
	return salida;
}
/// hacer kruskal ; unionfind me sirve para tener conjuntos auxiliares e ir armando la solucion
///con lo que me devuelve unionfind tengo que armar un nuevo grafo con los vertices iniciales y cagarle los arcos correspondoente
///que serian los de menor costo y aparte mostrarlo.

void kruskal (list<arcoOCD> listaDeArcosOrdenado, int cant,Grafo<int> & grafoMinimo, int & costoArbMin)
{
    costoArbMin = 0; /// costo inicial arbol minimo
    UnionFind arregloPadres(cant);    ///para cada vertice Creo un subconjunto
    /// las arista las recibo por parametro ya ordenadas
    typename list<arcoOCD>::iterator itList = listaDeArcosOrdenado.begin();
    while(itList != listaDeArcosOrdenado.end())
    {
        int origencito = arregloPadres.findPadre(itList->devolverOrigen());
        int destinito  = arregloPadres.findPadre(itList->devolverDestino());
        if (origencito != destinito)
        {
            grafoMinimo.agregarArco((itList->devolverOrigen()), (itList->devolverDestino()), (itList->devolverCosto()));
            arregloPadres.unionConjunto(origencito, destinito);
            costoArbMin = (costoArbMin + itList->devolverCosto());
        }
        itList++;

    }
    //cin.get();
}

///cargado de grafo por teclado
/*

void cargarGrafoListaArco(Grafo<int> & grafic, list<arcoOCD> & listaDeArcosOrdenado)
{
    int vertice = 15000;  ///por ponerle algo para que empiexe el ciclo
    int costo, destino;
    while (vertice > 0)
    {
        cout << "ingrese vertices, ingrese 0(cero) para terminar la carga: ";
        cin  >> vertice;
        grafic.agregarVertice(vertice);
    }
    vertice = 15000;
    cout << endl;
    cout << "ingrese arcos/ ingrese 0 (cero para finalizer la carga): " << endl;
    while (vertice > 0)
    {
        cout << "ingrese origen: ";
        cin  >> vertice;
        cout << "ingrese costo: ";
        cin  >> costo;
        cout << "ingrese destino: ";
        cin  >> destino;
        grafic.agregarArco(vertice, destino, costo);
        listaDeArcosOrdenado.push_back(arcoOCD(vertice, costo, destino));  ///cargar arco a la list
    }
    listaDeArcosOrdenado.sort();   ///ordenar lista
}

*/

void cargarGrafoListaArcoManual(Grafo<int> & g, list<arcoOCD> & listaDeArcosOrdenado)
{
    g.agregarVertice(1);
    g.agregarVertice(2);
    g.agregarVertice(3);
    g.agregarVertice(4);
    g.agregarVertice(5);
    g.agregarVertice(6);
    g.agregarVertice(7);
    g.agregarVertice(8);
    g.agregarVertice(9);

    g.agregarArco (1, 2, 1);
    g.agregarArco (1, 4, 2);
    g.agregarArco (2, 1, 1);
    g.agregarArco (2, 3, 8);
    g.agregarArco (2, 4, 2);
    g.agregarArco (2, 5, 17);
    g.agregarArco (2, 6, 16);
    g.agregarArco (3, 2, 8);
    g.agregarArco (3, 6, 9);
    g.agregarArco (4, 1, 2);
    g.agregarArco (4, 2, 2);
    g.agregarArco (4, 5, 5);
    g.agregarArco (4, 7, 9);
    g.agregarArco (5, 2, 17);
    g.agregarArco (5, 4, 5);
    g.agregarArco (5, 6, 1);
    g.agregarArco (5, 7, 17);
    g.agregarArco (5, 8, 11);
    g.agregarArco (5, 9, 4);
    g.agregarArco (6, 2, 16);
    g.agregarArco (6, 3, 9);
    g.agregarArco (6, 5, 1);
    g.agregarArco (6, 9, 4);
    g.agregarArco (7, 4, 9);
    g.agregarArco (7, 5, 17);
    g.agregarArco (7, 8, 16);
    g.agregarArco (8, 5, 11);
    g.agregarArco (8, 7, 16);
    g.agregarArco (8, 9, 3);
    g.agregarArco (9, 5, 4);
    g.agregarArco (9, 6, 4);
    g.agregarArco (9, 8, 3);

    listaDeArcosOrdenado.push_front(arcoOCD(1, 2, 1));
    listaDeArcosOrdenado.push_front(arcoOCD(1, 4, 2));
    listaDeArcosOrdenado.push_front(arcoOCD(2, 1, 1));
    listaDeArcosOrdenado.push_front(arcoOCD(2, 3, 8));
    listaDeArcosOrdenado.push_front(arcoOCD(2, 4, 2));
    listaDeArcosOrdenado.push_front(arcoOCD(2, 5, 17));
    listaDeArcosOrdenado.push_front(arcoOCD(2, 6, 16));
    listaDeArcosOrdenado.push_front(arcoOCD(3, 2, 8));
    listaDeArcosOrdenado.push_front(arcoOCD(3, 6, 9));
    listaDeArcosOrdenado.push_front(arcoOCD(4, 1, 2));
    listaDeArcosOrdenado.push_front(arcoOCD(4, 2, 2));
    listaDeArcosOrdenado.push_front(arcoOCD(4, 5, 5));
    listaDeArcosOrdenado.push_front(arcoOCD(4, 7, 9));
    listaDeArcosOrdenado.push_front(arcoOCD(5, 2, 17));
    listaDeArcosOrdenado.push_front(arcoOCD(5, 4, 5));
    listaDeArcosOrdenado.push_front(arcoOCD(5, 6, 1));
    listaDeArcosOrdenado.push_front(arcoOCD(5, 7, 17));
    listaDeArcosOrdenado.push_front(arcoOCD(5, 8, 11));
    listaDeArcosOrdenado.push_front(arcoOCD(5, 9, 4));
    listaDeArcosOrdenado.push_front(arcoOCD(6, 2, 16));
    listaDeArcosOrdenado.push_front(arcoOCD(6, 3, 9));
    listaDeArcosOrdenado.push_front(arcoOCD(6, 5, 1));
    listaDeArcosOrdenado.push_front(arcoOCD(6, 9, 4));
    listaDeArcosOrdenado.push_front(arcoOCD(7, 4, 9));
    listaDeArcosOrdenado.push_front(arcoOCD(7, 5, 17));
    listaDeArcosOrdenado.push_front(arcoOCD(7, 8, 16));
    listaDeArcosOrdenado.push_front(arcoOCD(8, 5, 11));
    listaDeArcosOrdenado.push_front(arcoOCD(8, 7, 16));
    listaDeArcosOrdenado.push_front(arcoOCD(8, 9, 3));
    listaDeArcosOrdenado.push_front(arcoOCD(9, 5, 4));
    listaDeArcosOrdenado.push_front(arcoOCD(9, 6, 4));
    listaDeArcosOrdenado.push_front(arcoOCD(9, 8, 3));

    listaDeArcosOrdenado.sort();
}

void cargarArbolMinimo(Grafo<int> & grafic, int cant)
{
    int canti = cant;
    while(canti > 0)   ///agrega los cant cantidad de vertice
    {
        grafic.agregarVertice(canti);
        canti--;
    }
}

int main()
{
    int costoArbMin;
    Grafo<int> ggrafo;
    Grafo<int> krusGrafo;
    list<arcoOCD> listaArcosEnOrden;
    int cantidadVertices= 9;

    cargarGrafoListaArcoManual(ggrafo,listaArcosEnOrden);
    cout << "Estructura del grafo:\n" << ggrafo << "\n";

//  cargarGrafoListaArco(krusGrafo, listaArcosEnOrden);
    cargarArbolMinimo(krusGrafo, cantidadVertices);
    kruskal (listaArcosEnOrden, cantidadVertices, krusGrafo, costoArbMin);

    cout << "Estructura del grafo:\n" << krusGrafo << "\n";
    cout << "El costo del Arbol de recubrimiento minimo(Kruskal) es de: " << costoArbMin << endl;
    return 0;

}
