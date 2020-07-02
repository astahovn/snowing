#ifndef SNOWING_MORPH_H
#define SNOWING_MORPH_H

#include <windows.h>
#include <GL\gl.h>
#include "IAnimation.h"

class Morph : public IAnimation {
public:
    void init() override;
    void computing() override;
    void render(float globalFading) const override;

private:
    static const int POINTS_COUNT = 100;

    struct TObject {
        GLdouble x, y, z;
    } circle[POINTS_COUNT], chaos[POINTS_COUNT], some[POINTS_COUNT], chaos2[POINTS_COUNT];

    struct TMorph {
        GLdouble x, y, z, xs, ys, zs;
    } objectX[POINTS_COUNT];

    GLdouble angle = 0, rad = 3.14 / 180;
    bool morphingInProcess = FALSE;
    int morphStep = 1;
};


#endif
