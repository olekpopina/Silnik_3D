#ifndef CUBE_H
#define CUBE_H

#include <GL/freeglut.h>
#include "TransformableObject.h"

class Cube {
public:
    Cube();
    void draw();
    void scaleUp();    // Powiêkszenie
    void scaleDown();  // Pomniejszenie
    void move(float dx, float dy); // Przesuniêcie szeœcianu
    float vertices[24];
    unsigned int indices[36];
    float normals[24];
    float colors[24];
    float scale;
    float offsetX, offsetY;
};

#endif // CUBE_H
