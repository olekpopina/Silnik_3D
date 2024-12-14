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
    void setShadingMode(int mode);
    void setRotation(bool rotating);
    void updateRotationC(float deltaTime);
    float vertices[24];
    unsigned int indices[36];
    float normals[24];
    float colors[24];
    float scale;
    float offsetX, offsetY;
    int shadingMode;
    bool isRotating = false; // Domyœlnie brak obrotu
    float rotationAngle = 0.0f; // Pocz¹tkowy k¹t
    float rotationSpeed = 0.1f; // Prêdkoœæ obrotu w stopniach/sekundê
};

#endif // CUBE_H
