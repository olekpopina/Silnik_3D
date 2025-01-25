#ifndef TRANSFORMABLEOBJECT_H
#define TRANSFORMABLEOBJECT_H

#include "Drawable.h"
#include <GL/freeglut.h>

class TransformableObject : public Drawable {
protected:
    float scaleFactor;  // Масштаб
    float posX, posY, posZ; // Позиція
    float rotationAngle; // Кут обертання

public:
    TransformableObject();
    virtual ~TransformableObject() = default;

    // Методи трансформації
    void scale(float factor); // Єдиний метод для масштабування
    void setPosition(float x, float y, float z);
    void rotate(float angle);

    // Геттери
    float getScale() const;
    void getPosition(float& x, float& y, float& z) const;
    float getRotation() const;
};

#endif // TRANSFORMABLEOBJECT_H
