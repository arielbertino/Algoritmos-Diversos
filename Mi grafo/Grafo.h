#ifndef GRAFO_H_
#define GRAFO_H_

#include <list>
#include <map>

using namespace std;

/*
    solo si se necesita en el metodo
    typename map <int, list<Arco> >::const_iterator iteradorVertices = Contenedor.posicion();
    por ejemplo iteradorVertices = mapaVertices.begin();
    list <Arco>::iterator iteradoArcos;
*/

template <typename C> class Grafo
{
public:
	class Arco
	{
	public:
		Arco();
		Arco(int adyacente, const C & costo);
		int devolverAdyacente() const;
		const C & devolverCosto() const;
	private:
		int vertice;
		C costo;
	}; // class Arco

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	Grafo();
	Grafo(const Grafo & otroGrafo);

	~Grafo();

	Grafo & operator = (const Grafo & otroGrafo);

	// Devuelve true si la cantidad de vértices es cero
	bool estaVacio() const;
	// Indica la cantidad de vértices del grafo
	int devolverLongitud() const;

	bool existeVertice(int vertice) const;

	bool existeArco(int origen, int destino) const;

	// PRE CONDICION: existeArco(origen, destino)
	const C & costoArco(int origen, int destino) const;

	void devolverVertices(list<int> & vertices) const;

	void devolverAdyacentes(int origen, list<Arco> & adyacentes) const;

	void agregarVertice(int vertice);

	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminarVertice(int vertice);

	// PRE CONDICION: existeArco(origen, destino)
	void modificarCostoArco(int origen, int destino, const C & costo);

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	void agregarArco(int origen, int destino, const C & costo);

	// POST CONDICION: !existeArco(origen, destino)
	void eliminarArco(int origen, int destino);

	void vaciar();

private:
	map <int, list <Arco> >mapaVertices;   // mapa de listas
}; // class Grafo


/*
 * Arco
 */

template <typename C> Grafo<C>::Arco::Arco() {}

template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo)
{
    this->costo = costo;
    this->vertice = adyacente;
}

template <typename C> int Grafo<C>::Arco::devolverAdyacente() const
{
    return vertice;  //   ¿¿ return (this->vertice)   ??
}

template <typename C> const C & Grafo<C>::Arco::devolverCosto() const
{
    return costo;  // ¿¿ return (this->costo) ??
}


/*
 * Grafo
 */

template <typename C> Grafo<C>::Grafo() {}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo)
{
    this->operator = (otroGrafo);  // ¿ esto seria que mi grafo toma los valores que tiene otroGrafo?
}

template <typename C> Grafo<C>::~Grafo() {}

template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{
    mapaVertices.clear();  //vacio mi grafo actual
    typename map <int, list <Arco> >::const_iterator itOtroGrafo = otroGrafo.begin();  //iterador en el principio de otrografo
    while(itOtroGrafo != otroGrafo.end())  // mientras no llegue a fin de otrografo
    {
        mapaVertices[itOtroGrafo->first] = itOtroGrafo->second;  // agrego a mi grafo actual la clave del otrovertice con el elemento que tiene esa clave
        /*
        typename list<Arco>::const_iterator itListMapa = mapaVertice->second.begin();
        typename list<Arco>::const_iterator itListOtroGrafo = otroGrafo->second.begin();
        while (itListOtroGrafo != otroGrafo.second.end()) {
        {
            *itListMapa = *itListOtroGrafo;            //alcanzaria con la linea 120 o hay que agregar uno por uno
            itListMapa++;                              // como hice en este bloque
            itListOtroGrafo++;
        }
        */
        itOtroGrafo++;
    }
    return *this;
}

template <typename C> bool Grafo<C>::estaVacio() const
{
    return (mapaVertices.empty());
};

template <typename C> int Grafo<C>::devolverLongitud() const
{
    return (mapaVertices.size());
}

template <typename C> bool Grafo<C>::existeVertice(int vertice) const
{
    typename map <int, list<Arco> >::const_iterator iteradorVertices;
    iteradorVertices = mapaVertices.find(vertice);
    if (iteradorVertices == mapaVertices.end())
        return false;
    else
        return true;
}

template <typename C> bool Grafo<C>::existeArco(int origen, int destino) const
{
    typename map <int, list<Arco> >::const_iterator iteradorVertices = mapaVertices.find(origen);
    typename map <int, list<Arco> >::const_iterator iteradorVertices2 = mapaVertices.find(destino);
    if ((iteradorVertices != mapaVertices.end()) && (iteradorVertices2 != mapaVertices.end()))
        {
            typename list <Arco>::const_iterator iteradoArcos = iteradorVertices->second.begin();
            while (iteradoArcos->devolverAdyacente() != destino)//rev
                iteradoArcos++;
            if (iteradoArcos != iteradorVertices->second.end())
                return true;
            else return false;
        }
    else return false;
}

template <typename C> const C & Grafo<C>::costoArco(int origen, int destino) const
{
    typename map<int, list<Arco> >::const_iterator iteradorVertices = mapaVertices.find(origen);
    if (iteradorVertices != mapaVertices.end())
    {
        typename list <Arco>::const_iterator iteradoArcos = iteradorVertices->second.begin();
        while ((iteradoArcos!=iteradorVertices->second.end()) && (iteradoArcos->devolverAdyacente() != destino))
            iteradoArcos++;
        if (iteradoArcos != iteradorVertices->second.end())
            return (iteradoArcos->devolverCosto());
        // else return 0; // ¿¿ retornar cero si no existe el arco ??
    }                   // ¿¿ o puede haber un arco con costo 0??
    // else return 0; // ¿¿ retornar cero si no existe el arco ??
}

template <typename C> void Grafo<C>::devolverVertices(list<int> & vertices) const
{
    typename map<int, list<Arco> >::const_iterator iteradorVertices = mapaVertices.begin();
    while (iteradorVertices != mapaVertices.end())
    {
        vertices.push_back(iteradorVertices->first);
        iteradorVertices++;
    }
}

template <typename C> void Grafo<C>::devolverAdyacentes(int origen, list<Arco> & adyacentes) const
{
    typename map<int,list<Arco> >::const_iterator iteradorVertices = mapaVertices.find(origen);
    if (iteradorVertices != mapaVertices.end())
    {
        typename list<Arco>::const_iterator iteradoArcos = iteradorVertices->second.begin();
        while (iteradoArcos != iteradorVertices->second.end())
        {
            adyacentes.push_back(Arco(iteradoArcos->first, iteradoArcos->second));
            iteradoArcos++;
        }
    }
}

template <typename C> void Grafo<C>::agregarVertice(int vertice)
{
    typename map <int, list<Arco> >::const_iterator iteradorVertices = mapaVertices.find(vertice);
    if (iteradorVertices == mapaVertices.end())
    {
        list <Arco> Adyacentes;
        mapaVertices[vertice]=  Adyacentes;
    }
}

template <typename C> void Grafo<C>::eliminarVertice(int vertice)
{
    mapaVertices.erase(vertice);  // ¿¿ se elimina asi o primero hay que borrar la lista de arcos del vertice a aliminar ??
    typename map<int,list<Arco> >::iterator iteradorVertices = mapaVertices.begin();
    while (iteradorVertices != mapaVertices.end())
    {
        typename list<Arco>::iterator iteradorArcos = iteradorVertices->second.begin();
        while (iteradorArcos->devolverAdyacente() != vertice)
            iteradorArcos++;
        if (iteradorArcos != iteradorVertices->second.end())
            iteradorVertices->second.erase(iteradorArcos);
            // o tambien podria ser iteradorVertices->second.remove(vertice); y queda invalido el iteradorArcos
        iteradorVertices++;
    }
}

template <typename C> void Grafo<C>::modificarCostoArco(int origen, int destino, const C & costo)
{
    // origen y destino existen y tiene un arco que los vincula
    typename list <Arco>::iterator iteradorArcos = mapaVertices.find(origen)->second.begin();
    iteradorArcos->second.remove(destino);
    iteradorArcos->second.push_back(Arco(destino, costo));
}



template <typename C> void Grafo<C>::agregarArco(int origen, int destino, const C & costo)
{
    typename map <int, list<Arco> >::iterator iteradorVertices = mapaVertices.find(origen);
    typename map <int, list<Arco> >::iterator iteradorVertices2 = mapaVertices.find(destino);
    if ((iteradorVertices != mapaVertices.end()) && (iteradorVertices2 != mapaVertices.end())) // si ambos existe se puede agregar el arco
    {
        iteradorVertices->second.push_back(Arco(destino,costo));
        //typename list <Arco>::iterator iteradoArcos = iteradorVertices->second.begin();
        //iteradoArcos->second.push_back(Arco(destino, costo));
    }

}

template <typename C> void Grafo<C>::eliminarArco(int origen, int destino)
{
    // origen y destino existen y tiene un arco que los vincula y es el que se quiere eliminar
    typename list <Arco>::iterator iteradoArcos = mapaVertices.find(origen)->second;
    iteradoArcos->second.remove(destino);
}

template <typename C> void Grafo<C>::vaciar()
{
    mapaVertices.clear();
    //¿¿o si no, obligatoriamente tengo que borrar lista, vertice uno por uno??

}

#endif /* GRAFO_H_ */
