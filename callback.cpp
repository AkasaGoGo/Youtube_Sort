#include "include/include.h"



//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int vkey;
    static int x,y;
    TCHAR szTemp[1024];
    HDC hdc;
    PAINTSTRUCT ps;

    HWND hBtn[3];


    HINSTANCE hbInst;

    static HPEN hpen,hpenPrev;
    static HBRUSH hbr, hbrPrev;
    static HMENU hMenu;
    switch (uMsg)
    {
    case WM_CREATE:
        hpen = CreatePen(PS_SOLID, 1, RGB(0x00, 0x7f, 0xff));
        //hbr = CreateHatchBrush(HS_DIAGCROSS,RGB(0xff, 0xbf, 0x00));
        hbr = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
        hBtn[0] =CreateWindowExW(0,L"Button",L"お気に入り",WS_CHILD | WS_VISIBLE | BS_FLAT,10,100,100,30,hwnd,(HMENU)0,hbInst,NULL);
        hBtn[1] =CreateWindowExW(0,L"Button",L"五十音順",WS_CHILD | WS_VISIBLE | BS_FLAT,10,150,100,30,hwnd,(HMENU)0,hbInst,NULL);
        hBtn[2] =CreateWindowExW(0,L"Button",L"グループ",WS_CHILD | WS_VISIBLE | BS_FLAT,10,200,100,30,hwnd,(HMENU)0,hbInst,NULL);
        
        
        hMenu = LoadMenu(NULL,"WIN_MENU");
        SetMenu(hwnd,hMenu);
        return 0;
    case WM_LBUTTONDOWN:
        y = HIWORD(lParam);
        x = LOWORD(lParam);
        InvalidateRect(hwnd,NULL,TRUE);
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hwnd,&ps);
        hpenPrev = (HPEN)SelectObject(hdc, hpen);
        hbrPrev = (HBRUSH) SelectObject(hdc, hbr);
        Rectangle(hdc,x-30,y-30,x+30,y+30);
        SelectObject(hdc,hpenPrev);
        SelectObject(hdc,hbrPrev);

        EndPaint(hwnd,&ps);
        return 0;

    case WM_COMMAND:
        return 0;

    case WM_DESTROY:
        DeleteObject(hpen);
        DeleteObject(hbr);

        PostQuitMessage(0);
        return 0;
    }
    //他のメッセージは既定のウィンドウプロシージャに投げる
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}