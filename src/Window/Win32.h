#ifndef SNOWING_WIN32_H
#define SNOWING_WIN32_H


#include "IWindow.h"

class Win32 : public IWindow {
    HWND hWnd = nullptr;

public:
    explicit Win32(HINSTANCE hInstance) : IWindow(hInstance) {}

    void Create() override;

};


#endif
