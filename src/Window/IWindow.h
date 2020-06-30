#ifndef SNOWING_IWINDOW_H
#define SNOWING_IWINDOW_H

#include <windows.h>

class IWindow {
protected:
    HINSTANCE hInstance;

public:
    explicit IWindow(HINSTANCE hInstance) : hInstance(hInstance) {};
    virtual ~IWindow() = default;

    virtual void Create() = 0;
};


#endif
