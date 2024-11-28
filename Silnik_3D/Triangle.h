#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/freeglut.h>
#include "PrimitiveDrawer.h"

class Triangle : public PrimitiveDrawer { // Dziedziczenie z PrimitiveDrawer
public:
    Triangle();
  
    void draw(); // Funkcja do rysowania ca³ego trójk¹ta

private:
    float vertices1[9];
    float vertices2[9];
    float vertices3[9];
    float colors[9];
    float posX, posY;    // Pozycja trójk¹ta
    bool isRotating = false; // Domyœlnie brak obrotu
    float rotationAngle = 0.0f; // Pocz¹tkowy k¹t
    float rotationSpeed = 0.1f; // Prêdkoœæ obrotu w stopniach/sekundê

public:
    void setRotation(bool rotate);
    void updateRotation(float deltaTime);
    void setPosition(float x, float y);
    void updatePosition();

};

#endif // TRIANGLE_H
