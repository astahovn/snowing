#include "Scene.h"

Scene::Scene() {
    snow = new Snow();
    morph = new Morph();
}

Scene::~Scene() {
    delete snow;
    delete morph;
}

void Scene::init() {
    glClearColor(0, 0, 0, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLdouble aspect = (GLdouble) GetSystemMetrics(SM_CXSCREEN) / GetSystemMetrics(SM_CYSCREEN);
    gluPerspective(45.0, aspect, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    snow->init();
    morph->init();
}

int Scene::computing() {
    snow->computing();
    morph->computing();

    if (globalFadingStart == TRUE) globalFadingStep = globalFadingStep - 0.005f;
    if (globalFadingStep < 0.1) {
        return COMPUTING_END;
    }
    return COMPUTING_OK;
}

void Scene::render(float globalFading) const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    snow->render(globalFadingStep);
    morph->render(globalFadingStep);
}

void Scene::processKeys(const bool *keys) {
    if (keys[VK_ESCAPE]) {
        globalFadingStart = TRUE;
    }

    snow->processKeys(keys);
    morph->processKeys(keys);
}
