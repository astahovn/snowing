#include <cstdlib>
#include "Snow.h"

void Snow::Init() {
    for (auto & Snowflake : Snowflakes) {
        Snowflake.x = ((GLfloat) (rand() % 120)) / 100 - 0.6;
        Snowflake.y = ((GLfloat) (rand() % 100)) / 100 - 0.5;
        Snowflake.sp = (GLfloat) (1 + rand() % 3) / 1000;
        Snowflake.angle = rand() % 360;
    }
}

void Snow::Computing() {
    for (auto & Snowflake : Snowflakes) {
        Snowflake.y = Snowflake.y - Snowflake.sp;
        Snowflake.angle += 5;
        if (Snowflake.y < -0.5) {
            Snowflake.x = ((GLfloat) (rand() % 120)) / 100 - 0.6;
            Snowflake.y = 0.5;
            Snowflake.angle = rand() % 360;
        }
    }
}

void Snow::Render(const float GlobalFading) const {
    glLoadIdentity();
    glColor4f(1, 1, 1, GlobalFading);
    glTranslatef(0, 0, -1);
    glPointSize(1);
    glBegin(GL_POINTS);
    for (auto & Snowflake : Snowflakes) {
        glVertex3f(Snowflake.x + 0.007 * cos(Snowflake.angle * rad), Snowflake.y, 0);
    }
    glEnd();
}
