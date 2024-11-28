#include "PrimitiveDrawer.h"

void PrimitiveDrawer::drawPoint(float x, float y, float z, float size) {
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
}

void PrimitiveDrawer::drawLine(float x1, float y1, float z1, float x2, float y2, float z2, float width) {
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glEnd();
}

void PrimitiveDrawer::drawTriangle(float* vertices, float* colors) {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {
        glColor3fv(&colors[i * 3]); // Ustaw kolor dla ka¿dego wierzcho³ka
        glVertex3fv(&vertices[i * 3]); // Dodaj wspó³rzêdne wierzcho³ka
    }
    glEnd();
}
