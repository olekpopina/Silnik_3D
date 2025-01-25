#include "TransformableObject.h"

TransformableObject::TransformableObject()
    : scaleFactor(1.0f), posX(0.0f), posY(0.0f), posZ(0.0f), rotationAngle(0.0f) {}

void TransformableObject::scale(float factor) {
    scaleFactor *= factor;
}

void TransformableObject::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

void TransformableObject::rotate(float angle) {
    rotationAngle += angle;
    if (rotationAngle >= 360.0f) {
        rotationAngle -= 360.0f;
    }
}

float TransformableObject::getScale() const {
    return scaleFactor;
}

void TransformableObject::getPosition(float& x, float& y, float& z) const {
    x = posX;
    y = posY;
    z = posZ;
}

float TransformableObject::getRotation() const {
    return rotationAngle;
}
