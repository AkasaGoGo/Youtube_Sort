#include "include/include.h"
#define BUTTON_ID_FAV 10001
#define BUTTON_ID_ABC 10002
#define BUTTON_ID_LIST 10003
#define BUTTON_ID_UP 10004
#define BUTTON_ID_DOWN 10005
// SETTING
#define ACCOUNT_SETTING 40001
#define ACCOUNT_URL 10006
// COLOR
#define RED 40006
#define ORANGE 40007
#define YELLOW 40008
#define GREEN 40009
#define BLUE 40010
#define PURPLE 40011

extern vector<Channel> chList;
extern CSV csv;
bool isOpen = false;
// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int vkey;
    static int x, y;

    static vector<Channel *> showCh(chList.size());
    static int start = 0;
    TCHAR szTemp[1024];
    HDC hdc;
    PAINTSTRUCT ps;

    HWND hBtn[5];

    HINSTANCE hbInst;

    static HPEN hpen, hpenPrev;
    static HBRUSH hbr, hbrPrev;
    static HBRUSH fillFev, notFev;
    static HMENU hMenu;
    static HWND hUrlEditor, hUrlBtn;
    static LPSTR strText;

    switch (uMsg)
    {
    case WM_CREATE:
        
        hMenu = LoadMenu(NULL, "WIN_MENU");
        SetMenu(hwnd, hMenu);

        return 0;
    case WM_LBUTTONDOWN:
        y = HIWORD(lParam);
        x = LOWORD(lParam);
        for (int i = 0; i < 5; i++)
        {
            if ((x - (360)) * (x - (360)) + (y - (115 + i * 30)) * (y - (115 + i * 30)) < 100)
            {
                showCh[i]->fav = !(showCh[i]->fav);
                break;
            }
        }
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_PAINT:
        if(isOpen){
        hdc = BeginPaint(hwnd, &ps);
        hpenPrev = (HPEN)SelectObject(hdc, hpen);
        hbrPrev = (HBRUSH)SelectObject(hdc, hbr);
        SelectObject(hdc, hpenPrev);
        SelectObject(hdc, hbrPrev);
        EndPaint(hwnd, &ps);
        hdc = GetDC(hwnd);

        for (int i = 0; i < 5; i++)
        {
            int selector;
            if (chList.size() > i + start)
            {
                selector = i + start;
            }
            else
            {
                selector = i + start - chList.size();
            }
            TextOut(hdc, 400, 100 + i * 30, showCh[selector]->name.c_str(), showCh[selector]->name.length());
            if (showCh[selector]->fav)
            {
                SelectObject(hdc, fillFev);
            }
            else
            {
                SelectObject(hdc, notFev);
            }
            Ellipse(hdc, 350, 105 + i * 30, 370, 125 + i * 30);
        }
        ReleaseDC(hwnd, hdc);
        }
        return 0;

    case WM_COMMAND:

        switch (LOWORD(wParam))
        {
        case BUTTON_ID_DOWN:
            start++;
            if (start > chList.size())
                start = 0;
            break;
        case BUTTON_ID_UP:
            start--;
            if (start < 0)
                start = chList.size();
            break;
        case BUTTON_ID_FAV:
            sort(chList.begin(), chList.end(), cmp_fev);
            start = 0;
            break;
        case ACCOUNT_SETTING:
            hUrlEditor = CreateWindow(
                TEXT("EDIT"), TEXT("UCHC_xxR2kbIcVtMCGRIvcoA"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
                0, 0, 200, 30, hwnd, (HMENU)6,
                hbInst, NULL);
            hUrlBtn = CreateWindow(
                TEXT("Button"), TEXT("OK"),
                WS_CHILD | WS_VISIBLE | BS_FLAT,
                200, 0, 50, 30, hwnd, (HMENU)ACCOUNT_URL,
                hbInst, NULL);
            break;
        case ACCOUNT_URL:
            printf("%d", GetWindowTextA(hUrlEditor, strText, 5000));
            system("python get_reg_channel.py UCHC_xxR2kbIcVtMCGRIvcoA");
            csv.open(string("channel_reports.csv"));
            csv.read(chList);
            cout << "hello";
            hpen = CreatePen(PS_SOLID, 1, RGB(0x00, 0x7f, 0xff));
            // hbr = CreateHatchBrush(HS_DIAGCROSS,RGB(0xff, 0xbf, 0x00));
            hbr = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
            fillFev = CreateSolidBrush(RGB(255, 0, 0));
            notFev = CreateSolidBrush(RGB(255, 255, 255));
            hBtn[0] = CreateWindowExW(0, L"Button", L"お気に入り", WS_CHILD | WS_VISIBLE | BS_FLAT, 10, 100, 100, 30, hwnd, (HMENU)BUTTON_ID_FAV, hbInst, NULL);
            hBtn[1] = CreateWindowExW(0, L"Button", L"五十音順", WS_CHILD | WS_VISIBLE | BS_FLAT, 10, 150, 100, 30, hwnd, (HMENU)BUTTON_ID_ABC, hbInst, NULL);
            hBtn[2] = CreateWindowExW(0, L"Button", L"グループ", WS_CHILD | WS_VISIBLE | BS_FLAT, 10, 200, 100, 30, hwnd, (HMENU)BUTTON_ID_LIST, hbInst, NULL);
            hBtn[3] = CreateWindowExW(0, L"Button", L"↑", WS_CHILD | WS_VISIBLE | BS_FLAT, 700, 100, 30, 30, hwnd, (HMENU)BUTTON_ID_UP, hbInst, NULL);
            hBtn[4] = CreateWindowExW(0, L"Button", L"↓", WS_CHILD | WS_VISIBLE | BS_FLAT, 700, 250, 30, 30, hwnd, (HMENU)BUTTON_ID_DOWN, hbInst, NULL);
            cout << "ddd";
            for (int i = 0; i < chList.size(); i++)
            {
                showCh.push_back(&(chList[i]));
            }
            isOpen = true;
            cout << "sdsd";
            break;
        }
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_DESTROY:
        DeleteObject(hpen);
        DeleteObject(hbr);

        PostQuitMessage(0);
        return 0;
    }
    // 他のメッセージは既定のウィンドウプロシージャに投げる
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}