#ifndef SNOWING_WIN_H
#define SNOWING_WIN_H

#include <vector>
#include <windows.h>
#include "Gfx.h"
#include "IWMHandler.h"

class Win {
public:
    Win(HINSTANCE pHInstance);

    ~Win();

    void init();

    bool processMessages();

    void destroy();

    void addHandler(IWMHandler * handler);

private:
    HINSTANCE hInstance;
    HWND hWnd = nullptr;

    Gfx *gfx;

    std::vector<IWMHandler *> handlers{};

    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};


#endif
