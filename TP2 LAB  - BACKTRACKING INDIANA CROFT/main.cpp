#include <iostream>
#include <list>
#include <set>
#include <fstream>
#include <cstdlib>
#define  izquierda 0
#define      abajo 1
#define     arriba 2
#define    derecha 3
#define diagSupDer 4
#define diagInfIzq 5

//#include "entrada.txt"

using namespace std;

void cargarTablero(/*ifstream & archivo,*/ int ** & tablero, int filas, int columnas, int & sumaTablero)
{
   /* string cadena;
    archivo.is_open();
    while (!archivo.eof())
    {
        archivo >> intfil >> coma >>  intcol;
        getline(archivo,cadena);
        for (int i=0; i<cadena.length();i++)
        {
            cout << cadena[i];
            atoi(cadena[i]);
        }*/
    tablero = new int*[filas];  ///inicializacion
    for (int f=0; f<filas; f++)
        tablero[f] = new int[columnas];
    for (int f=0;f<filas;f++)        ///cargado en si con el ejemplo del pdf
        for (int c=0;c<columnas;c++)
        {
            //if (f==c)
                tablero[f][c]= 1;
            //else
             //   tablero[f][c]= 2;
            sumaTablero+=tablero[f][c];
        }
//    archivo.close();
}

void generarMovPosibles(int ** & tablero, int limiteF, int limiteC, int filaAc, int columnaAc, bool arrMov[])
{

    if ((filaAc+1 <= limiteF)&&(tablero[filaAc+1][columnaAc]!=0)) arrMov[abajo] = true;
    else arrMov[abajo] = false;

    if ((filaAc-1 >= 0)&&(tablero[filaAc-1][columnaAc]!=0)) arrMov[arriba] = true;
    else arrMov[arriba] = false;

    if ((columnaAc-1 >= 0)&&(tablero[filaAc][columnaAc-1]!=0)) arrMov[izquierda] = true;
    else arrMov[izquierda] = false;

    if ((columnaAc+1 <= limiteC)&&(tablero[filaAc][columnaAc+1]!=0)) arrMov[derecha] = true;
    else arrMov[derecha] = false;

 /*   if((filaAc+1 <= limiteC)&&(columnaAc-1 >= 0)&&(tablero[filaAc+1][columnaAc-1]!=0)) arrMov[diagInfIzq] = true;
    else arrMov[diagInfIzq] = false;

    if ((filaAc-1 >= 0)&&(columnaAc+1 <= limiteC)&&(tablero[filaAc-1][columnaAc+1]!=0)) arrMov[diagSupDer] = true;
    else arrMov[diagSupDer] = false;

    for (int i=izquierda ; i<= diagInfIzq; i++)
        cout << arrMov[i]<< "-";*/

}

bool sePuedePodar (int**&tablero, int filaAc, int columnaAc,int limiteF, int limiteC)
{
    int sumaAdy=0;
    if (filaAc+1 <= limiteF)     ///abajo
        sumaAdy += tablero[filaAc+1][columnaAc];
    if (filaAc-1 >= 0)          ///arriba
        sumaAdy += tablero[filaAc-1][columnaAc];
    if (columnaAc-1 >= 0)       /// izquierda
        sumaAdy += tablero[filaAc][columnaAc-1];
    if (columnaAc+1 <= limiteC)  ///derecha
        sumaAdy += tablero[filaAc][columnaAc+1];
  /*  if ((columnaAc+1 <= limiteC)&&(filaAc-1 >= 0))  ///diagonal derecha superior
        sumaAdy += tablero[filaAc-1][columnaAc+1];
    if ((columnaAc-1 >= 0)&&(filaAc+1 <= limiteF))              ///diagonal izquierda inferior
        sumaAdy += tablero[filaAc+1][columnaAc-1];*/
    if (sumaAdy < tablero[filaAc][columnaAc])
        return true;
    else
        return false;
}
void indianaBack(int ** & tablero, int filaInicio, int columInicio, int filaSalida, int colSalida,
                 int limiteF, int limiteC, int & sumaTab, list<int> & solParcial ,set<list<int> > & solucionTotal, int & cantEstados)
{
    sumaTab-=1;
    sumaTab-=1;
    sumaTab-=1;
   // if (tablero[filaInicio][columInicio]>0)
        tablero[filaInicio][columInicio]-=1;
    if ((filaInicio==filaSalida)&&(columInicio==colSalida)&&(sumaTab==0))  ///hoja solucion factible
        solucionTotal.insert(solParcial);
    else /// no es hoja hay que generar estado nuevos
    {   bool movPosibles[4];
        generarMovPosibles(tablero,limiteF,limiteC,filaInicio,columInicio,movPosibles);
        for(int i=izquierda;i<=derecha;i++)
        {

            if((i == izquierda) && (movPosibles[i]) /*&& (!sePuedePodar(tablero,filaInicio,columInicio-1, limiteF, limiteC))*/)
            {
                cout << " i";
                solParcial.push_back(filaInicio);
                solParcial.push_back(columInicio-1);
                indianaBack(tablero,filaInicio,columInicio-1,filaSalida,colSalida,limiteF,limiteC,sumaTab,solParcial,solucionTotal,cantEstados+=1);
                solParcial.pop_back();
                solParcial.pop_back();
            }

            else if((i == arriba)&&(movPosibles[i])/* && (!sePuedePodar(tablero,filaInicio-1,columInicio,limiteF,limiteC))*/)
                {
                    cout << " a";
                solParcial.push_back(filaInicio-1);
                solParcial.push_back(columInicio);
                   for (int f=0;f<limiteF;f++)
                    for (int c=0;c<limiteC;c++)
                        cout << tablero[f][c];
                indianaBack(tablero,filaInicio-1,columInicio,filaSalida,colSalida,limiteF,limiteC,sumaTab,solParcial,solucionTotal,cantEstados+=1);
                   for (int f=0;f<limiteF;f++)
                    for (int c=0;c<limiteC;c++)
                        cout << tablero[f][c];
                solParcial.pop_back();
                solParcial.pop_back();

                }
                else if((i == abajo) && (movPosibles[i]) /*&& (!sePuedePodar(tablero,filaInicio+1,columInicio,limiteF,limiteC)*/)
                    {
                        cout << "ab";
                    solParcial.push_back(filaInicio+1);
                    solParcial.push_back(columInicio);
                       for (int f=0;f<limiteF;f++)
                    for (int c=0;c<limiteC;c++)
                        cout << tablero[f][c];
                    indianaBack(tablero,filaInicio+1,columInicio,filaSalida,colSalida,limiteF,limiteC,sumaTab,solParcial,solucionTotal,cantEstados+=1);
                       for (int f=0;f<limiteF;f++)
                    for (int c=0;c<limiteC;c++)
                        cout << tablero[f][c];
                    solParcial.pop_back();
                    solParcial.pop_back();
                    }
                    else if((i == derecha)&&(movPosibles[i]) /*&& (!sePuedePodar(tablero,filaInicio,columInicio+1,limiteF,limiteC)*/)
                        {cout << " d";
                        solParcial.push_back(filaInicio);
                        solParcial.push_back(columInicio+1);
                        indianaBack(tablero,filaInicio,columInicio+1,filaSalida,colSalida,limiteF,limiteC,sumaTab,solParcial,solucionTotal,cantEstados+=1);
                        solParcial.pop_back();
                        solParcial.pop_back();
                        }/*
                        else if((i == diagInfIzq)&&(movPosibles[i])/* && (!sePuedePodar(tablero,filaInicio+1,columInicio-1,limiteF,limiteC)))*/
                         /*   {
                                cout << "diizqinf";
                            solParcial.push_back(filaInicio+1);
                            solParcial.push_back(columInicio-1);
                            indianaBack(tablero,filaInicio+1,columInicio-1,filaSalida,colSalida,limiteF,limiteC,sumaTab,solParcial,solucionTotal,cantEstados+=1);
                            solParcial.pop_back();
                            solParcial.pop_back();
                            }
                            else if((i == diagSupDer)&&(movPosibles[i]) /*&& (!sePuedePodar(tablero,filaInicio-1,columInicio+1,limiteF,limiteC)))
                             /*   {
                                    cout << "didesup";
                                solParcial.push_back(filaInicio-1);
                                solParcial.push_back(columInicio+1);
                                indianaBack(tablero,filaInicio-1,columInicio+1,filaSalida,colSalida,limiteF,limiteC,sumaTab,solParcial,solucionTotal,cantEstados+=1);
                                solParcial.pop_back();
                                solParcial.pop_back();
                                }*/
    sumaTab+=1;
    //if (tablero[filaInicio][columInicio]>0)
    tablero[filaInicio][columInicio]+=1;
        }
    }
}

int main()
{
    ifstream archEntrada("entrada.txt");
    int ** tablero = 0;
    int filas=3;
    int columnas=3;
    int sumaTab = 0;

    int estados =1;
    set<list<int> > soluciones;
    list<int> solParcial;

    cargarTablero(tablero,filas,columnas,sumaTab);

    indianaBack(tablero,2,0,0,2,2,2,sumaTab,solParcial,soluciones,estados);

    for (typename set<list<int> >::iterator itlistGrande = soluciones.begin(); itlistGrande != soluciones.end(); itlistGrande++)
    {
        for (typename list<int>::const_iterator itList = itlistGrande->begin(); itList != itlistGrande->end(); itList++)
            cout << *itList<< " ";
        cout << endl;
    }
    cout << estados << "estados visitados";

    return 0;

}
