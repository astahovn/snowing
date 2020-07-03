#include <cstdlib>
#include "Morph.h"

void Morph::init() {
    int i;
    GLdouble step = 100 / (2 * 3.141592);
    GLdouble aangle = 0;

    for (i = 0; i < POINTS_COUNT; i++) {
        some[i].x = 0.1 * cos(aangle * rad);
        some[i].y = 0.1 * sin(aangle * rad);
        some[i].z = 0.1 * cos(aangle * rad) * sin(aangle * rad);

        circle[i].x = 0.1 * cos(aangle * rad);
        circle[i].y = 0.1 * sin(aangle * rad);
        circle[i].z = 0.1 * cos(aangle * rad);
        aangle = aangle + step;
        chaos[i].x = (GLdouble) (rand() % 30) / 100 - 0.15;
        chaos[i].y = (GLdouble) (rand() % 30) / 100 - 0.15;
        chaos[i].z = (GLdouble) (rand() % 30) / 100 - 0.15;

        chaos2[i].x = 0.1 * sin(aangle * rad) * cos(aangle * rad);
        chaos2[i].y = 0.1 * cos(aangle * rad);
        chaos2[i].z = 0.1 * sin(aangle * rad) * cos(aangle * rad);
    }
    for (i = 0; i < POINTS_COUNT; i++) {
        objectX[i].x = chaos2[i].x;
        objectX[i].y = chaos2[i].y;
        objectX[i].z = chaos2[i].z;
    }
    angle = 0;
}

int Morph::computing() {
    int i;
    if (morphStep == 300) {
        morphingInProcess = FALSE;
        morphStep = 1;
    }
    if (morphStep == 200) {
        int z = rand() % 4;
        switch (z) {
            case 0: {
                for (i = 0; i < POINTS_COUNT; i++) {
                    objectX[i].xs = (chaos[i].x - objectX[i].x) / 100;
                    objectX[i].ys = (chaos[i].y - objectX[i].y) / 100;
                    objectX[i].zs = (chaos[i].z - objectX[i].z) / 100;
                }
                break;
            }
            case 1: {
                for (i = 0; i < POINTS_COUNT; i++) {
                    objectX[i].xs = (chaos2[i].x - objectX[i].x) / 100;
                    objectX[i].ys = (chaos2[i].y - objectX[i].y) / 100;
                    objectX[i].zs = (chaos2[i].z - objectX[i].z) / 100;
                }
                break;
            }
            case 2: {
                for (i = 0; i < POINTS_COUNT; i++) {
                    objectX[i].xs = (circle[i].x - objectX[i].x) / 100;
                    objectX[i].ys = (circle[i].y - objectX[i].y) / 100;
                    objectX[i].zs = (circle[i].z - objectX[i].z) / 100;
                }
                break;
            }
            case 3: {
                for (i = 0; i < POINTS_COUNT; i++) {
                    objectX[i].xs = (some[i].x - objectX[i].x) / 100;
                    objectX[i].ys = (some[i].y - objectX[i].y) / 100;
                    objectX[i].zs = (some[i].z - objectX[i].z) / 100;
                }
                break;
            }
        }
        morphingInProcess = TRUE;
    }
    if (morphingInProcess == TRUE) {
        for (i = 0; i < POINTS_COUNT; i++) {
            objectX[i].x += objectX[i].xs;
            objectX[i].y += objectX[i].ys;
            objectX[i].z += objectX[i].zs;
        }
    }

    morphStep++;
    angle += 1;
    if (angle == 360) angle = 0;

    return COMPUTING_OK;
}

void Morph::render(float globalFading) const {
    if (!showMorph) {
        return;
    }

    glLoadIdentity();
    glColor4f(0.6, 0.6, 1, globalFading);
    glTranslatef(0, 0, -1);
    glRotatef(angle, sin(angle * rad), cos(angle * rad), 0);
    glPointSize(1.5);
    glBegin(GL_POINTS);
    for (auto & objectXPoint : objectX) {
        glVertex3f(objectXPoint.x, objectXPoint.y, objectXPoint.z);
    }
    glEnd();
}

void Morph::processKeys(const bool *keys) {
    if (keys[VK_SPACE]) {
        showMorph = !showMorph;
    }
}
