#include "include/include.h"

extern HWND hBtn;
extern HINSTANCE hbInst;


//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int vkey;
    static int x,y;
    TCHAR szTemp[1024];
    HDC hdc;
    PAINTSTRUCT ps;
    static HPEN hpen,hpenPrev;
    static HBRUSH hbr, hbrPrev;

    switch (uMsg)
    {
    case WM_CREATE:
        hpen = CreatePen(PS_SOLID, 1, RGB(0x00, 0x7f, 0xff));
        //hbr = CreateHatchBrush(HS_DIAGCROSS,RGB(0xff, 0xbf, 0x00));
        hbr = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
        hBtn =CreateWindowEx(0,"BUTTON","Push",WS_CHILD | WS_VISIBLE | BS_FLAT,10,100,50,30,hwnd,(HMENU)0,hbInst,NULL);
        return 0;
    case WM_KEYDOWN:
        vkey = wParam;
        wsprintf(szTemp,TEXT("WM_KEYDOWN (vkey:%d)"),vkey);
        SetWindowText(hwnd,szTemp);
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
    case WM_DESTROY:
        DeleteObject(hpen);
        DeleteObject(hbr);

        PostQuitMessage(0);
        return 0;
    }
    //他のメッセージは既定のウィンドウプロシージャに投げる
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}