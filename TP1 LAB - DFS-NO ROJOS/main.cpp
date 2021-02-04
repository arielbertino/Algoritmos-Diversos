#include "GrafoF.h"
#include "iostream"
#include <list>
#include <map>
#include <set>

using namespace std;

int const cant = 11;

template <typename C>
ostream & operator << (ostream & salida, const Grafo<C> & grafo)
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

struct regVertex  //datos que van a ir en el arrglo =???
{
    char letra;
    string color;
    char marca;
};

void noVisitarVertices(regVertex arregloDatos[]) // CARGAR MARCAS "NO VISITADO"
{
    for(int i=1; i <= cant+1 ; i++)
        arregloDatos[i].marca = 'N';
}

void cargarArregloDatos(regVertex arregloDatos[]) //DATOS DEL TP2
{
    arregloDatos[1].color = "BLANCO";
    arregloDatos[1].letra = 'A';
    arregloDatos[2].color = "ROJO";
    arregloDatos[2].letra = 'B';
    arregloDatos[3].color = "BLANCO";
    arregloDatos[3].letra = 'C';
    arregloDatos[4].color = "VERDE";
    arregloDatos[4].letra = 'E';
    arregloDatos[5].color = "AZUL";
    arregloDatos[5].letra = 'D';
    arregloDatos[6].color = "VERDE";
    arregloDatos[6].letra = 'J';
    arregloDatos[7].color = "AMARILLO";
    arregloDatos[7].letra = 'F';
    arregloDatos[8].color = "AZUL";
    arregloDatos[8].letra = 'I';
    arregloDatos[9].color = "ROJO";
    arregloDatos[9].letra = 'H';
    arregloDatos[10].color = "ROJO";
    arregloDatos[10].letra = 'G';
}

void DFScoloreado(Grafo<int> graf, int origen, int destino, regVertex arregloDatos[], int & cantRojos, list<int> & caminoActual, set<list<int> > & caminos)
{
    if ((origen == destino)&&(cantRojos < 2))
        caminos.insert(caminoActual);
    else
        {
        list<Grafo<int>::Arco> adyacentes;
        graf.devolverAdyacentes(origen, adyacentes);
        for (typename list<typename Grafo<int>::Arco>::iterator it = adyacentes.begin(); it != adyacentes.end(); it++)
            {
                int u = it->devolverAdyacente();
                if ((arregloDatos[u].marca == 'N')&&(cantRojos < 2))
                    {
                        arregloDatos[origen].marca = 'V';  //Visitado
                        caminoActual.push_back(u);
                        if (arregloDatos[u].color == "ROJO")
                            cantRojos++;
                        DFScoloreado(graf, u, destino, arregloDatos,  cantRojos, caminoActual, caminos);
                        arregloDatos[origen].marca = 'N'; //No visitado
                        caminoActual.pop_back();
                        if (arregloDatos[u].color == "ROJO")
                            cantRojos--;
                    }
            }
        }
}

void mostrarCaminos(set<list<int> > & caminos)
{
    typename set<list<int> >::const_iterator itSet = caminos.begin();
    while (itSet != caminos.end())
        {
        typename list<int>::const_iterator itList = itSet->begin();
        while (itList != itSet->end())
            {
            cout << *itList;
            itList++;
            }
        cout << "    FIN CAMINO" << endl;
        itSet++;
        }
}

// PLANTEO : EN EL ARREGLO DE REGISTROS GUARDAR LOS DATOS DE LOS NODOS
//           DFS ADAPTADO
//           GUARDAR LOS CAMINOS UN CONJUNTOS DE CAMINOS
//           MOSTRAR LOS CAMINO POR PANTALLA

int main(int argc, char **argv)
{
    // DEFINICIONES
    regVertex arregloDatos[cant];
	Grafo<int> g;
	list<int> caminoActual;
	set<list<int> > caminos;
	int cantRojos = 0;

	//GRAFO CARGADO
	g.agregarVertice(1);
	g.agregarVertice(2);
	g.agregarVertice(3);
	g.agregarVertice(4);
	g.agregarVertice(5);
	g.agregarVertice(6);
	g.agregarVertice(7);
	g.agregarVertice(8);
	g.agregarVertice(9);
	g.agregarVertice(10);

	// ARCOS CARGADOS
	g.agregarArco(1, 2, 0);
	g.agregarArco(1, 4, 0);
	g.agregarArco(2, 3, 0);
	g.agregarArco(4, 7, 0);
	g.agregarArco(5, 3, 0);
	g.agregarArco(5, 4, 0);
	g.agregarArco(6, 3, 0);
	g.agregarArco(7, 6, 0);
	g.agregarArco(7, 10, 0);
	g.agregarArco(8, 3, 0);
	g.agregarArco(9, 8, 0);
	g.agregarArco(10, 8, 0);
	g.agregarArco(10, 9, 0);


    //CARGAR ARREGLO DE DATOS-GRAFO NO VISITADOS
    noVisitarVertices(arregloDatos);

    //CARGAR ARREGLO DE DATOS-GRAFO COLOR-LETRA
    cargarArregloDatos(arregloDatos);

    // GENERAR CONJUNTO DE CAMINOS
    DFScoloreado(g, 1, 3, arregloDatos, cantRojos, caminoActual, caminos);

    // MOSTRAR CONJUNTO DE CAMINOS
    mostrarCaminos(caminos);

	// MOSTRAR EL GRAFO
	cout << "Estructura del grafo:\n" << g << "\n";

	return 0;

}
