#ifndef SNOWING_APP_H
#define SNOWING_APP_H

#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "Animation/Snow.h"
#include "Animation/Morph.h"

class App {
public:
    explicit App(HINSTANCE hInstance);

    ~App();

    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    BOOL bSetupPixelFormat(HDC hdc);

    void Init();

    void InitGL();

    void Loop();

    void Render();

    void ProcessKeys();

private:
    HINSTANCE hInstance;

    IAnimation *snow, *morph;

    HWND hWnd = nullptr;
    HGLRC hglrc;
    HDC hDC;
    bool keys[256];
    bool globalFadingStart = FALSE;
    float globalFadingStep = 1;
    bool showMorph = TRUE;
};

#endif
