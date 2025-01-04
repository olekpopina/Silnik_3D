#include "Cube.h"



Cube::Cube() : vertices{
    -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f
}, indices{
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    0, 4, 7, 7, 3, 0,
    1, 5, 6, 6, 2, 1,
    3, 7, 6, 6, 2, 3,
    0, 4, 5, 5, 1, 0
}, normals{
    0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
    0.0f, 0.0f,  1.0f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f,  1.0f
}, colors{
    1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.5f, 0.5f, 0.5f,  1.0f, 1.0f, 1.0f
}, scale(1.0f),offsetX(0.0f), offsetY(0.0f) {} 

void Cube::draw() {
    glPushMatrix(); 
   // glTranslatef(offsetX, offsetY, 0.0f); 


    if (isRotating) {
        glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f); 
    }

    PrimitiveDrawer::drawCube(scale, offsetX, offsetY, vertices, indices, normals, colors);
    PrimitiveDrawer::setShadingMode(PrimitiveDrawer::FLAT); 
    PrimitiveDrawer::setShadingMode(PrimitiveDrawer::GOURAUD);
    PrimitiveDrawer::setShadingMode(PrimitiveDrawer::PHONG);
    glPopMatrix(); 

}

void Cube::drawNew() {
    

    PrimitiveDrawer::drawCubeNew(scale, offsetX, offsetY, vertices, indices, normals, colors, bitmapHandler);
}


void Cube::scaleUp() {
   
    TransformableObject::scaleUp_Cube(scale);
}

void Cube::scaleDown() {
   
    TransformableObject::scaleDown_Cube(scale);
}

void Cube::move(float dx, float dy) {
    offsetX += dx;
    offsetY += dy;
}

void Cube::setShadingMode(int mode)
{
    shadingMode = mode;
}

void Cube::setRotationC(bool rotating)
{
    isRotating = rotating;
}

void Cube::updateRotationC(float deltaTime)
{
    if (isRotating) {
        rotationAngle += rotationSpeed * deltaTime;
        if (rotationAngle > 360.0f) {
            rotationAngle -= 360.0f;
        }
    }
}
