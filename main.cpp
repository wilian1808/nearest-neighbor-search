#include <iostream>
#include <windows.h>
#include <vector>
#include <math.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stdio.h>

#include "resource.h"
#include "Punto.h"
#include "KDTree.h"

HINSTANCE hInst;

int xInicial;
int xFinal;
int yInicial;
int yFinal;

KDTree tree;

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc;
        hdc = BeginPaint(hwndDlg, &ps);
        tree.lookNodo(hdc, 380, 20, 720, 400);
        Rectangle(hdc, xInicial, yInicial, xFinal, yFinal);
        tree.viewRectangle(hdc, xInicial, yInicial, xFinal, yFinal);
        EndPaint(hwndDlg, &ps);
    }
    return TRUE;

    case WM_LBUTTONDOWN:
    {
        long xValue = GET_X_LPARAM(lParam);
        long yValue = GET_Y_LPARAM(lParam);

        if (xValue<xFinal && xValue > xInicial && yValue < yFinal && yValue > yInicial)
        tree.addNodo(Punto(xValue, yValue));
        InvalidateRect(hwndDlg, NULL, true);
    }
    return TRUE;

    case WM_INITDIALOG:
    {
        xInicial = 10;
        yInicial = 50;
        xFinal = 210;
        yFinal = 250;
    }
    return TRUE;

    case WM_MOUSEMOVE:
    {
        long xValue = GET_X_LPARAM(lParam);
        long yValue = GET_Y_LPARAM(lParam);
        SetDlgItemInt(hwndDlg, EDITX, (int)xValue, FALSE);
        SetDlgItemInt(hwndDlg, EDITY, (int)yValue, FALSE);

        Punto p = tree.searchNodo(Punto(xValue, yValue));

        SetDlgItemInt(hwndDlg, VALPUNTOX, (int)p.getX(), FALSE);
        SetDlgItemInt(hwndDlg, VALPUNTOY, (int)p.getY(), FALSE);
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        }
    }
    return TRUE;
    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
