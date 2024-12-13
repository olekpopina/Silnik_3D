#ifndef CUBE_H
#define CUBE_H

#include <GL/freeglut.h>
#include "TransformableObject.h"

class Cube {
public:
    Cube();
    void draw();
    void scaleUp();    // Powi�kszenie
    void scaleDown();  // Pomniejszenie
    void move(float dx, float dy); // Przesuni�cie sze�cianu
    void setShadingMode(int mode);
    float vertices[24];
    unsigned int indices[36];
    float normals[24];
    float colors[24];
    float scale;
    float offsetX, offsetY;
    int shadingMode;
};

#endif // CUBE_H
