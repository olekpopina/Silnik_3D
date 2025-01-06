#ifndef CUBE_H
#define CUBE_H

#include <GL/freeglut.h>
#include "TransformableObject.h"
#include "BitmapHandler.h"
#include "PrimitiveDrawer.h"

class Cube : public PrimitiveDrawer {
public:
    Cube();
    void draw();
    void drawNew();
    void scaleUp();    
    void scaleDown();  
    void move(float dx, float dy); 
    void setShadingMode(int mode);
    void setRotationC(bool rotating);
    void updateRotationC(float deltaTime);
    float vertices[24];
    unsigned int indices[36];
    float normals[24];
    float colors[24];
    float scale;
    float offsetX, offsetY, offsetX2, offsetY2;
    int shadingMode;
    bool isRotating = false; 
    float rotationAngle = 0.0f; 
    float rotationSpeed = 0.5f; 
    BitmapHandler bitmapHandler;
};

#endif // CUBE_H
