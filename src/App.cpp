#include "App.h"
#include <GL\gl.h>
#include <GL\glu.h>
#include <math.h>
#include <stdlib.h>

App::App(HINSTANCE hInstance) {
    this->hInstance = hInstance;
}

void App::Init() {
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
    ws.hInstance = this->hInstance;
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
    ShowWindow(this->hWnd, SW_SHOWNORMAL);
    UpdateWindow(this->hWnd);
    SetCursor(nullptr);
    for (int i = 0; i < 255; i++) {
        this->keys[i] = false;
    }
}

void App::Loop() {
    MSG msg;
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE)) {
            if (!GetMessage(&msg, nullptr, 0, 0)) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        drawscene();
    }
}

App::~App() {
}

void App::ProcessKeys() {
    if (this->keys[VK_ESCAPE])
        this->Exit = TRUE;
    if (this->keys[VK_SPACE]) {
        if (this->ShowMorph == TRUE) this->ShowMorph = FALSE;
        else this->ShowMorph = TRUE;
    }
}

void App::InitGL() {
    int i;
    for (i = 0; i < App::N; i++) {
        this->Point[i].x = ((GLfloat) (rand() % 120)) / 100 - 0.6;
        this->Point[i].y = ((GLfloat) (rand() % 100)) / 100 - 0.5;
        this->Point[i].sp = (GLfloat) (1 + rand() % 3) / 1000;
        this->Point[i].angle = rand() % 360;
    }

    float step = 100 / (2 * 3.141592);
    float aangle = 0;
    for (i = 0; i < 100; i++) {
        this->Some[i].x = 0.1 * cos(aangle * this->rad);
        this->Some[i].y = 0.1 * sin(aangle * this->rad);
        this->Some[i].z = 0.1 * cos(aangle * this->rad) * sin(aangle * this->rad);

        this->Circle[i].x = 0.1 * cos(aangle * this->rad);
        this->Circle[i].y = 0.1 * sin(aangle * this->rad);
        this->Circle[i].z = 0.1 * cos(aangle * this->rad);
        aangle = aangle + step;
        this->Haos[i].x = (GLfloat) (rand() % 30) / 100 - 0.15;
        this->Haos[i].y = (GLfloat) (rand() % 30) / 100 - 0.15;
        this->Haos[i].z = (GLfloat) (rand() % 30) / 100 - 0.15;

        this->Haos2[i].x = 0.1 * sin(aangle * this->rad) * cos(aangle * this->rad);
        this->Haos2[i].y = 0.1 * cos(aangle * this->rad);
        this->Haos2[i].z = 0.1 * sin(aangle * this->rad) * cos(aangle * this->rad);
    }
    for (i = 0; i < 100; i++) {
        this->ObjectX[i].x = this->Haos2[i].x;
        this->ObjectX[i].y = this->Haos2[i].y;
        this->ObjectX[i].z = this->Haos2[i].z;
    }
    this->angle = 0;

    glClearColor(0, 0, 0, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspect = (GLfloat) GetSystemMetrics(SM_CXSCREEN) / GetSystemMetrics(SM_CYSCREEN);
    gluPerspective(45.0, aspect, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

void App::drawscene() {
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glColor4f(1, 1, 1, Ex);
    glTranslatef(0, 0, -1);
    glPointSize(1);
    glBegin(GL_POINTS);
    for (i = 0; i < App::N; i++)
        glVertex3f(this->Point[i].x + 0.007 * cos(this->Point[i].angle * rad), this->Point[i].y, 0);
    glEnd();

    if (this->ShowMorph == TRUE) {
        glLoadIdentity();
        glColor4f(1, 0, 1, Ex);
        glTranslatef(0, 0, -1);
        glRotatef(angle, sin(angle * rad), cos(angle * rad), 0);
        glPointSize(1.5);
        glBegin(GL_POINTS);
        for (i = 0; i < 100; i++)
            glVertex3f(ObjectX[i].x, ObjectX[i].y, ObjectX[i].z);
        glEnd();
    }

    for (i = 0; i < App::N; i++) {
        this->Point[i].y = this->Point[i].y - this->Point[i].sp;
        this->Point[i].angle += 5;
        if (this->Point[i].y < -0.5) {
            this->Point[i].x = ((GLfloat) (rand() % 120)) / 100 - 0.6;
            this->Point[i].y = 0.5;
            this->Point[i].angle = rand() % 360;
        }
    }

    if (this->StepMorph == 300) {
        this->Morphing = FALSE;
        this->StepMorph = 1;
    }
    if (this->StepMorph == 200) {
        int z = rand() % 4;
        switch (z) {
            case 0: {
                for (i = 0; i < 100; i++) {
                    this->ObjectX[i].xs = (this->Haos[i].x - this->ObjectX[i].x) / 100;
                    this->ObjectX[i].ys = (this->Haos[i].y - this->ObjectX[i].y) / 100;
                    this->ObjectX[i].zs = (this->Haos[i].z - this->ObjectX[i].z) / 100;
                }
                break;
            }
            case 1: {
                for (i = 0; i < 100; i++) {
                    this->ObjectX[i].xs = (this->Haos2[i].x - this->ObjectX[i].x) / 100;
                    this->ObjectX[i].ys = (this->Haos2[i].y - this->ObjectX[i].y) / 100;
                    this->ObjectX[i].zs = (this->Haos2[i].z - this->ObjectX[i].z) / 100;
                }
                break;
            }
            case 2: {
                for (i = 0; i < 100; i++) {
                    this->ObjectX[i].xs = (this->Circle[i].x - this->ObjectX[i].x) / 100;
                    this->ObjectX[i].ys = (this->Circle[i].y - this->ObjectX[i].y) / 100;
                    this->ObjectX[i].zs = (this->Circle[i].z - this->ObjectX[i].z) / 100;
                }
                break;
            }
            case 3: {
                for (i = 0; i < 100; i++) {
                    this->ObjectX[i].xs = (this->Some[i].x - this->ObjectX[i].x) / 100;
                    this->ObjectX[i].ys = (this->Some[i].y - this->ObjectX[i].y) / 100;
                    this->ObjectX[i].zs = (this->Some[i].z - this->ObjectX[i].z) / 100;
                }
                break;
            }
        }
        this->Morphing = TRUE;
    }
    if (this->Morphing == TRUE) {
        for (i = 0; i < 100; i++) {
            this->ObjectX[i].x += this->ObjectX[i].xs;
            this->ObjectX[i].y += this->ObjectX[i].ys;
            this->ObjectX[i].z += this->ObjectX[i].zs;
        }
    }

    this->StepMorph++;
    this->angle += 1;
    if (this->angle == 360) this->angle = 0;

    if (this->Exit == TRUE) this->Ex = this->Ex - 0.005f;
    if (this->Ex < 0.1) SendMessage(this->hWnd, WM_DESTROY, 0, 0);

    SwapBuffers(this->hDC);
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
            this->hDC = GetDC(hwnd);
            if (!bSetupPixelFormat(this->hDC))
                MessageBox(hwnd, "Setup pixel format", "Error", MB_OK);
            this->hglrc = wglCreateContext(this->hDC);
            if (this->hglrc == nullptr) MessageBox(hwnd, "wglCreateContext", "Error", MB_OK);
            if (!wglMakeCurrent(this->hDC, this->hglrc))
                MessageBox(hwnd, "wglMakeCurrent", "Error", MB_OK);
            InitGL();
            break;

        case WM_KEYDOWN:
            this->keys[wParam] = true;
            ProcessKeys();
            break;

        case WM_KEYUP:
            this->keys[wParam] = false;
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
