#ifndef SNOWING_SNOW_H
#define SNOWING_SNOW_H

#include <windows.h>
#include <GL\gl.h>
#include "IAnimation.h"

class Snow : public IAnimation {
public:
    void init() override;
    int computing() override;
    void render(float globalFading) const override;
    void processKeys(const bool keys[]) override {};

private:
    static const int SNOWFLAKES_COUNT = 500;

    struct TSnowflake {
        GLdouble x, y, sp;
        int angle;
    } snowflakes[SNOWFLAKES_COUNT];

    GLdouble rad = 3.14 / 180;
};

#endif
