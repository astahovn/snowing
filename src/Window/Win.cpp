#include "Win.h"

Win::Win(HINSTANCE pHInstance) {
    hInstance = pHInstance;
    gfx = new Gfx();
}

Win::~Win() {
    delete gfx;
}

void Win::init() {
    WNDCLASS ws;
    ws.cbClsExtra = NULL;
    ws.cbWndExtra = sizeof(*this);
    ws.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    ws.hCursor = nullptr;
    ws.hIcon = nullptr;
    ws.hInstance = hInstance;
    ws.lpfnWndProc = Win::StaticWndProc;
    ws.lpszClassName = "EWClass";
    ws.lpszMenuName = nullptr;
    ws.style = CS_HREDRAW || CS_VREDRAW;
    RegisterClass(&ws);
    hWnd = CreateWindowEx(
            WS_EX_APPWINDOW,
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
            this
    );
    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);
    SetCursor(nullptr);

}

LRESULT CALLBACK Win::StaticWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_NCCREATE) {
        auto cs = (LPCREATESTRUCT) lParam;
        SetWindowLong(hwnd, GWL_USERDATA, (long) cs->lpCreateParams);
    }

    Win *win = (Win *) GetWindowLong(hwnd, GWL_USERDATA);
    if (win) {
        return win->WndProc(hwnd, uMsg, wParam, lParam);
    } else {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

LRESULT CALLBACK Win::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            gfx->shutdown(hwnd);
            for (auto & handler : handlers) {
                handler->onWinDestroy();
            }
            PostQuitMessage(0);
            break;

        case WM_CREATE:
            gfx->init(hwnd);
            for (auto & handler : handlers) {
                handler->onWinCreate();
            }
            break;

        case WM_KEYDOWN:
            for (auto & handler : handlers) {
                handler->onKeyDown(wParam);
            }
            break;

        case WM_KEYUP:
            for (auto & handler : handlers) {
                handler->onKeyUp(wParam);
            }
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool Win::processMessages() {
    MSG msg;
    if (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE)) {
        if (!GetMessage(&msg, nullptr, 0, 0)) {
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    gfx->paint();
    return true;
}

void Win::destroy() {
    SendMessage(hWnd, WM_DESTROY, 0, 0);
}

void Win::addHandler(IWMHandler * handler) {
    handlers.push_back(handler);
}
