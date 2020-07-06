#ifndef KDTREE_H_INCLUDED
#define KDTREE_H_INCLUDED

#include <math.h>

#include "Punto.h"
#include "Nodo.h"

class KDTree
{
private:
    Nodo *root;
    void addingNodo(Punto punto, Nodo *&root, int eje);
    void LookingNodo(HDC hdc, Nodo *root, int xInicial, int yInicial, int a);
    void viewingRectangle(HDC hdc, Nodo *root, int xInicial, int yInicial, int xFinal, int yFinal);
    Punto searchingNodo(Punto punto, Nodo *&root, int eje);
    int distaciaEuclidiana(int xInicial, int xFinal, int yInicial, int yFinal);
public:
    KDTree();
    void addNodo(Punto punto);
    void lookNodo(HDC hdc, int xInicial, int yInicial, int xFinal, int yFinal);
    void viewRectangle(HDC hdc, int xInicial, int yInicial, int xFinal, int yFinal);

    Punto searchNodo(Punto punto);
};

// METODO DE BUSQUEDA DEL VECINO MAS CERCANO
Punto KDTree::searchNodo(Punto punto)
{
    return this->searchingNodo(punto, this->root, 0);
}

Punto KDTree::searchingNodo(Punto punto, Nodo *&root, int eje)
{
    if (root != NULL)
    {
        if (eje == 0)
        {
            if (punto.getX() <= root->getPunto().getX())
            {
                if (root->getLeft() == NULL)
                    return root->getPunto();
                else
                    this->searchingNodo(punto, root->getLeft(), 1);
            } else
            {
                if (root->getRight() == NULL)
                    return root->getPunto();
                else
                    this->searchingNodo(punto, root->getRight(), 1);
            }
        }

        if (eje == 1)
        {
            if (punto.getY() <= root->getPunto().getY())
            {
                if (root->getLeft() == NULL)
                    return root->getPunto();
                else
                    this->searchingNodo(punto, root->getLeft(), 0);
            } else
            {
                if (root->getRight() == NULL)
                    return root->getPunto();
                else
                    this->searchingNodo(punto, root->getRight(), 0);
            }
        }
    } else
    {
        return punto;
    }
}
// FIN DEL METODO DE BUSQUEDA DEL VECINO MAS CERCANO

KDTree::KDTree()
{
    this->root = NULL;
}

void KDTree::addNodo(Punto punto)
{
    this->addingNodo(punto, this->root, 0);
}

void KDTree::addingNodo(Punto punto, Nodo *&root, int eje)
{
    if (root == NULL)
    {
        root = new Nodo(punto, NULL, NULL, eje);
    } else
    {
        if (eje == 0)
        {
            if (punto.getX() <= root->getPunto().getX())
                this->addingNodo(punto, root->getLeft(), 1);
            else
                this->addingNodo(punto, root->getRight(), 1);
        }
        if (eje == 1)
        {
            if (punto.getY() <= root->getPunto().getY())
                this->addingNodo(punto, root->getLeft(), 0);
            else
                this->addingNodo(punto, root->getRight(), 0);
        }
    }
}

void KDTree::lookNodo(HDC hdc, int xInicial, int yInicial, int xFinal, int yFinal)
{
    this->LookingNodo(hdc, this->root, (xInicial+xFinal)/2, yInicial+20, xFinal-xInicial);
}

void KDTree::LookingNodo(HDC hdc, Nodo  *root, int xInicial, int yInicial, int a)
{
    if (root != NULL)
    {
        char datos[30];

        if (root->getLeft() != NULL)
        {
            MoveToEx(hdc, xInicial, yInicial, NULL);
            LineTo(hdc, xInicial-a/2, yInicial+50);
        }

        if (root->getRight() != NULL)
        {
            MoveToEx(hdc, xInicial, yInicial, NULL);
            LineTo(hdc, xInicial+a/2, yInicial+50);
        }

        Rectangle(hdc, xInicial-3, yInicial-3, xInicial+28, yInicial+48);
        sprintf(datos, "%i", int(root->getPunto().getX()));
        TextOut(hdc, xInicial, yInicial, datos, strlen(datos));
        sprintf(datos, "%i", int(root->getPunto().getY()));
        TextOut(hdc, xInicial, yInicial+15, datos, strlen(datos));

        if (root->getEje() == 0)
            TextOut(hdc, xInicial, yInicial+30, "X", 1);
        else
            TextOut(hdc, xInicial, yInicial+30, "Y", 1);

        this->LookingNodo(hdc, root->getLeft(), xInicial-a/2, yInicial+50, a/2);
        this->LookingNodo(hdc, root->getRight(), xInicial+a/2, yInicial+50, a/2);
    }
}


void KDTree::viewRectangle(HDC hdc, int xInicial, int yInicial, int xFinal, int yFinal)
{
    this->viewingRectangle(hdc, this->root, xInicial, yInicial, xFinal, yFinal);
}

void KDTree::viewingRectangle(HDC hdc, Nodo *root, int xInicial, int yInicial, int xFinal, int yFinal)
{
    if (root != NULL)
    {
        int puntoX = root->getPunto().getX();
        int puntoY = root->getPunto().getY();

        if (root->getEje() == 1)
        {
            MoveToEx(hdc, xInicial, puntoY, NULL);
            LineTo(hdc, xFinal, puntoY);
            this->viewingRectangle(hdc, root->getLeft(), xInicial, yInicial, xFinal, puntoY);
            this->viewingRectangle(hdc, root->getRight(), xInicial, puntoY, xFinal, yFinal);
        } else
        {
            MoveToEx(hdc, puntoX, yInicial, NULL);
            LineTo(hdc, puntoX, yFinal);
            this->viewingRectangle(hdc, root->getLeft(), xInicial, yInicial, puntoX, yFinal);
            this->viewingRectangle(hdc, root->getRight(), puntoX, yInicial, xFinal, yFinal);
        }

        Ellipse(hdc, puntoX-5, puntoY-5, puntoX+5, puntoY+5);
    }
}

#endif // KDTREE_H_INCLUDED
