#ifndef ARCOOCD_H
#define ARCOOCD_H


class arcoOCD
{
     public:
        arcoOCD();
        arcoOCD(int origen, int costo, int destino);
        ~arcoOCD();
        const int devolverOrigen() const;
        const int devolverCosto() const;
        const int devolverDestino() const;
        const bool operator < (const arcoOCD & otroArco) const;

    private:
        int origen;
        int costo;
        int destino;
};

//metodos del arco O-C-D

arcoOCD::arcoOCD() {}

arcoOCD::arcoOCD(int origen, int destino, int costo)
{
    this->origen = origen;
    this->costo = costo;
    this->destino = destino;
}

arcoOCD::~arcoOCD() {}

const int arcoOCD::devolverOrigen() const

{
    return origen;
}

const int arcoOCD::devolverCosto() const
{
    return costo;
}

const int arcoOCD::devolverDestino() const
{
    return destino;
}

const bool arcoOCD::operator<(const arcoOCD & otroArco) const
{
    if ((devolverCosto()) < (otroArco.devolverCosto()))
        return true;
    else
        return false;
}

#endif // ARCOOCD_H
