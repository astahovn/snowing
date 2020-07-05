#ifndef SNOWING_SCENE_H
#define SNOWING_SCENE_H

#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "IAnimation.h"
#include "AnimationAggregate.h"
#include "Snow.h"
#include "Morph.h"

class Scene : public IAnimation {
public:
    Scene();
    ~Scene() override;

    void init() override;
    int computing() override;
    void render(float globalFading) const override;
    void processKeys(const bool keys[]) override;

private:
    AnimationAggregate *animation;

    bool globalFadingStart = FALSE;
    float globalFadingStep = 1;
};

#endif
