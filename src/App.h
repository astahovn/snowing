#ifndef SNOWING_APP_H
#define SNOWING_APP_H

#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "Window/Win.h"
#include "Window/IWMHandler.h"
#include "Animation/Scene.h"

class App : public IWMHandler {
public:
    explicit App(HINSTANCE hInstance);

    ~App();

    void init();

    void loop();

    void onWinCreate() override;
    void onWinDestroy() override;
    void onKeyDown(int key) override;
    void onKeyUp(int key) override;

private:
    bool keys[256]{};

    Win *win;
    IAnimation *scene;

    void computing();

    void render();
};

#endif
