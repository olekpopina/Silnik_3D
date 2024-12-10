#include "Cube.h"

Cube::Cube() : vertices{
    -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f
}, indices{
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    0, 4, 7, 7, 3, 0,
    1, 5, 6, 6, 2, 1,
    3, 7, 6, 6, 2, 3,
    0, 4, 5, 5, 1, 0
}, normals{
    0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
    0.0f, 0.0f,  1.0f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f,  1.0f
}, colors{
    1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.5f, 0.5f, 0.5f,  1.0f, 1.0f, 1.0f
}, scale(1.0f),
offsetX(0.0f), offsetY(0.0f) {} 


void Cube::draw() {
    glPushMatrix();
    glScalef(scale, scale, scale);
    glTranslatef(offsetX, offsetY, 0.0f); // Przesuni�cie

    // Ustawienia materia��w
    GLfloat matAmbient[] = { 0.2f, 0.2f, 0.5f, 1.0f };   // Sk�adowa ambientowa
    GLfloat matDiffuse[] = { 0.5f, 0.5f, 1.0f, 1.0f };   // Sk�adowa rozproszona
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Sk�adowa lustrzana
    GLfloat matShininess = 50.0f;                        // Po�ysk

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

    // W��czenie o�wietlenia
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Konfiguracja �r�d�a �wiat�a
    GLfloat lightPos[] = { 1.0f, 1.0f, 1.0f, 1.0f };     // Pozycja �wiat�a
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Sk�adowa ambient
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Sk�adowa rozproszona
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Sk�adowa lustrzana

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Aktywacja tablic wierzcho�k�w i normalnych
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);

    // Rysowanie sze�cianu
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);

    // Wy��czenie tablic
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    // Wy��czenie o�wietlenia
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    glPopMatrix();
}

void Cube::scaleUp() {
    scale *= 1.1f; // Zwi�kszamy skal� o 10%
}

void Cube::scaleDown() {
    scale *= 0.9f; // Zmniejszamy skal� o 10%
}

void Cube::move(float dx, float dy) {
    offsetX += dx;
    offsetY += dy;
}
