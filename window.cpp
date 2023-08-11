#include "include/include.h"



Window::Window(HINSTANCE hI, TCHAR appName[]){
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc; //ウィンドウプロシージャ
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hI;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = appName;

        // RegisterClass関数でウィンドウクラスを登録、失敗したら終了
    if (!RegisterClass(&wc))
        exit(0);

    hwnd = CreateWindow(
        appName,
        TEXT("YoutubeSort"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hI,
        NULL);
    // CreateWindowがNULLを返したときは終了
    if (!hwnd)
        exit(0);

}
