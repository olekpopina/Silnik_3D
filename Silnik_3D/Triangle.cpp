#include "Triangle.h"
#include <fstream>


/**
 * @brief Konstruktor klasy Triangle.
 *
 * Konstruktor inicjalizuje wartości współrzędnych wierzchołków i kolorów trójkąta.
 * Trójkąt początkowo jest ustawiony na rotację 0.0f i nie jest obracany.
 */
Triangle::Triangle() : rotationAngle(0.0f), isRotating(false) {

    float initialColors[] = {
        1.0f, 0.0f, 0.0f,  // Czerwony
        0.0f, 1.0f, 0.0f,  // Zielony
        0.0f, 0.0f, 1.0f   // Niebieski
    };
    std::copy(std::begin(initialColors), std::end(initialColors), colors);


    float initialVertices1[] = {
        0.0f,  0.5f, 0.0f,  // Górny wierzchołek
       -0.5f, -0.5f, -0.5f, // Lewy dolny
        0.5f, -0.5f, -0.5f  // Prawy dolny
    };
    std::copy(std::begin(initialVertices1), std::end(initialVertices1), vertices1);

    float initialVertices2[] = {
        0.0f,  0.5f, 0.0f,  // Górny wierzchołek
        0.5f, -0.5f, -0.5f, // Lewy dolny
        0.0f, -0.5f,  0.5f  // Prawy dolny
    };
    std::copy(std::begin(initialVertices2), std::end(initialVertices2), vertices2);

    float initialVertices3[] = {
        0.0f,  0.5f, 0.0f,  // Górny wierzchołek
        0.0f, -0.5f,  0.5f, // Lewy dolny
       -0.5f, -0.5f, -0.5f  // Prawy dolny
    };
    std::copy(std::begin(initialVertices3), std::end(initialVertices3), vertices3);

}

/**
 * @brief Rysowanie trójkąta.
 *
 * Metoda rysuje trójkąt na podstawie współrzędnych jego wierzchołków i przypisanych kolorów.
 * Używa funkcji `drawTriangle` z klasy `PrimitiveDrawer`.
 */
void Triangle::draw() const {
    PrimitiveDrawer::drawTriangle(vertices1, vertices2, vertices3, colors, posX, posY, scaleFactor, rotationAngle );
}

/**
 * @brief Ustawienie stanu obrotu trójkąta.
 *
 * Ta metoda ustawia flagę `isRotating`, która decyduje, czy trójkąt ma być obracany.
 * @param rotating Flaga określająca, czy trójkąt ma być obracany.
 */
void Triangle::setRotation(bool rotating) {
    isRotating = rotating;
}

/**
 * @brief Ustawienie pozycji trójkąta.
 *
 * Metoda ta ustawia współrzędne X i Y pozycji trójkąta.
 * @param x Nowa współrzędna X trójkąta.
 * @param y Nowa współrzędna Y trójkąta.
 */
void Triangle::setPosition(float x, float y) {
    posX = x; 
    posY = y; 
}

/**
 * @brief Aktualizacja obrotu trójkąta.
 *
 * Ta metoda aktualizuje kąt obrotu trójkąta, jeśli flaga `isRotating` jest ustawiona na `true`.
 * Obrotu dokonuje się na podstawie prędkości rotacji i upływającego czasu.
 * @param deltaTime Czas, który minął od ostatniej aktualizacji. Domyślnie 0.0f.
 */
void Triangle::updateRotation(float deltaTime) {
    if (isRotating) {
        rotationAngle += rotationSpeed * deltaTime;
        if (rotationAngle > 360.0f) {
            rotationAngle -= 360.0f; 
        }
    }
}

