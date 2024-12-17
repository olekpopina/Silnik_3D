#include "Line.h"
#include "PrimitiveDrawer.h"

Line::Line() {
    start[0] = 0.0f; start[1] = 0.0f; start[2] = 0.0f;
    end[0] = 1.0f; end[1] = 0.0f; end[2] = 0.0f;
}

Line::Line(float startX, float startY, float startZ, float endX, float endY, float endZ) {
    start[0] = startX;
    start[1] = startY;
    start[2] = startZ;
    end[0] = endX;
    end[1] = endY;
    end[2] = endZ;
}

void Line::setStart(float x, float y, float z) {
    start[0] = x;
    start[1] = y;
    start[2] = z;
}

void Line::setEnd(float x, float y, float z) {
    end[0] = x;
    end[1] = y;
    end[2] = z;
}

void Line::getStart(float& x, float& y, float& z) const {
    x = start[0];
    y = start[1];
    z = start[2];
}

void Line::getEnd(float& x, float& y, float& z) const {
    x = end[0];
    y = end[1];
    z = end[2];
}

void Line::draw() {
    PrimitiveDrawer::drawLine(start[0], start[1], start[2], end[0], end[1], end[2], 2.0f);
}
