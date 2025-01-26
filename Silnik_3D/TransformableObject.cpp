#include "TransformableObject.h"

/**
 * @brief Konstruktor domyœlny klasy TransformableObject.
 *
 * Inicjalizuje obiekt klasy `TransformableObject` z domyœlnymi wartoœciami:
 * - wspó³czynnik skali ustawiony na 1.0,
 * - pozycja (x, y, z) ustawiona na (0.0, 0.0, 0.0),
 * - k¹t obrotu ustawiony na 0.0.
 */
TransformableObject::TransformableObject()
    : scaleFactor(1.0f), posX(0.0f), posY(0.0f), posZ(0.0f), rotationAngle(0.0f) {}

/**
 * @brief Skalowanie obiektu.
 *
 * Zmienia wspó³czynnik skali obiektu, mno¿¹c go przez podany parametr `factor`.
 * @param factor Wspó³czynnik skali, przez który zostanie pomno¿ony aktualny wspó³czynnik skali.
 */
void TransformableObject::scale(float factor) {
    scaleFactor *= factor;
}

/**
 * @brief Ustawienie pozycji obiektu.
 *
 * Zmienia pozycjê obiektu w przestrzeni 3D, przypisuj¹c wartoœci `x`, `y` i `z`.
 * @param x Wartoœæ wspó³rzêdnej X obiektu.
 * @param y Wartoœæ wspó³rzêdnej Y obiektu.
 * @param z Wartoœæ wspó³rzêdnej Z obiektu.
 */
void TransformableObject::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

/**
 * @brief Przemieszczanie obiektu.
 *
 * Przemieszcza obiekt w przestrzeni 3D, dodaj¹c wartoœci `dx` i `dy` do wspó³rzêdnych `x` i `y`.
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
 * Zmienia k¹t obrotu obiektu o zadany parametr `angle`. K¹t jest dodawany do aktualnego k¹ta,
 * a jeœli przekroczy 360 stopni, zostaje zredukowany do wartoœci w przedziale [0, 360).
 * @param angle K¹t obrotu w stopniach.
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
 * Zwraca aktualny wspó³czynnik skali obiektu.
 * @return Wspó³czynnik skali obiektu.
 */
float TransformableObject::getScale() const {
    return scaleFactor;
}

/**
 * @brief Pobranie pozycji obiektu.
 *
 * Zwraca wspó³rzêdne pozycji obiektu w przestrzeni 3D poprzez przekazywanie wartoœci do zmiennych `x`, `y`, `z`.
 * @param x Zmienna, do której zostanie przypisana wspó³rzêdna X obiektu.
 * @param y Zmienna, do której zostanie przypisana wspó³rzêdna Y obiektu.
 * @param z Zmienna, do której zostanie przypisana wspó³rzêdna Z obiektu.
 */
void TransformableObject::getPosition(float& x, float& y, float& z) const {
    x = posX;
    y = posY;
    z = posZ;
}
/**
 * @brief Pobranie k¹ta obrotu obiektu.
 *
 * Zwraca aktualny k¹t obrotu obiektu w stopniach.
 * @return K¹t obrotu obiektu w stopniach.
 */
float TransformableObject::getRotation() const {
    return rotationAngle;
}
