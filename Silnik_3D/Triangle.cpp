#include "Triangle.h"
#include <fstream>

Triangle::Triangle() : posX(0.0f), posY(0.0f), rotationAngle(0.0f), scale(1.0f), isRotating(false) {
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
    PrimitiveDrawer::drawTriangle(vertices1, vertices2, vertices3, colors, posX, posY, scale, rotationAngle );
}

void Triangle::scale_Up() {
    scale *= 1.1f; // Zwi�kszamy skal� o 10%
}

void Triangle::scale_Down() {
    scale *= 0.9f; // Zmniejszamy skal� o 10%
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




