#include "App.h"

App::App(HINSTANCE pHInstance) {
    win = new Win(pHInstance);
    win->addHandler(this);
    scene = new Scene();
}

App::~App() {
    delete scene;
    delete win;
}

void App::init() {
    MessageBox(nullptr, "SNOWING\n\n"
                        "Code by Astakhov Nikolay\n"
                        "Made in Novouralsk 2003\n\n"
                        "Active keys:\n"
                        "'SPACE' - Morphing\n"
                        "'Esc' - exit", "SNOWING", MB_OK | MB_ICONINFORMATION);

    win->init();
}

void App::loop() {
    while (true) {
        computing();
        render();
        if (!win->processMessages()) {
            break;
        }
    }
}

void App::computing() {
    int computingResult = scene->computing();

    if (IAnimation::COMPUTING_END == computingResult) {
        win->destroy();
    }
}

void App::render() {
    scene->render(0);
}

void App::onWinCreate() {
    scene->init();
}

void App::onWinDestroy() {
}

void App::onKeyDown(int key) {
    keys[key] = true;
    scene->processKeys(keys);
}

void App::onKeyUp(int key) {
    keys[key] = false;
}
