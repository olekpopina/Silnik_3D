#ifndef CUBE_H
#define CUBE_H

#include <GL/freeglut.h>

class Cube {
private:
    float vertices[24];
    unsigned int indices[36];
    float normals[24];
    float colors[24];
    float scale;
    float offsetX, offsetY;

public:
    Cube();
    void draw();
    void scaleUp();    // Powiększenie
    void scaleDown();  // Pomniejszenie
    void move(float dx, float dy); // Przesunięcie sześcianu
};

#endif // CUBE_H
