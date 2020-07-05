#include "App.h"
#include <math.h>

App::App(HINSTANCE pHInstance) {
    hInstance = pHInstance;
    gfx = new Gfx();
    scene = new Scene();
}

App::~App() {
    delete scene;
    delete gfx;
}

void App::init() {
    MessageBox(nullptr, "SNOWING\n\n"
                        "Code by Astakhov Nikolay\n"
                        "Made in Novouralsk 2003\n\n"
                        "Active keys:\n"
                        "'SPACE' - Morphing\n"
                        "'Esc' - exit", "SNOWING", MB_OK | MB_ICONINFORMATION);

    WNDCLASS ws;
    ws.cbClsExtra = NULL;
    ws.cbWndExtra = sizeof(*this);
    ws.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    ws.hCursor = nullptr;
    ws.hIcon = nullptr;
    ws.hInstance = hInstance;
    ws.lpfnWndProc = App::StaticWndProc;
    ws.lpszClassName = "EWClass";
    ws.lpszMenuName = nullptr;
    ws.style = CS_HREDRAW || CS_VREDRAW;
    RegisterClass(&ws);
    this->hWnd = CreateWindowEx(
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

void App::loop() {
    MSG msg;
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE)) {
            if (!GetMessage(&msg, nullptr, 0, 0)) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        computing();
        render();
    }
}

void App::computing() {
    int computingResult = scene->computing();

    if (IAnimation::COMPUTING_END == computingResult) {
        SendMessage(hWnd, WM_DESTROY, 0, 0);
    }
}

void App::render() {
    scene->render(0);

    gfx->paint();
}

LRESULT CALLBACK App::StaticWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_NCCREATE) {
        auto cs = (LPCREATESTRUCT) lParam;
        SetWindowLong(hwnd, GWL_USERDATA, (long) cs->lpCreateParams);
    }

    App *app = (App *) GetWindowLong(hwnd, GWL_USERDATA);
    if (app) {
        return app->WndProc(hwnd, uMsg, wParam, lParam);
    } else {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

LRESULT CALLBACK App::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            gfx->shutdown(hwnd);
            PostQuitMessage(0);
            break;

        case WM_CREATE:
            gfx->init(hwnd);
            scene->init();
            break;

        case WM_KEYDOWN:
            keys[wParam] = true;
            scene->processKeys(keys);
            break;

        case WM_KEYUP:
            keys[wParam] = false;
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
