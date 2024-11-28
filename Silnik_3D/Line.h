#ifndef LINE_H
#define LINE_H

#include "PrimitiveDrawer.h"

class Line : public PrimitiveDrawer {
public:
    Line();
    Line(float startX, float startY, float startZ, float endX, float endY, float endZ);
    // Gettery i settery
    void setStart(float x, float y, float z);
    void setEnd(float x, float y, float z);

    void getStart(float& x, float& y, float& z) const;
    void getEnd(float& x, float& y, float& z) const;

    void draw(); // Funkcja rysuj¹ca liniê

private:
    float start[3];  // Pocz¹tek linii (x, y, z)
    float end[3];    // Koniec linii (x, y, z)
};

#endif // LINE_H
