#include "TransformableObject.h"

/**
 * @brief Konstruktor domy�lny klasy TransformableObject.
 *
 * Inicjalizuje obiekt klasy `TransformableObject` z domy�lnymi warto�ciami:
 * - wsp�czynnik skali ustawiony na 1.0,
 * - pozycja (x, y, z) ustawiona na (0.0, 0.0, 0.0),
 * - k�t obrotu ustawiony na 0.0.
 */
TransformableObject::TransformableObject()
    : scaleFactor(1.0f), posX(0.0f), posY(0.0f), posZ(0.0f), rotationAngle(0.0f) {}

/**
 * @brief Skalowanie obiektu.
 *
 * Zmienia wsp�czynnik skali obiektu, mno��c go przez podany parametr `factor`.
 * @param factor Wsp�czynnik skali, przez kt�ry zostanie pomno�ony aktualny wsp�czynnik skali.
 */
void TransformableObject::scale(float factor) {
    scaleFactor *= factor;
}

/**
 * @brief Ustawienie pozycji obiektu.
 *
 * Zmienia pozycj� obiektu w przestrzeni 3D, przypisuj�c warto�ci `x`, `y` i `z`.
 * @param x Warto�� wsp�rz�dnej X obiektu.
 * @param y Warto�� wsp�rz�dnej Y obiektu.
 * @param z Warto�� wsp�rz�dnej Z obiektu.
 */
void TransformableObject::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

/**
 * @brief Przemieszczanie obiektu.
 *
 * Przemieszcza obiekt w przestrzeni 3D, dodaj�c warto�ci `dx` i `dy` do wsp�rz�dnych `x` i `y`.
 * @param dx Zmiana pozycji w osi X.
 * @param dy Zmiana pozycji w osi Y.
 */
void TransformableObject::move(float dx, float dy) {
    posX += dx;
    posY += dy;
}

/**
 * @brief Obr�t obiektu.
 *
 * Zmienia k�t obrotu obiektu o zadany parametr `angle`. K�t jest dodawany do aktualnego k�ta,
 * a je�li przekroczy 360 stopni, zostaje zredukowany do warto�ci w przedziale [0, 360).
 * @param angle K�t obrotu w stopniach.
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
 * Zwraca aktualny wsp�czynnik skali obiektu.
 * @return Wsp�czynnik skali obiektu.
 */
float TransformableObject::getScale() const {
    return scaleFactor;
}

/**
 * @brief Pobranie pozycji obiektu.
 *
 * Zwraca wsp�rz�dne pozycji obiektu w przestrzeni 3D poprzez przekazywanie warto�ci do zmiennych `x`, `y`, `z`.
 * @param x Zmienna, do kt�rej zostanie przypisana wsp�rz�dna X obiektu.
 * @param y Zmienna, do kt�rej zostanie przypisana wsp�rz�dna Y obiektu.
 * @param z Zmienna, do kt�rej zostanie przypisana wsp�rz�dna Z obiektu.
 */
void TransformableObject::getPosition(float& x, float& y, float& z) const {
    x = posX;
    y = posY;
    z = posZ;
}
/**
 * @brief Pobranie k�ta obrotu obiektu.
 *
 * Zwraca aktualny k�t obrotu obiektu w stopniach.
 * @return K�t obrotu obiektu w stopniach.
 */
float TransformableObject::getRotation() const {
    return rotationAngle;
}
