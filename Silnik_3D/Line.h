#ifndef LINE_H
#define LINE_H

#include "PrimitiveDrawer.h"

class Line : public PrimitiveDrawer {
public:
    Line();
    Line(float startX, float startY, float startZ, float endX, float endY, float endZ);

    void setStart(float x, float y, float z);
    void setEnd(float x, float y, float z);

    void getStart(float& x, float& y, float& z) const;
    void getEnd(float& x, float& y, float& z) const;

    void draw();
   
private:
    float start[3];  
    float end[3];   
};

#endif // LINE_H
