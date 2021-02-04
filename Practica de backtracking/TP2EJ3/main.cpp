#include <iostream>
#include <math.h>
using namespace std;

void inicializarArr(int arr[], int cReinas)
{
    for (int i=1; i<cReinas+1; i++)
        arr[i] = -1;
}
void nReinas(int solucion[], int cReinas, int ReinaActual)
{
    if (solucion[cReinas+1] != -1)   ///TODAS LAS REINA ASIGNADAS
    {
        bool sirveLaSolucion = true;

        while (sirveLaSolucion)
            for (int i=1; i<cReinas+1; i++)
                for (int k=1; k<cReinas+1; k++)
                    if (i != k)
                    {
                        sirveLaSolucion = true;
                        int diagonal = (fabs(solucion[i] - solucion[k]));
                        int     diag = fabs(i-k);
                        if ((solucion[i] = solucion[k]) || (diagonal = diag))
                            sirveLaSolucion = false;
                    }
        if (sirveLaSolucion)
        {
            cout << "La solucion es: ";
            for (int i=1; i<cReinas+1; i++)
                cout << solucion[i];
        }
    }
    else
    {
            for (int c=1; c<cReinas+1; c++)
            {
                solucion[ReinaActual]=c;
                nReinas(solucion, cReinas, ReinaActual+1);
            }
    }
}
int main()
{
    int PrimaReina=1;
    int cReinas =4;
    int arregloSolucion[cReinas];
    inicializarArr(arregloSolucion, cReinas);
    nReinas(arregloSolucion, cReinas, PrimaReina);
    return 0;
}
