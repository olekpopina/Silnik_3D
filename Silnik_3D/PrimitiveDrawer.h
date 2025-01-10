
#ifndef PRIMITIVE_DRAWER_H
#define PRIMITIVE_DRAWER_H

#include <GL/freeglut.h>
#include "BitmapHandler.h"


class PrimitiveDrawer {

public:

    enum ShadingMode {
        FLAT,
        GOURAUD,
        PHONG
    };

    static void setShadingMode(ShadingMode mode);
    static void drawPoint(float x, float y, float z, float size = 1.0f);
    static void drawLine(float x1, float y1, float z1, float x2, float y2, float z2, float width = 1.0f);
    static void drawTriangle(float vertices1[9], float vertices2[9], float vertices3[9], float colors[9], float posX, float posY, float scale, float rotationAngle = 0.0f);
    static void drawCube(float scale, float offsetX, float offsetY, float vertices[24], unsigned int indices[36], float normals[24], float colors[24]);

   static void drawCubeNew(float scale, float offsetX, float offsetY, BitmapHandler& bitmapHandler);

   // static void drawCubeNew(float scale, float offsetX, float offsetY, BitmapHandler& bitmapHandler);

   static int textureSet;

   static GLuint textures[6];

private:
    static ShadingMode currentShadingMode;
};

#endif // PRIMITIVE_DRAWER_H