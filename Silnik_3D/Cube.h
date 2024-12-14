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
    void setRotation(bool rotating);
    void updateRotationC(float deltaTime);
    float vertices[24];
    unsigned int indices[36];
    float normals[24];
    float colors[24];
    float scale;
    float offsetX, offsetY;
    int shadingMode;
    bool isRotating = false; // Domy�lnie brak obrotu
    float rotationAngle = 0.0f; // Pocz�tkowy k�t
    float rotationSpeed = 0.1f; // Pr�dko�� obrotu w stopniach/sekund�
};

#endif // CUBE_H
