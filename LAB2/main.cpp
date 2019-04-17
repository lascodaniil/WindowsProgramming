#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <math.h>

HBITMAP hbmMask;

HINSTANCE HH;
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
	HH  = hThisInstance;


    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
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
               _T("LUCRAREA DE LABORATOR NR.2"),
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT,
               CW_USEDEFAULT,
               900,
               500,
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

HBITMAP btfly;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static float x=1,i=0,coef =1,y=0,k=0,j=0;
    HDC hdc,hdcMem;
    PAINTSTRUCT ps;
    POINT pt;
    RECT rc;
    static int cxClient, cyClient, cxSource, cySource ;
	HDC hdcClient, hdcWindow ;

    static POINT elSegment  [1][8] = {110,300,100,230,120,230,110,300};
    static POINT elSegment1 [1][8] = {110,300,180,290,180,310,110,300};
    static POINT elSegment2 [1][8] = {110,300,100,370,120,370,110,300};
    static POINT elSegment3 [1][8] = {110,300,40,290,40,310,110,300};
    static POINT elicopter [1][40] = {62,275,94,266,147,307,295,293,370,279,403,243,528,238,515,258,625,253
    ,625,253,615,283,641,283,717,337,649,367,333,367,305,347,183,341,159,369,97,363,119,345,62,275};
    static POINT FERESTRE[1][10] = {717,337,665,325,600,320,600,273,649,273};
    static POINT JOS [1][12]= {649,367,640,372,370,380,365,385,360,367,355,367};
    static POINT p2 [1][8]= {485,214,667,123,689,119,521,210};
    static POINT p3 [1][8]= {485,214,775,231,779,241,485,218};
    static POINT p4 [1][8]= {485,214,201,137,205,152,485,216};
    static POINT p5 [1][8]= {485,214,293,235,300,242,485,216};



    switch (message)
    {
    case WM_CREATE:{
        SetTimer(hwnd, 0,10,NULL); // timer
        btfly = (HBITMAP) LoadImage(NULL, "butterfly.bmp", IMAGE_BITMAP,100,100, LR_LOADFROMFILE);
    	break;
    }

    case WM_DESTROY:
    {   KillTimer(hwnd,0);
        PostQuitMessage (0);
        break;
    }

    case WM_PAINT:
    {

        GetClientRect(hwnd, &rc);
        hdc = BeginPaint (hwnd, &ps) ;

        FillRect(hdc,&rc,CreateSolidBrush(RGB(255,255,255)));
		SelectObject (hdc, GetStockObject (NULL_PEN));
        SelectObject(hdc, CreateSolidBrush(RGB(255,0,0)));
        Polygon(hdc,elicopter[0],40);
        SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		SelectObject(hdc, GetStockObject(BLACK_PEN));
        MoveToEx(hdc,0,100,NULL);
        LineTo(hdc,200,100);
        TextOut(hdc,30,80,"LASCO DANIIL",strlen("LASCO DANIIL"));
		SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		SelectObject (hdc, GetStockObject (NULL_PEN));
        Ellipse(hdc,100,290,120,310);
        Polygon(hdc,elSegment[0],4);
        Polygon(hdc,elSegment1[0],4);
        Polygon(hdc,elSegment2[0],4);
        Polygon(hdc,elSegment3[0],4);

        // ferestrele elicopterului
        SelectObject(hdc, CreateSolidBrush(RGB(255,255,255)));
        Rectangle(hdc,570,283,590,313);
        Rectangle(hdc,540,283,560,313);
        Rectangle(hdc,470,273,530,350);
        Rectangle(hdc,440,283,460,313);
        Rectangle(hdc,440,283,460,313);
        Rectangle(hdc,400,283,420,313);

        SelectObject(hdc, CreateSolidBrush(RGB(220,220,220)));
        Polygon(hdc,FERESTRE[0],5);
        SelectObject(hdc, CreateSolidBrush(RGB(128,0,0)));
        Polygon(hdc,JOS[0],6);
        SelectObject(hdc, CreateSolidBrush(RGB(0,0,0)));
        Rectangle(hdc,620,372,625,382);
        Rectangle(hdc,433,378,438,409);
        SelectObject(hdc, CreateSolidBrush(RGB(150,0,0)));
        Ellipse(hdc,610,380,640,410);
        Ellipse(hdc,362,379,393,410);
        Ellipse(hdc,420,405,450,435);


        SelectObject(hdc, CreateSolidBrush(RGB(10,10,0)));
        Ellipse(hdc,460,209,510,219);
        Rectangle(hdc,480,217,490,241);
        Polygon(hdc,p2[0],4);
        Polygon(hdc,p3[0],4);
        Polygon(hdc,p4[0],4);
        Polygon(hdc,p5[0],4);


        HDC bitmapDC = CreateCompatibleDC(hdc);
        SelectObject(bitmapDC,btfly);
        BitBlt(hdc, 350+coef,10,450+coef,150, bitmapDC, 0,0, SRCCOPY);


        SelectObject(hdc, CreateSolidBrush(RGB(16,52,166)));
        Ellipse(hdc,550-y,75,690-y,140);
        Ellipse(hdc,575-y,35,700-y,100);
        Ellipse(hdc,650-y,55,790-y,135);




        DeleteDC(bitmapDC);
	 	Sleep(1000);

    }
    case WM_TIMER:
    {

           i+=0.01;
           y+=k;
           k+=0.01;
        if(coef == 1.10){
            coef = 0;
        }
        else{
            coef+=0.10;
        }

           elSegment[0][0].x= 110+(110-110)*cos(10*i) - (300-300)*sin(10*i);
           elSegment[0][0].y= 300+(110-110)*sin(10*i) + (300-300)*cos(10*i);
           elSegment[0][1].x= 110+(100-110)*cos(10*i) - (230-300)*sin(10*i);
           elSegment[0][1].y= 300+(100-110)*sin(10*i) + (230-300)*cos(10*i);
           elSegment[0][2].x= 110+(120-110)*cos(10*i) - (230-300)*sin(10*i);
           elSegment[0][2].y= 300+(120-110)*sin(10*i) + (230-300)*cos(10*i);
           elSegment[0][3].x= 110+(110-110)*cos(10*i) - (300-300)*sin(10*i);
           elSegment[0][3].y= 300+(110-110)*sin(10*i) + (300-300)*cos(10*i);





           elSegment1[0][0].x= 110+(110-110)*cos(10*i) - (300-300)*sin(10*i);
           elSegment1[0][0].y= 300+(110-110)*sin(10*i) + (300-300)*cos(10*i);
           elSegment1[0][1].x= 110+(180-110)*cos(10*i) - (290-300)*sin(10*i);
           elSegment1[0][1].y= 300+(180-110)*sin(10*i) + (290-300)*cos(10*i);
           elSegment1[0][2].x= 110+(180-110)*cos(10*i) - (310-300)*sin(10*i);
           elSegment1[0][2].y= 300+(180-110)*sin(10*i) + (310-300)*cos(10*i);
           elSegment1[0][3].x= 110+(110-110)*cos(10*i) - (300-300)*sin(10*i);
           elSegment1[0][3].y= 300+(110-110)*sin(10*i) + (300-300)*cos(10*i);


           elSegment2[0][0].x= 110+(110-110)*cos(10*i) - (300-300)*sin(10*i);
           elSegment2[0][0].y= 300+(110-110)*sin(10*i) + (300-300)*cos(10*i);
           elSegment2[0][1].x= 110+(100-110)*cos(10*i) - (370-300)*sin(10*i);
           elSegment2[0][1].y= 300+(100-110)*sin(10*i) + (370-300)*cos(10*i);
           elSegment2[0][2].x= 110+(120-110)*cos(10*i) - (370-300)*sin(10*i);
           elSegment2[0][2].y= 300+(120-110)*sin(10*i) + (370-300)*cos(10*i);
           elSegment2[0][3].x= 110+(110-110)*cos(10*i) - (300-300)*sin(10*i);
           elSegment2[0][3].y= 300+(110-110)*sin(10+i) + (300-300)*cos(10+i);


           elSegment3[0][0].x= 110+(110-110)*cos(10*i) - (300-300)*sin(10*i);
           elSegment3[0][0].y= 300+(110-110)*sin(10*i) + (300-300)*cos(10*i);
           elSegment3[0][1].x= 110+(40-110)*cos(10*i)  - (290-300)*sin(10*i);
           elSegment3[0][1].y= 300+(40-110)*sin(10*i)  + (290-300)*cos(10*i);
           elSegment3[0][2].x= 110+(40-110)*cos(10*i)  - (310-300)*sin(10*i);
           elSegment3[0][2].y= 300+(40-110)*sin(10*i)  + (310-300)*cos(10*i);
           elSegment3[0][3].x= 110+(110-110)*cos(10*i) - (300-300)*sin(10*i);
           elSegment3[0][3].y= 300+(110-110)*sin(10*i) + (300-300)*cos(10*i);
               InvalidateRect(hwnd, NULL, FALSE);
           break;

    }
	default:
		return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

