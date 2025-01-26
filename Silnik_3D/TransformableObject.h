#ifndef TRANSFORMABLEOBJECT_H
#define TRANSFORMABLEOBJECT_H

#include "Drawable.h"
#include <GL/freeglut.h>
#include "PrimitiveDrawer.h"

/**
 * @class TransformableObject
 * @brief Klasa reprezentująca obiekt, który można transformować w przestrzeni 3D.
 *
 * `TransformableObject` jest klasą bazową, która umożliwia zmianę pozycji, skali i kąta obrotu obiektów
 * w przestrzeni 3D. Dziedziczy po klasie `Drawable` i udostępnia metody do wykonywania tych transformacji.
 */
class TransformableObject : public Drawable {
protected:
    float scaleFactor;  /**< Współczynnik skali obiektu */
    float posX, posY, posZ; /**< Pozycja obiektu w przestrzeni 3D (współrzędne X, Y, Z) */
    float rotationAngle; /**< Kąt obrotu obiektu w stopniach */

public:
    /**
    * @brief Konstruktor domyślny.
    *
    * Tworzy obiekt `TransformableObject` o domyślnych wartościach dla skali, pozycji i kąta obrotu.
    */
    TransformableObject();

    /**
     * @brief Wirtualny destruktor.
     *
     * Destruktor zapewniający poprawne zwolnienie zasobów w przypadku, gdy obiekt jest usuwany.
     */
    virtual ~TransformableObject() = default;

    /**
     * @brief Skalowanie obiektu.
     *
     * Zmienia skalę obiektu, modyfikując współczynnik skali.
     * @param factor Współczynnik skali, przez który obiekt będzie pomnożony.
     */
    void scale(float factor);

    /**
     * @brief Ustawienie pozycji obiektu.
     *
     * Ustala pozycję obiektu w przestrzeni 3D za pomocą współrzędnych X, Y i Z.
     * @param x Wartość współrzędnej X.
     * @param y Wartość współrzędnej Y.
     * @param z Wartość współrzędnej Z.
     */
    void setPosition(float x, float y, float z);

    /**
     * @brief Przemieszczanie obiektu.
     *
     * Przemieszcza obiekt w przestrzeni 3D o zadany wektor (dx, dy).
     * @param dx Zmiana pozycji w osi X.
     * @param dy Zmiana pozycji w osi Y.
     */
    void move(float dx, float dy);

    /**
     * @brief Obrót obiektu.
     *
     * Zmienia kąt obrotu obiektu wokół osi Z.
     * @param angle Kąt obrotu w stopniach.
     */
    void rotate(float angle);

    /**
     * @brief Pobranie skali obiektu.
     *
     * Zwraca aktualny współczynnik skali obiektu.
     * @return Współczynnik skali obiektu.
     */
    float getScale() const;

    /**
     * @brief Pobranie pozycji obiektu.
     *
     * Zwraca współrzędne X, Y i Z obiektu.
     * @param x Zmienna, do której zostanie przypisana współrzędna X obiektu.
     * @param y Zmienna, do której zostanie przypisana współrzędna Y obiektu.
     * @param z Zmienna, do której zostanie przypisana współrzędna Z obiektu.
     */
    void getPosition(float& x, float& y, float& z) const;

    /**
     * @brief Pobranie kąta obrotu obiektu.
     *
     * Zwraca aktualny kąt obrotu obiektu w stopniach.
     * @return Kąt obrotu obiektu.
     */
    float getRotation() const;
};

#endif // TRANSFORMABLEOBJECT_H
