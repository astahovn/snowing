#ifndef SNOWING_GFX_H
#define SNOWING_GFX_H

#include <windows.h>

class Gfx {
public:
    void init(HWND hwnd);
    void shutdown(HWND hwnd);
    void paint();

private:
    HGLRC hglrc = nullptr;
    HDC hDC = nullptr;

    BOOL bSetupPixelFormat(HDC hdc);
};


#endif
