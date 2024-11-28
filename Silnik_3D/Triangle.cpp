#include "Triangle.h"
#include <fstream>

Triangle::Triangle() : posX(0.0f), posY(0.0f), rotationAngle(0.0f), isRotating(false) {
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
    glPushMatrix(); // Zapamiêtanie bie¿¹cej macierzy
    glTranslatef(posX, posY, 0.0f); // Przesuniêcie trójk¹ta na pozycjê
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f); // Obrót wokó³ osi Y

    // Rysowanie trzech czêœci trójk¹ta
    drawTriangle(vertices1, colors);
    drawTriangle(vertices2, colors);
    drawTriangle(vertices3, colors);

    glPopMatrix(); // Przywrócenie poprzedniej macierzy
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




