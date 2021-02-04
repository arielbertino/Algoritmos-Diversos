#include <iostream>
#include "GrafoF.h"
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>

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

void cargarArreglo(char arreglo[],int numeracion[], int n)
{
    arreglo[0] = 'n';
    for (int i=1 ; i<=n ; i++)
    {
        arreglo[i] = 'N';  //'NO VISITADO'
        numeracion[i] = 0;
    }
}

void cargarGrafoSortTop(Grafo<int> & grafo, int n)
{
    /// CARGADO PARA TESTEAR EL SORT TOPOLOGICO

    /// VERTICES
    for (int i=1; i<=n; i++)
        grafo.agregarVertice(i);

    /// ARCOS

    grafo.agregarArco(1,2,0);
    grafo.agregarArco(3,2,0);
    grafo.agregarArco(3,4,0);
    grafo.agregarArco(5,4,0);
    grafo.agregarArco(5,6,0);
}

void cargarGrafo(Grafo<int> & grafo, int n)
{
    /// CARGARDO PARA TESTEAR DFS Y BFS
    /// VERTICES
    for (int i=1; i<=n; i++)
        grafo.agregarVertice(i);

    /// ARCOS

    grafo.agregarArco(1,2,0);
    grafo.agregarArco(1,4,0);
    grafo.agregarArco(2,3,0);
    grafo.agregarArco(4,2,0);
    grafo.agregarArco(4,5,0);
    grafo.agregarArco(5,3,0);
    grafo.agregarArco(5,6,0);
    grafo.agregarArco(6,3,0);

}

void DFSmostrar(Grafo<int> grafo, int inicio, char arregloMarcas[], int cant)
{
    arregloMarcas[inicio] = 'V';  /// VISITADO
    list<Grafo<int>::Arco> adyacentes;
    grafo.devolverAdyacentes(inicio,adyacentes);
    for(typename list<Grafo<int>::Arco>::iterator itAdy = adyacentes.begin(); itAdy != adyacentes.end(); itAdy++)
    {
        int u = itAdy->devolverAdyacente();
        if (arregloMarcas[u] == 'N')
            {
                cout << u ;
                DFSmostrar(grafo, u,arregloMarcas,cant);
            }
    }
}

void BFSmostrar(Grafo<int> grafo, int inicio, char arregloMarcas[])
{
    list<int> verticesDELgrafo;
    grafo.devolverVertices(verticesDELgrafo);
    for(typename list<int>::iterator itVertices = verticesDELgrafo.begin(); itVertices != verticesDELgrafo.end(); itVertices++)
        arregloMarcas[*itVertices] = 'B';
    arregloMarcas[inicio] = 'G';
    queue<int> fila;
    fila.push(inicio);
    while (!fila.empty())
    {
        int u = fila.front();
        //cout << u;
        fila.pop();
        list<Grafo<int>::Arco> adyacentes;
        grafo.devolverAdyacentes(u, adyacentes);
        for (typename list<Grafo<int>::Arco>::iterator itAdy = adyacentes.begin(); itAdy != adyacentes.end(); itAdy++)
        {
            int v = itAdy->devolverAdyacente();
            if (arregloMarcas[v] == 'B')
            {
                arregloMarcas[v] = 'G';
                fila.push(v);
            }
        }
        arregloMarcas[u]='N';
        cout<<u;
    }
}
void DFSTopologico(Grafo<int> grafo, int inicio, char arregloMarcas[],int numeracion[],int & posTop, stack<int> & pilaTop)
{
    arregloMarcas[inicio] = 'V';  /// VISITADO
    list<Grafo<int>::Arco> adyacentes;
    grafo.devolverAdyacentes(inicio,adyacentes);
    for(typename list<Grafo<int>::Arco>::iterator itAdy = adyacentes.begin(); itAdy != adyacentes.end(); itAdy++)
    {
        int u = itAdy->devolverAdyacente();
        if (arregloMarcas[u] == 'N')
            {
                posTop++;
                DFSTopologico(grafo, u, arregloMarcas, numeracion, ++posTop, pilaTop);
                pilaTop.push(u);

                numeracion[u] = posTop;


            }
    }
}

void forestTopologico(Grafo<int> grafo, int inicio, char arregloMarcas[], int numeracion[])
{
    list<int> verticesDELgrafo;
    grafo.devolverVertices(verticesDELgrafo);
    stack<int> pilaTop;
    int posTop = 0;
    for(typename list<int>::iterator itVertices = verticesDELgrafo.begin(); itVertices != verticesDELgrafo.end(); itVertices++)
        if (arregloMarcas[*itVertices] == 'N')
            DFSTopologico(grafo, inicio, arregloMarcas, numeracion,posTop, pilaTop);
}

int main()   /// PRICIPAL
{
    //int inicio;
    Grafo<int> G;
    int cantVertices = 7;
    int posTop;

    int arregloNumeracion[cantVertices];
    char arrMarcas[cantVertices];
    cargarArreglo(arrMarcas,arregloNumeracion, cantVertices);
    cargarGrafoSortTop(G, cantVertices);
    cout << "ESTRUCTURA DE GRAFO: " << endl;
    cout << G << endl;
    forestTopologico(G, 3, arrMarcas,arregloNumeracion);
    for(int i=1 ; i<=cantVertices; i++)
        cout << "vertice " << i << ": orden topologico " << arregloNumeracion[i] << endl;

    ///cargarGrafo(G, cantVertice);
    /**     DFS


    cout << "ingrese inicio del grafo: ";
    cin >> inicio;
    cout << "Recorrido del grafo con DFS desde " << inicio << ": " << inicio; DFSmostrar(G, inicio , arrMarcas, cantVertice);
    **/

    /**     BFS
    cout << "ingrese inicio del grafo: ";
    cin >> inicio;
    BFSmostrar(G, inicio, arrMarcas);
    **/

    return 0;
}
