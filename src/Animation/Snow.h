#ifndef SNOWING_SNOW_H
#define SNOWING_SNOW_H

#include <windows.h>
#include <GL\gl.h>
#include "IAnimation.h"

class Snow : public IAnimation {
private:
    static const int SnowflakesCount = 500;

    struct TSnowflake {
        float x, y, sp;
        int angle;
    } Snowflakes[SnowflakesCount];

    GLfloat rad = 3.14 / 180;

public:
    void Init() override;
    void Computing() override;
    void Render(float GlobalFading) override;

};

#endif
