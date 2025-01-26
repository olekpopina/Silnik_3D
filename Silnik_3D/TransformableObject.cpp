#include "TransformableObject.h"

/**
 * @brief Konstruktor domyślny klasy TransformableObject.
 *
 * Inicjalizuje obiekt klasy `TransformableObject` z domyślnymi wartościami:
 * - współczynnik skali ustawiony na 1.0,
 * - pozycja (x, y, z) ustawiona na (0.0, 0.0, 0.0),
 * - kąt obrotu ustawiony na 0.0.
 */
TransformableObject::TransformableObject()
    : scaleFactor(1.0f), posX(0.0f), posY(0.0f), posZ(0.0f), rotationAngle(0.0f) {}

/**
 * @brief Skalowanie obiektu.
 *
 * Zmienia współczynnik skali obiektu, mnożąc go przez podany parametr `factor`.
 * @param factor Współczynnik skali, przez który zostanie pomnożony aktualny współczynnik skali.
 */
void TransformableObject::scale(float factor) {
    scaleFactor *= factor;
}

/**
 * @brief Ustawienie pozycji obiektu.
 *
 * Zmienia pozycję obiektu w przestrzeni 3D, przypisując wartości `x`, `y` i `z`.
 * @param x Wartość współrzędnej X obiektu.
 * @param y Wartość współrzędnej Y obiektu.
 * @param z Wartość współrzędnej Z obiektu.
 */
void TransformableObject::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

/**
 * @brief Przemieszczanie obiektu.
 *
 * Przemieszcza obiekt w przestrzeni 3D, dodając wartości `dx` i `dy` do współrzędnych `x` i `y`.
 * @param dx Zmiana pozycji w osi X.
 * @param dy Zmiana pozycji w osi Y.
 */
void TransformableObject::move(float dx, float dy) {
    posX += dx;
    posY += dy;
}

/**
 * @brief Obrót obiektu.
 *
 * Zmienia kąt obrotu obiektu o zadany parametr `angle`. Kąt jest dodawany do aktualnego kąta,
 * a jeśli przekroczy 360 stopni, zostaje zredukowany do wartości w przedziale [0, 360).
 * @param angle Kąt obrotu w stopniach.
 */
void TransformableObject::rotate(float angle) {
    rotationAngle += angle;
    if (rotationAngle >= 360.0f) {
        rotationAngle -= 360.0f;
    }
}

/**
 * @brief Pobranie skali obiektu.
 *
 * Zwraca aktualny współczynnik skali obiektu.
 * @return Współczynnik skali obiektu.
 */
float TransformableObject::getScale() const {
    return scaleFactor;
}

/**
 * @brief Pobranie pozycji obiektu.
 *
 * Zwraca współrzędne pozycji obiektu w przestrzeni 3D poprzez przekazywanie wartości do zmiennych `x`, `y`, `z`.
 * @param x Zmienna, do której zostanie przypisana współrzędna X obiektu.
 * @param y Zmienna, do której zostanie przypisana współrzędna Y obiektu.
 * @param z Zmienna, do której zostanie przypisana współrzędna Z obiektu.
 */
void TransformableObject::getPosition(float& x, float& y, float& z) const {
    x = posX;
    y = posY;
    z = posZ;
}
/**
 * @brief Pobranie kąta obrotu obiektu.
 *
 * Zwraca aktualny kąt obrotu obiektu w stopniach.
 * @return Kąt obrotu obiektu w stopniach.
 */
float TransformableObject::getRotation() const {
    return rotationAngle;
}
