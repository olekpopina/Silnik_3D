#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/freeglut.h>
#include "TransformableObject.h"


class Triangle : public TransformableObject {
public:
    Triangle();
  
    void draw() const override; 

private:
    float vertices1[9];
    float vertices2[9];
    float vertices3[9];
    float colors[9];
    bool isRotating = false;
    float rotationAngle = 0.0f; 
    float rotationSpeed = 1.0f; 

public:
    void setRotation(bool rotate);
    void updateRotation(float deltaTime = 0.0f);
    void setPosition(float x, float y);
    float getPositionX() const { return posX; }
    float getPositionY() const { return posY; }

};

#endif // TRIANGLE_H
