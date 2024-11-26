#ifndef COMPLEX_OBJECT_H
#define COMPLEX_OBJECT_H

#include <GL/freeglut.h>

class ComplexObject {
private:
    float vertices[12];
    float colors[12];
    unsigned int indices[6];

public:
    ComplexObject();
    void draw();
};

#endif // COMPLEX_OBJECT_H
