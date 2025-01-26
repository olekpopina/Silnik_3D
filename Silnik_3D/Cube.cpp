#include "Cube.h"

/**
 * @brief Konstruktor klasy Cube.
 *
 * Inicjalizuje współrzędne wierzchołków, indeksy, normalki i kolory dla sześcianu,
 * oraz ustawia początkowe wartości zmiennych obrotu, skali i innych parametrów.
 * Współrzędne wierzchołków określają rozmiar i kształt sześcianu.
 * Indeksy wierzchołków pozwalają na rysowanie powierzchni sześcianu, a normalki i kolory
 * są przypisane do wierzchołków w celu poprawnego oświetlenia i wizualizacji.
 */
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
} {
}

/**
 * @brief Funkcja rysująca sześcian.
 *
 * Funkcja wykorzystuje transformacje (przesunięcie, skalowanie, obrót), aby umiejscowić sześcian
 * w odpowiedniej pozycji w przestrzeni 3D. Następnie wywołuje metodę `drawCube` klasy PrimitiveDrawer,
 * aby narysować sześcian z wykorzystaniem wcześniej zdefiniowanych współrzędnych wierzchołków,
 * indeksów, normalnych i kolorów.
 */
void Cube::draw() const {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);  ///< Przemieszcza sześcian do określonej pozycji.
    glScalef(scaleFactor, scaleFactor, scaleFactor);  ///< Skaluje sześcian.
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);  ///< Obraca sześcian wokół osi Y.

    // Rysuje sześcian z użyciem klasy PrimitiveDrawer.
    PrimitiveDrawer::drawCube(scaleFactor, posX, posY, vertices, indices, normals, colors);
    glPopMatrix();
}

/**
 * @brief Ustawia flagę rotacji sześcianu.
 *
 * Funkcja umożliwia włączenie lub wyłączenie rotacji sześcianu.
 * Jeśli parametr `rotating` jest ustawiony na true, sześcian zacznie się obracać.
 *
 * @param rotating Określa, czy sześcian ma się obracać (true) czy nie (false).
 */
void Cube::setRotationC(bool rotating) {
    isRotating = rotating;
}

/**
 * @brief Aktualizuje kąt rotacji sześcianu na podstawie upływającego czasu.
 *
 * Funkcja zwiększa kąt rotacji sześcianu na podstawie prędkości rotacji i czasu,
 * który upłynął od ostatniej klatki (deltaTime).
 * Kąt rotacji jest ograniczany do zakresu [0, 360] stopni.
 *
 * @param deltaTime Czas, który upłynął od ostatniej aktualizacji w sekundach.
 */
void Cube::updateRotationC(float deltaTime) {
    if (isRotating) {
        rotationAngle += rotationSpeed * deltaTime;

        // Ogranicza kąt rotacji do zakresu 0-360 stopni.
        if (rotationAngle > 360.0f) {
            rotationAngle -= 360.0f;
        }
    }
}
