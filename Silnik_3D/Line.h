#ifndef LINE_H
#define LINE_H

#include "TransformableObject.h"

class Line : public TransformableObject {
public:
    Line();
    Line(float startX, float startY, float startZ, float endX, float endY, float endZ);

    void setStart(float x, float y, float z);
    void setEnd(float x, float y, float z);

    void getStart(float& x, float& y, float& z) const;
    void getEnd(float& x, float& y, float& z) const;
    float getStartX() const;
    float getStartY() const;
    float getStartZ() const;

    float getEndX() const;
    float getEndY() const;
    float getEndZ() const;

    void draw() const override; 

private:
    float start[3];
    float end[3];
};

#endif // LINE_H
