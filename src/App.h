#ifndef SNOWING_APP_H
#define SNOWING_APP_H

#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "Animation/Scene.h"

class App {
public:
    explicit App(HINSTANCE hInstance);

    ~App();

    void init();

    void loop();

private:
    void initGL();

    void computing();

    void render();

    void processKeys();

    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    BOOL bSetupPixelFormat(HDC hdc);

    HINSTANCE hInstance;
    HWND hWnd = nullptr;
    HGLRC hglrc = nullptr;
    HDC hDC = nullptr;

    bool keys[256]{};

    IAnimation *scene;
};

#endif
