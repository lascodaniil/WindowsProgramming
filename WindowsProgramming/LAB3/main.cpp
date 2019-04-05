
#include <tchar.h>
#include <windows.h>
#include <math.h>
#include <bits/stdc++.h>
#include <string>
using namespace std;
ofstream fout ("out1.txt");

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;


    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS|CS_HREDRAW| CS_VREDRAW;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) GetStockObject(RGB(125,125,125));

    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx (
               0,
               szClassName,
               _T("Curbe Bezier | Lucrarea de laborator NR.3"),
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT,
               CW_USEDEFAULT,
               800,
               400,
               NULL,
               NULL,
               hThisInstance,
               NULL
           );

    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

float X[4] = {200,250,450,500} ;
float Y[4] =  {100,150,150,100} ;
float x,y,u=0,i=0;
static POINT pt [4] ;


LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rc;


    switch (message)
    {

    case WM_CREATE:{

        pt[0].x = 300; pt[0].y = 200;
        pt[1].x = 350; pt[1].y=250;
        pt[2].x = 550; pt[2].y = 250;
        pt[3].x = 600; pt[3].y = 200;

        break;
    }

    case WM_DESTROY:
    {   KillTimer(hwnd,0);
        PostQuitMessage (0);
        break;
    }

    case WM_KEYDOWN:{
        switch(wParam){
            case VK_LEFT:
                X[2] +=5;
                break;
            case VK_RIGHT:
                X[2] -=5;
                break;
            case VK_DOWN:
                Y[3]-=5;
                break;
            case VK_UP:
                Y[3]+=5;
                break;

        }
        InvalidateRect(hwnd,NULL,false);
    }

    case WM_CHAR: {
        switch(wParam){

            case 'W' : {
                Y[1] +=5;
                break;
            }
            case 'A' : {
                X[1] -=5;
                break;
            }

            case 'D' : {
                X[1] +=5;
                break;
            }

            case 'S' : {
                Y[1] -=5;
                break;
            }

        InvalidateRect(hwnd,NULL, false);

        }
    }


   case WM_MOUSEMOVE:
    {
        if (wParam == MK_LBUTTON)
        {
            X[1] = LOWORD(lParam);
            Y[1] = HIWORD(lParam);
            Sleep(1);
            InvalidateRect(hwnd, NULL, false);
        }
        if (wParam == MK_RBUTTON)
        {
            X[2] = LOWORD(lParam);
            Y[2] = HIWORD(lParam);
            Sleep(1);
            InvalidateRect(hwnd, NULL, false);
        }

        break;
    }

    case WM_PAINT:
    {
        GetClientRect(hwnd, &rc);
        hdc = BeginPaint (hwnd, &ps) ;
        FillRect(hdc,&rc,CreateSolidBrush(RGB(255,255,255)));
        MoveToEx(hdc,X[1],Y[1],NULL);
        SelectObject (hdc, GetStockObject (RGB(255,0,0)));
        LineTo(hdc,X[1],Y[1]);
        for(double t=0.1;t<1; t+=0.03)
        {
            x =((pow((1-t),3)*X[0])+((pow((1-t),2)*X[1]*3*t))+(3*t*t*(1-t)*X[2])+(t*t*t*X[3]));
            y =((pow((1-t),3)*Y[0])+((pow((1-t),2)*Y[1]*3*t))+(3*t*t*(1-t)*Y[2])+(t*t*t*Y[3]));
            fout << x << " " << y << "\n";
            LineTo(hdc,x,y);
        }

        LineTo(hdc,X[2],Y[2]);

        string s = "Functia PolyBezier predefinita";
        TextOut(hdc,400,250,"Functia PolyBezier predefinita",s.size());
        PolyBezier(hdc,pt,4);
        MoveToEx(hdc,pt[0].x ,pt[0].y ,NULL);
        LineTo(hdc,pt[1].x,pt[1].y);
        MoveToEx(hdc,pt[2].x,pt[2].y,NULL);
        LineTo(hdc,pt[3].x,pt[3].y);

    }

	default:
		return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
