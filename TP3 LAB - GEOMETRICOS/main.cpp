#include <iostream>
#include <list>
#include <fstream>
#include <cstdlib>
#define separador -111111
///#include "Poligono1.txt"
///#include "Poligono2.txt"
///#include "Poligono3.txt"
///#include "Modelo de trabajo con punteros iteradores.txt"
using namespace std;


struct puntito { double x,y; };

double area(puntito p0, puntito p1, puntito p2) /// orden inicial p0p1p2
{
    double area=0;
    area = (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
    return area*0.5;
}

void generarListaPuntos(ifstream & archivo, list<puntito> & puntos)
{
    if (archivo.is_open())
    {
        string numero; //numero.clear();
        string linea;
        getline(archivo, linea);
        getline(archivo, linea);
        puntito nuevoP;
        while (!archivo.eof())
        {
            getline(archivo, linea);
            int longLinea = linea.length();
            for (int i=0; i<longLinea; i++)
            {
                if (longLinea<3)
                {
                    nuevoP.x = separador;
                    nuevoP.y = separador;
                    puntos.push_back(nuevoP);
                    getline(archivo,linea);
                    longLinea = linea.length();
                    i=0;
                }
                if(linea[i+1]==',')
                {
                    numero = numero+linea[i];
                    int valor = atoi(numero.c_str());
                    nuevoP.x = valor;
                    i+=2;
                }
                if(linea[i+1]!=',') numero = numero+linea[i];
                if (i==longLinea-1)
                {

                    numero.clear();
                    if (linea[i-1] != ',')
                        numero = numero + linea[i-1]+ linea[i];
                    else numero = numero + linea[i];
                    int valor = atoi(numero.c_str());
                    nuevoP.y = valor;
                    puntos.push_back(nuevoP);
                }

            }
           numero.clear();
        }
    archivo.close();
}
}
bool esUnSeparador (puntito p0)
{
    if ((p0.x == separador)&&(p0.y == separador))
        return true;
    return false;
}
bool sonIguales(puntito p0, puntito p1)
{
    if ( (p0.x == p1.x) && (p0.y == p1.y) )
        return true;
    else
        return false;
}

double benditaArea(list<puntito> puntos, puntito pDado)
{
    /**
    puntito itor;
    itor = puntos.back();  devuelve el ultimo elemento, no como cree el colectivo que dicen que devuelve puntero al ultimo
    */
    double areaTotal=0;
    int cantPuntos=1;
    puntito ultimoP = puntos.back();
    typename list<puntito>::iterator itP = puntos.begin();   ///primer elemento (punto)
    typename list<puntito>::iterator itAux = itP;
    itAux++;            ///segundo elemento de la lista
    while(itAux!=puntos.end())
    {
        if(!esUnSeparador(*itAux)&&(itAux!=puntos.end()))
        {
            areaTotal+=area(*itP,*itAux,pDado);
            cantPuntos++;
            itP++;
            itAux++;
            /// **--**
            ///la ultima vez que pase por aca va a estar el itP en el ultimo e itAux fuera de la lista (sig al ultimo)
        }
        else
            if( (esUnSeparador(*itAux)) )
            {
                for(int i=0; i<cantPuntos; i++)
                    itAux--;
                areaTotal+=area(*itP,*itAux,pDado);
                itP++;
                itP++;
                itAux = itP;
                itAux++;
                cantPuntos=1;
            }
        if(sonIguales(*itP,ultimoP))    /// esto tambien puede ir aca **--**  ^
        {
            for(int i=0; i<cantPuntos; i++)
                itAux--;
            areaTotal+=area(*itP,*itAux,pDado);
            itAux=puntos.end();
        }
    }
    cout<<endl;
    return areaTotal;
}

void generarListaPoligonos(list<puntito> listaPuntos, list<list<puntito> >& listaPoligonos)
{
    typename list<puntito>::iterator itList = listaPuntos.begin();
    ///cargar lista de listas
    while(itList != listaPuntos.end())
    {

        list<puntito> listaParcial;
        for (typename list<puntito>::iterator itAux = listaPuntos.begin(); itAux != listaPuntos.end(); itAux++)
        {

            if (sonIguales(*itList, *itAux)) {
                list<puntito>::iterator aux = itAux;
                aux++;
                if (aux != listaPuntos.end())
                    itAux++;
            }else
                listaParcial.push_back(*itAux);
        }
        listaPoligonos.push_back(listaParcial);
        itList++;
    }
}

void calcularAreas(double areaGrande, list<puntito>poligonoGrande , list<list<puntito> > poligonos, int &lActual)
{
    puntito puntoDado;
    cout << "ingrese punto dado(x): ";
    cin >> puntoDado.x;
    cout << "ingrese punto dado(y): ";
    cin >> puntoDado.y;
    cout<<endl;
    double areaMasChica = 1000;
    typename list<list<puntito> >::iterator itListG = poligonos.begin();
    int i=1;
    while (itListG != poligonos.end())
    {
          /// llevo un contador y cuando modifica el area mascchica guardo ese contador(ej si contador es 1 esta en la lista 1 y falta el punto 1)
        double areaParcial = benditaArea(*itListG,puntoDado);
        cout <<"poligono " << i << ": " << areaParcial << endl;
        if (areaParcial<areaMasChica)
        {
            areaMasChica=areaParcial;
            lActual=i;
        }
        itListG++;
        i++;
    }
}

int main()
{
    list<puntito> listaPuntos;
    list<list<puntito> >listaPoligonos;
    int listaActual =0;
    ifstream archivo("Poligono5.txt");
    generarListaPuntos(archivo,listaPuntos);
    typename list<puntito>::iterator itList = listaPuntos.begin();
    cout << "Puntos del archivo: " << endl << endl;
    while(itList != listaPuntos.end())
    {
        cout << (*itList).x << "," << itList->y << endl;
        itList++;
    }
    cout<<endl;
    puntito puntoDado;
    cout << "ingrese punto dado(x): ";
    cin >> puntoDado.x;
    cout << "ingrese punto dado(y): ";
    cin >> puntoDado.y;
    cout<<endl;
    system("cls");
    cout << endl;
    double areaGrande = benditaArea(listaPuntos, puntoDado);
    cout <<"Area Totales: " << areaGrande << endl;
    cout << "aaaaaaaa" << endl;
    generarListaPoligonos(listaPuntos,listaPoligonos);
    cout << "bbbbbbbb" << endl;
    calcularAreas(areaGrande,listaPuntos,listaPoligonos,listaActual);
    cout << listaActual;
    return 0;
}
