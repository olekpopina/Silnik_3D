#ifndef PRIMITIVE_DRAWER_H
#define PRIMITIVE_DRAWER_H

#include <GL/freeglut.h>

class PrimitiveDrawer {
public:
    static void drawPoint(float x, float y, float z, float size = 1.0f);
    static void drawLine(float x1, float y1, float z1, float x2, float y2, float z2, float width = 1.0f);
    void drawTriangle(float* vertices, float* colors);
};

#endif // PRIMITIVE_DRAWER_H
