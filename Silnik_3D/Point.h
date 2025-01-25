#ifndef POINT_H
#define POINT_H

#include "TransformableObject.h"

class Point : public TransformableObject {
public:
    Point(float x , float y, float z);
    Point();

    void set(float x, float y, float z);
    void translate(float dx, float dy, float dz);
    float getX() const;
    float getY() const;
    float getZ() const;
    void draw() const override;
};

#endif // POINT_H
