// Windows アプリケーションの雛形

#include <windows.h>
HWND hBtn;
HINSTANCE hbInst;
//コールバック関数の宣言
LRESULT CALLBACK WndProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//メイン関数
int WINAPI WinMain(
    HINSTANCE hInstance,     //インスタンスへのハンドル
    HINSTANCE hPrevInstance, // win16時代の遺産
    LPSTR lpszCmdLine,       //コマンドライン引数
    int nCmdShow             //ウィンドウの表示状態
)
{
    TCHAR szAppName[] = TEXT("TestApp");
    HWND hwnd;
    MSG msg;
    // WNDCLASS構造体
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc; //ウィンドウプロシージャ
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szAppName;
    // RegisterClass関数でウィンドウクラスを登録、失敗したら終了
    if (!RegisterClass(&wc))
        return 0;

    hwnd = CreateWindow(
        szAppName,
        TEXT(""),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);
    // CreateWindowがNULLを返したときは終了
    if (!hwnd)
        return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

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