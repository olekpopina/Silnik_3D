#include "Triangle.h"
#include <fstream>

Triangle::Triangle() : posX(0.0f), posY(0.0f), rotationAngle(0.0f), scale(1.0f), isRotating(false) {
    // Ustawienia kolorów dla wierzcho³ków
    float initialColors[] = {
        1.0f, 0.0f, 0.0f,  // Czerwony
        0.0f, 1.0f, 0.0f,  // Zielony
        0.0f, 0.0f, 1.0f   // Niebieski
    };
    std::copy(std::begin(initialColors), std::end(initialColors), colors);

    // Wierzho³ki trójk¹tów
    float initialVertices1[] = {
        0.0f,  0.5f, 0.0f,  // Górny wierzcho³ek
       -0.5f, -0.5f, -0.5f, // Lewy dolny
        0.5f, -0.5f, -0.5f  // Prawy dolny
    };
    std::copy(std::begin(initialVertices1), std::end(initialVertices1), vertices1);

    float initialVertices2[] = {
        0.0f,  0.5f, 0.0f,  // Górny wierzcho³ek
        0.5f, -0.5f, -0.5f, // Lewy dolny
        0.0f, -0.5f,  0.5f  // Prawy dolny
    };
    std::copy(std::begin(initialVertices2), std::end(initialVertices2), vertices2);

    float initialVertices3[] = {
        0.0f,  0.5f, 0.0f,  // Górny wierzcho³ek
        0.0f, -0.5f,  0.5f, // Lewy dolny
       -0.5f, -0.5f, -0.5f  // Prawy dolny
    };
    std::copy(std::begin(initialVertices3), std::end(initialVertices3), vertices3);

}

void Triangle::draw() {
    // W³¹czenie oœwietlenia i ustawienie materia³u
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // Aktywacja œwiat³a 0 (podstawowe)

    GLfloat lightPos[] = { 0.0f, 0.0f, 5.0f, 1.0f }; // Pozycja œwiat³a
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Sk³adnik ambient
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Sk³adnik rozproszony
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Sk³adnik zwierciadlany

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    GLfloat matAmbient[] = { 0.2f, 0.5f, 0.2f, 1.0f };
    GLfloat matDiffuse[] = { 0.5f, 1.0f, 0.5f, 1.0f };
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matShininess = 30.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

    glPushMatrix(); // Zapamiêtanie bie¿¹cej macierzy
    glTranslatef(posX, posY, 0.0f); // Przesuniêcie trójk¹ta na pozycjê
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f); // Obrót wokó³ osi Y
    glScalef(scale, scale, scale);

    // Normalki dla ka¿dego wierzcho³ka
    GLfloat normals[] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    // Rysowanie trzech czêœci trójk¹ta z u¿yciem ró¿nych wierzcho³ków
    glVertexPointer(3, GL_FLOAT, 0, vertices1);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glVertexPointer(3, GL_FLOAT, 0, vertices2);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glVertexPointer(3, GL_FLOAT, 0, vertices3);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glPopMatrix(); // Przywrócenie poprzedniej macierzy

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glScalef(scale, scale, scale);
}

void Triangle::scale_Up() {
    scale *= 1.1f; // Zwiêkszamy skalê o 10%
}

void Triangle::scale_Down() {
    scale *= 0.9f; // Zmniejszamy skalê o 10%
}


void Triangle::setRotation(bool rotating) {
    isRotating = rotating;
}

void Triangle::setPosition(float x, float y) {
    posX = x; // Ustawia pozycjê X
    posY = y; // Ustawia pozycjê Y
}

void Triangle::updateRotation(float deltaTime) {
    if (isRotating) {
        rotationAngle += rotationSpeed * deltaTime;
        if (rotationAngle > 360.0f) {
            rotationAngle -= 360.0f; // Resetowanie k¹ta
        }
    }
}

void Triangle::updatePosition() {
    // Mo¿esz dodaæ logikê aktualizacji pozycji, jeœli bêdzie to potrzebne
}




