#ifndef CUBE_H
#define CUBE_H

#include <GL/freeglut.h>
#include "TransformableObject.h"
#include "BitmapHandler.h"
#include "PrimitiveDrawer.h"

class Cube : public TransformableObject {
public:
    Cube();
    void draw() const override;
    void setShadingMode(int mode);
    void setRotationC(bool rotating);
    void updateRotationC(float deltaTime);

    float vertices[24];
    unsigned int indices[36];
    float normals[24];
    float colors[24];
    int shadingMode;
    bool isRotating = false;
    float rotationAngle = 0.0f;
    float rotationSpeed = 0.4f;
    BitmapHandler bitmapHandler;
};

#endif // CUBE_H
