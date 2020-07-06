#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include "Punto.h"

class Nodo
{
private:
    Nodo *left;
    Nodo *right;
    Punto punto;
    int eje;
public:
    Nodo(Punto punto, Nodo *left, Nodo *right, int eje);
    Nodo *&getLeft();
    Nodo *&getRight();
    Punto getPunto();
    int getEje();
};

Nodo::Nodo(Punto punto, Nodo *left = NULL, Nodo *right = NULL, int eje = 0)
{
    this->punto = punto;
    this->left = left;
    this->right = right;
    this->eje = eje;
}

Nodo *&Nodo::getLeft()
{
    return this->left;
}

Nodo *&Nodo::getRight()
{
    return this->right;
}

Punto Nodo::getPunto()
{
    return this->punto;
}

int Nodo::getEje()
{
    return this->eje;
}

#endif // NODO_H_INCLUDED
