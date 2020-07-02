#ifndef SNOWING_SNOW_H
#define SNOWING_SNOW_H

#include <windows.h>
#include <GL\gl.h>
#include "IAnimation.h"

class Snow : public IAnimation {
public:
    void Init() override;
    void Computing() override;
    void Render(float GlobalFading) const override;

private:
    static const int SnowflakesCount = 500;

    struct TSnowflake {
        GLdouble x, y, sp;
        int angle;
    } Snowflakes[SnowflakesCount];

    GLdouble rad = 3.14 / 180;
};

#endif
