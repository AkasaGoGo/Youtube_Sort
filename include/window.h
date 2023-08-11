#ifndef __INCLUDE_WINDOW_H__
#define __INCLUDE_WINDOW_H__

#include "include.h"


class Window{
public:
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;
    Window(HINSTANCE hI, TCHAR appName[]);
};

#endif