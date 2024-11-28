#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/freeglut.h>
#include "PrimitiveDrawer.h"

class Triangle : public PrimitiveDrawer { // Dziedziczenie z PrimitiveDrawer
public:
    Triangle();
  
    void draw(); // Funkcja do rysowania ca�ego tr�jk�ta

private:
    float vertices1[9];
    float vertices2[9];
    float vertices3[9];
    float colors[9];
    float posX, posY;    // Pozycja tr�jk�ta
    bool isRotating = false; // Domy�lnie brak obrotu
    float rotationAngle = 0.0f; // Pocz�tkowy k�t
    float rotationSpeed = 0.1f; // Pr�dko�� obrotu w stopniach/sekund�

public:
    void setRotation(bool rotate);
    void updateRotation(float deltaTime);
    void setPosition(float x, float y);
    void updatePosition();

};

#endif // TRIANGLE_H
