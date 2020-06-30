#include <windows.h>
#include "App.h"

int APIENTRY WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow
) {
    App *app = new App(hInstance);
    app->Init();
    app->Loop();

    delete app;
    return 0;
}
