#ifndef SNOWING_IWINDOW_H
#define SNOWING_IWINDOW_H

#include <windows.h>

class IWindow {
protected:
    HINSTANCE hInstance;

public:
    explicit IWindow(HINSTANCE hInstance) : hInstance(hInstance) {};

    virtual void Create() = 0;

    ~IWindow() = default;

};


#endif
