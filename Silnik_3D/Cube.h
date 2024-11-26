#ifndef CUBE_H
#define CUBE_H

#include <GL/freeglut.h>

class Cube {
private:
    float vertices[24];
    unsigned int indices[36];
    float normals[24];
    float colors[24];

public:
    Cube();
    void draw();
};

#endif // CUBE_H
