#ifndef SNOWING_APP_H
#define SNOWING_APP_H

#include "Window/IWindow.h"

class App
{
protected:
    IWindow* window;

public:
    explicit App(IWindow* window);

    void Init();

};

#endif
