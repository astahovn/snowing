#include "App.h"
#include <math.h>

App::App(HINSTANCE pHInstance) {
    hInstance = pHInstance;
    scene = new Scene();
}

App::~App() {
    delete scene;
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

void App::processKeys() {
    scene->processKeys(keys);
}

void App::initGL() {
    scene->init();
}

void App::computing() {
    int computingResult = scene->computing();

    if (IAnimation::COMPUTING_END == computingResult) {
        SendMessage(hWnd, WM_DESTROY, 0, 0);
    }
}

void App::render() {
    scene->render(0);

    SwapBuffers(hDC);
}

BOOL App::bSetupPixelFormat(HDC hdc) {
    PIXELFORMATDESCRIPTOR pfd, *ppfd;
    int pixelformat;

    ppfd = &pfd;

    ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
    ppfd->nVersion = 1;
    ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    ppfd->dwLayerMask = PFD_MAIN_PLANE;
    ppfd->iPixelType = PFD_TYPE_RGBA;
    ppfd->cColorBits = 8;
    ppfd->cDepthBits = 16;
    ppfd->cAccumBits = 0;
    ppfd->cStencilBits = 0;

    if ((pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0) {
        MessageBox(nullptr, "ChoosePixelFormat failed", "Error", MB_OK);
        return FALSE;
    }

    if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE) {
        MessageBox(nullptr, "SetPixelFormat failed", "Error", MB_OK);
        return FALSE;
    }

    return TRUE;
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
            if (!wglMakeCurrent(nullptr, nullptr))
                MessageBox(hwnd, "wglMakeCurrent", "Error", MB_OK);
            if (!wglDeleteContext(hglrc))
                MessageBox(hwnd, "wglDeleteContext", "Error", MB_OK);
            PostQuitMessage(0);
            break;

        case WM_CREATE:
            hDC = GetDC(hwnd);
            if (!bSetupPixelFormat(hDC))
                MessageBox(hwnd, "Setup pixel format", "Error", MB_OK);
            hglrc = wglCreateContext(hDC);
            if (hglrc == nullptr) MessageBox(hwnd, "wglCreateContext", "Error", MB_OK);
            if (!wglMakeCurrent(hDC, hglrc))
                MessageBox(hwnd, "wglMakeCurrent", "Error", MB_OK);
            initGL();
            break;

        case WM_KEYDOWN:
            keys[wParam] = true;
            processKeys();
            break;

        case WM_KEYUP:
            keys[wParam] = false;
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
