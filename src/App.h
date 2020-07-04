#ifndef SNOWING_APP_H
#define SNOWING_APP_H

#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "Gfx.h"
#include "Animation/Scene.h"

class App {
public:
    explicit App(HINSTANCE hInstance);

    ~App();

    void init();

    void loop();

private:
    HINSTANCE hInstance;
    HWND hWnd = nullptr;

    bool keys[256]{};

    Gfx *gfx;
    IAnimation *scene;

    void computing();

    void render();

    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
