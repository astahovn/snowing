#include <windows.h>
#include "App.h"

int APIENTRY WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow
) {
    App *app = new App(hInstance);
    app->init();
    app->loop();

    delete app;
    return 0;
}
