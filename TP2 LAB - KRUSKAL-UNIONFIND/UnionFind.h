#ifndef UNIONFIND_H
#define UNIONFIND_H
using namespace std;


class UnionFind
{
    public:
        UnionFind(int);  ///int es el tamaño del arreglo de padres
        ~UnionFind(); ///id anterior
        int findPadre(int); /// int es el vertice al cual yo le quiero encontrar el padre, int es la cantidad de elementos
        void unionConjunto(int, int);  /// ambos son "padres" de "conjuntos" vertices que quiero unir
    private:
        int * padre; ///arreglo de enteros
};

/// Metodos

UnionFind::UnionFind(int cantidad)
{
    padre = new int[cantidad+1];
    padre[0]= cantidad + 1;
    for(int i = 1; i<cantidad+1; i++)
        padre[i]=-1;        //al inicio todos son padres de su conjunto
}

UnionFind::~UnionFind()
{
    //delete [] padre;
}

int UnionFind::findPadre(int valor)
{
   // cout << padre[0] << " FIND: " << valor << endl;    DEPURACION

    int aux = valor;
    while ((padre[aux])>0)   /// mientras que aux no sea padre
        aux=padre[aux];

    int v = valor;
    while (v!=aux)     /// compresion de camino
    {
        int aux2 = padre[v];
        padre[v] = aux;
        v = aux2;
    }

    /*for(int i=1; i<padre[0]+1; i++)
        cout << "el padre de " << i << " es " << padre[i] << endl;      MAS DEPURACION
    cout << padre[aux] << endl;
    cout << aux << "es el nuevo padre "<< endl << endl;*/
    return aux;
}

void UnionFind::unionConjunto(int i, int j)
{
        if (padre[j] <= padre[i])
        {
            padre[j] = padre[j] + padre[i];
            padre[i] = j;
        }
        else
        {
            padre[i] = padre[i] + padre[j];
            padre[j] = i;
        }
        /*for(int i=0; i<padre[0]+1; i++)            PARA DEPURAR
        cout << "el padre de " << i << " es " << padre[i] << endl;*/
}



#endif // UNIONFIND_H
