#include <Windows.h>
#include "Win32.h"

void Win32::Create() {
    WNDCLASS ws;
    ws.cbClsExtra = NULL;
    ws.cbWndExtra = NULL;
    ws.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    ws.hCursor = nullptr;
    ws.hIcon = nullptr;
    ws.hInstance = this->hInstance;
    ws.lpfnWndProc = WndProc;
    ws.lpszClassName = "EWClass";
    ws.lpszMenuName = nullptr;
    ws.style = CS_HREDRAW || CS_VREDRAW;
    RegisterClass(&ws);
    this->hWnd = CreateWindowEx(
        WS_EX_TOPMOST,
        "EWClass",
        "OpenGL",
        WS_POPUP,
        0,
        0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );
    ShowWindow(this->hWnd, SW_SHOWNORMAL);
    UpdateWindow(this->hWnd);
    SetCursor(nullptr);
}
