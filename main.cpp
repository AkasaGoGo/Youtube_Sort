// Windows アプリケーションの雛形
#include "include/include.h"
using namespace std;

//メイン関数
int WINAPI WinMain(
    HINSTANCE hInstance,     //インスタンスへのハンドル
    HINSTANCE hPrevInstance, // win16時代の遺産
    LPSTR lpszCmdLine,       //コマンドライン引数
    int nCmdShow             //ウィンドウの表示状態
)
{
    Window wind(hInstance,TEXT("Youtube"));
    ShowWindow(wind.hwnd, nCmdShow);
    UpdateWindow(wind.hwnd);
    CSV csv(string("CH_LIST.csv"));
    vector<vector<Channel>> chList;
    csv.read(chList);
    while (GetMessage(&wind.msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&(wind.msg));
        DispatchMessage(&(wind.msg));
    }

    return wind.msg.wParam;
}
