#include "ComplexObject.h"

ComplexObject::ComplexObject() : vertices{
    -0.5f, -0.5f, 0.0f,  0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,  0.0f,  0.0f, 0.5f
}, indices{
    0, 1, 2,  0, 2, 3
}, colors{
    1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f
} {}

void ComplexObject::draw() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
