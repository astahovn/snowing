#include <cstdlib>
#include "Snow.h"

void Snow::init() {
    for (auto & snowflake : snowflakes) {
        snowflake.x = ((GLdouble) (rand() % 120)) / 100 - 0.6;
        snowflake.y = ((GLdouble) (rand() % 100)) / 100 - 0.5;
        snowflake.sp = (GLdouble) (1 + rand() % 3) / 1000;
        snowflake.angle = rand() % 360;
    }
}

void Snow::computing() {
    for (auto & snowflake : snowflakes) {
        snowflake.y = snowflake.y - snowflake.sp;
        snowflake.angle += 5;
        if (snowflake.y < -0.5) {
            snowflake.x = ((GLfloat) (rand() % 120)) / 100 - 0.6;
            snowflake.y = 0.5;
            snowflake.angle = rand() % 360;
        }
    }
}

void Snow::render(const float globalFading) const {
    glLoadIdentity();
    glColor4f(1, 1, 1, globalFading);
    glTranslatef(0, 0, -1);
    glPointSize(1);
    glBegin(GL_POINTS);
    for (auto & Snowflake : snowflakes) {
        glVertex3f(Snowflake.x + 0.007 * cos(Snowflake.angle * rad), Snowflake.y, 0);
    }
    glEnd();
}
