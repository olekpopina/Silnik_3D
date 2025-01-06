#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/freeglut.h>
#include "PrimitiveDrawer.h"
#include "TransformableObject.h"


class Triangle : public PrimitiveDrawer { 
public:
    Triangle();
  
    void draw(); 

private:
    float vertices1[9];
    float vertices2[9];
    float vertices3[9];
    float colors[9];
    float posX, posY;    
    bool isRotating = false;
    float rotationAngle = 0.0f; 
    float rotationSpeed = 0.1f; 
    float scale;

public:
    void setRotation(bool rotate);
    void updateRotation(float deltaTime);
    void setPosition(float x, float y);
    void updatePosition();
    void scale_Up();
    void scale_Down();
    float getPositionX() const { return posX; }
    float getPositionY() const { return posY; }

};

#endif // TRIANGLE_H
