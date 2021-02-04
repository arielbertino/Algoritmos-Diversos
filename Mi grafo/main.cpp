#include <iostream>
#include "Grafo.h"
#include <list>
using namespace std;

int main()
{
    int valor;
    Grafo<int> grafito;
    list<int> vertices;
   // list<Arco> arcosAdy;   no me permite definir list de Arco
    int vNuevo = 10;

    grafito.agregarVertice(1);
    grafito.agregarVertice(2);
    grafito.agregarVertice(3);
    grafito.agregarVertice(4);
    grafito.agregarVertice(5);

    grafito.agregarArco(1,2,12);
    grafito.agregarArco(1,4,14);
    grafito.agregarArco(1,5,15);
    grafito.agregarArco(2,3,23);
    grafito.agregarArco(2,3,34);
    grafito.agregarArco(4,5,45);
    grafito.agregarArco(5,2,52);

    if (grafito.estaVacio()) cout << "esta vacio" << endl;
    else cout << "esta lleno" << endl;
    cout << grafito.estaVacio() << endl;
    cout << !grafito.estaVacio() << endl;

    cout << "ingrese vertice a buscar: ";
    cin >> valor ;
    if (grafito.existeVertice(valor)) cout << "el vertice " << valor << " existe" << endl;
    else cout << "el vertice " << valor << " no existe" << endl;

    cout << "la cantidad de elementos de grafo es: " << grafito.devolverLongitud() << endl;

    if (grafito.existeArco(5,2)) cout <<"el arco buscado existe" << endl; //cuando buscas un arco que no existe se queda pensando
    else cout << "el arco buscado no existe" << endl;

    cout << grafito.costoArco(1,4) << endl;

    grafito.devolverVertices(vertices);

//    grafito.devolverAdyacentes(1, arcos);  no me permite definir list de Arco que va en el parametro

    grafito.agregarVertice(vNuevo);
    if (grafito.existeVertice(vNuevo)) cout << "el vertice " << vNuevo << " existe" << endl;
    else cout << "el vertice " << vNuevo << " no existe" << endl;


    grafito.eliminarVertice(vNuevo);
    if (grafito.existeVertice(vNuevo)) cout << "el vertice " << vNuevo << " existe" << endl;
    else cout << "el vertice " << vNuevo << " no existe" << endl;



}
