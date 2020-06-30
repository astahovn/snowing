#ifndef SNOWING_APP_H
#define SNOWING_APP_H

#include "Window/IWindow.h"
#include <GL\gl.h>
#include <GL\glu.h>

class App {
protected:
    HINSTANCE hInstance;

    static const int N = 500;

    struct tsnow {
        float x, y, sp;
        int angle;
    } Point[N];

    struct tobject {
        float x, y, z;
    } Circle[100], Haos[100], Some[100], Haos2[100];

    struct tmorph {
        float x, y, z, xs, ys, zs;
    } ObjectX[100];

    HWND hWnd = nullptr;
    HGLRC hglrc;
    HDC hDC;
    GLfloat angle = 0, rad = 3.14 / 180;
    bool keys[256];
    bool Morphing = FALSE;
    int StepMorph = 1;
    bool Exit = FALSE;
    float Ex = 1;
    bool ShowMorph = TRUE;

public:
    explicit App(HINSTANCE hInstance);

    ~App();

    void Init();

    void Loop();

    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    void drawscene();

    void InitGL();

    void ProcessKeys();

    BOOL bSetupPixelFormat(HDC hdc);
};

#endif
