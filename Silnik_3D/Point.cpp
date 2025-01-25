#include "Point.h"

Point::Point(float x, float y, float z) {
    setPosition(x, y, z); // Використання методу з TransformableObject
}

Point::Point() {
    setPosition(0.0f, 0.0f, 0.0f); // Використання методу з TransformableObject
}

void Point::set(float x, float y, float z) {
    setPosition(x, y, z); // Використання методу з TransformableObject
}

void Point::translate(float dx, float dy, float dz) {
    move(dx, dy); // Використання методу переміщення з TransformableObject
    posZ += dz;   // Додаткова обробка для Z координати
}

float Point::getX() const {
    return posX; // Використання внутрішніх змінних TransformableObject
}

float Point::getY() const {
    return posY;
}

float Point::getZ() const {
    return posZ;
}

void Point::draw() const {
    PrimitiveDrawer::drawPoint(this->getX(), this->getY(), this->getZ(), 8);
}
