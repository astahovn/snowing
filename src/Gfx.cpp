#include "Gfx.h"

void Gfx::init(HWND hwnd) {
    hDC = GetDC(hwnd);
    if (!bSetupPixelFormat(hDC)) {
        MessageBox(hwnd, "Setup pixel format", "Error", MB_OK);
    }
    hglrc = wglCreateContext(hDC);
    if (hglrc == nullptr) {
        MessageBox(hwnd, "wglCreateContext", "Error", MB_OK);
    }
    if (!wglMakeCurrent(hDC, hglrc)) {
        MessageBox(hwnd, "wglMakeCurrent", "Error", MB_OK);
    }
}

void Gfx::shutdown(HWND hwnd) {
    if (!wglMakeCurrent(nullptr, nullptr)) {
        MessageBox(hwnd, "wglMakeCurrent", "Error", MB_OK);
    }
    if (!wglDeleteContext(hglrc)) {
        MessageBox(hwnd, "wglDeleteContext", "Error", MB_OK);
    }
}

BOOL Gfx::bSetupPixelFormat(HDC hdc) {
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

void Gfx::paint() {
    SwapBuffers(hDC);
}
