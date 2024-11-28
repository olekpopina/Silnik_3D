#include "Triangle.h"
#include <fstream>

Triangle::Triangle() : posX(0.0f), posY(0.0f), rotationAngle(0.0f), isRotating(false) {
    // Ustawienia kolor�w dla wierzcho�k�w
    float initialColors[] = {
        1.0f, 0.0f, 0.0f,  // Czerwony
        0.0f, 1.0f, 0.0f,  // Zielony
        0.0f, 0.0f, 1.0f   // Niebieski
    };
    std::copy(std::begin(initialColors), std::end(initialColors), colors);

    // Wierzho�ki tr�jk�t�w
    float initialVertices1[] = {
        0.0f,  0.5f, 0.0f,  // G�rny wierzcho�ek
       -0.5f, -0.5f, -0.5f, // Lewy dolny
        0.5f, -0.5f, -0.5f  // Prawy dolny
    };
    std::copy(std::begin(initialVertices1), std::end(initialVertices1), vertices1);

    float initialVertices2[] = {
        0.0f,  0.5f, 0.0f,  // G�rny wierzcho�ek
        0.5f, -0.5f, -0.5f, // Lewy dolny
        0.0f, -0.5f,  0.5f  // Prawy dolny
    };
    std::copy(std::begin(initialVertices2), std::end(initialVertices2), vertices2);

    float initialVertices3[] = {
        0.0f,  0.5f, 0.0f,  // G�rny wierzcho�ek
        0.0f, -0.5f,  0.5f, // Lewy dolny
       -0.5f, -0.5f, -0.5f  // Prawy dolny
    };
    std::copy(std::begin(initialVertices3), std::end(initialVertices3), vertices3);
}

void Triangle::draw() {
    glPushMatrix(); // Zapami�tanie bie��cej macierzy
    glTranslatef(posX, posY, 0.0f); // Przesuni�cie tr�jk�ta na pozycj�
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f); // Obr�t wok� osi Y

    // Rysowanie trzech cz�ci tr�jk�ta
    drawTriangle(vertices1, colors);
    drawTriangle(vertices2, colors);
    drawTriangle(vertices3, colors);

    glPopMatrix(); // Przywr�cenie poprzedniej macierzy
}

void Triangle::setRotation(bool rotating) {
    isRotating = rotating;
}

void Triangle::setPosition(float x, float y) {
    posX = x; // Ustawia pozycj� X
    posY = y; // Ustawia pozycj� Y
}

void Triangle::updateRotation(float deltaTime) {
    if (isRotating) {
        rotationAngle += rotationSpeed * deltaTime;
        if (rotationAngle > 360.0f) {
            rotationAngle -= 360.0f; // Resetowanie k�ta
        }
    }
}


void Triangle::updatePosition() {
    // Mo�esz doda� logik� aktualizacji pozycji, je�li b�dzie to potrzebne
}




