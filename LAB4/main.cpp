#include <tchar.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include<iostream>

#define ID_RADIO_1 0
#define ID_RADIO_2 1
#define ID_RADIO_3 2
#define ID_CHECK_1 3
#define ID_PUSH_1 4


using namespace std;


int time=50;
int i=0,score=0;
int arr_sol[3][3];

LPTSTR arr[4] = {"Care este prima litera din alfabet?",
    "Citi ani are Chisinaul?","Ziua Independentei este? ", "SFIRSIT TEST"};
LPTSTR arr1[4][4] = {{"A" ,"B" , "C"} ,{"100", "582","20"} , {"1 APRILE" ,"2 MAI" ," 27 AUGUST"}};

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");


HWND *hwndButton= new HWND[10];
HINSTANCE hInstancee;

int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS |  CS_HREDRAW | CS_VREDRAW ;
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
               _T("LUCRAREA DE LABORATOR NR.4"),
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT,
               CW_USEDEFAULT,
               400,
               600,
               NULL,
               NULL,
               hThisInstance,
               NULL
           );


        ShowWindow (hwnd, nCmdShow);
        UpdateWindow(hwnd);
        SetTimer(hwnd,0,1000,NULL);


    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}


LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    HDC hdc;
    PAINTSTRUCT ps;
    RECT rc;
    HINSTANCE hInstancee;
    char szBuffer[20], sz[20];
    LPTSTR str;
    switch (message)
    {

        case WM_TIMER :
            time--;
                InvalidateRect(hwnd,NULL,FALSE);
            break;

        case WM_COMMAND:

        for(int j = 0; j < 3; j++){
            arr_sol[i][j] = (int)SendMessage (hwndButton[j], BM_GETCHECK, 0, 0);
            score = arr_sol[0][0] + arr_sol[1][1] + arr_sol[2][2];
            }

            if(LOWORD(wParam)==ID_PUSH_1){
              if((int)SendMessage (hwndButton[3], BM_GETCHECK, 0, 0)){
                time-=10;
                i+=1;
                InvalidateRect(hwnd,NULL,FALSE);
                SelectObject(hdc, CreateSolidBrush(RGB(255,255,255)));
                SelectObject (hdc, GetStockObject (NULL_PEN));
                Rectangle(hdc,0,23,400,600);

                DestroyWindow(hwndButton[0]);
                DestroyWindow(hwndButton[1]);
                DestroyWindow(hwndButton[2]);
                DestroyWindow(hwndButton[3]);
                DestroyWindow(hwndButton[4]);

        SendMessage(hwnd,WM_CREATE,wParam,lParam);
                }}
            break;

         case WM_CREATE:
            if(i<=3){

                hInstancee = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
                hwndButton[0] = CreateWindowEx(0,"BUTTON", arr1[i][0], WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON ,10,50,150,40,hwnd, (HMENU)ID_RADIO_1, hInstancee,NULL);
                hwndButton[1] = CreateWindowEx(0,"BUTTON", arr1[i][1], WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,10,90,150,40,hwnd, (HMENU)ID_RADIO_2, hInstancee,NULL);
                hwndButton[2] = CreateWindowEx(0,"BUTTON", arr1[i][2], WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,10,130,150,40,hwnd, (HMENU)ID_RADIO_3, hInstancee,NULL);
                hwndButton[3] = CreateWindowEx(0,"BUTTON", "CONFIRM", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,10,175,150,20,hwnd, (HMENU)ID_CHECK_1, hInstancee,NULL);
                hwndButton[4] = CreateWindowEx(0,"BUTTON", "TRIMITE", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,10,200,100,20,hwnd, (HMENU)ID_PUSH_1, hInstancee,NULL);

                InvalidateRect(hwnd,NULL,FALSE);
            }
            else{
                DestroyWindow(hwndButton[0]);
                DestroyWindow(hwndButton[1]);
                DestroyWindow(hwndButton[2]);
                DestroyWindow(hwndButton[3]);
                DestroyWindow(hwndButton[4]);

                SendMessage(hwnd,WM_PAINT,wParam,lParam);
            }
            break;

        case WM_PAINT:

            hdc = BeginPaint(hwnd,&ps);
            GetClientRect(hwnd, &rc);

            if(i==3){
                DestroyWindow(hwndButton[0]);
                DestroyWindow(hwndButton[1]);
                DestroyWindow(hwndButton[2]);
                DestroyWindow(hwndButton[3]);
                DestroyWindow(hwndButton[4]);

                SelectObject(hdc, CreateSolidBrush(RGB(255,255,255)));
                SelectObject (hdc, GetStockObject (NULL_PEN));
                Rectangle(hdc,0,22,400,600);
                time = 0;
                }


            if(time >= 10) {
                    SelectObject (hdc, GetStockObject (NULL_PEN));
                    Rectangle(hdc,0,0,350,20);
                    wsprintfA(szBuffer,"TIME: %d", time);
                    LPCSTR str = szBuffer;
                    TextOut(hdc,0,0,str,strlen(str));

            }else if(time < 10 && time >0){
                    SelectObject (hdc, GetStockObject (NULL_PEN));
                    Rectangle(hdc,0,0,350,20);
                    wsprintfA(szBuffer,"TIME: %d", time);
                    LPCSTR str = szBuffer;
                    TextOut(hdc,0,0,str,strlen(str));
            }
            if(time >0){
                    SelectObject(hdc, CreateSolidBrush(RGB(255,255,255)));
                    Rectangle(hdc,0,22,400,600);
                    SelectObject (hdc, GetStockObject (NULL_PEN));
                    TextOut(hdc,20,20,arr[i],strlen(arr[i]));
            }
            if(time ==0 || time <0 ){
                    SelectObject(hdc, CreateSolidBrush(RGB(255,255,255)));
                    SelectObject (hdc, GetStockObject (NULL_PEN));
                    Rectangle(hdc,0,0,400,600);

                    wsprintfA(szBuffer,"SCORE: %d", score);
                    LPCSTR str = szBuffer;
                    TextOut(hdc,0,0,str,strlen(str));


            }

            DeleteDC(hdc);
            break;

        case WM_DESTROY:
            KillTimer(hwnd,0);
            PostQuitMessage (0);
            return 0 ;

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
        }

    return 0;
}


