#include "App.h"

App::App(IWindow* window) {
    this->window = window;
}

void App::Init() {
    this->window->Create();
}


