#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/freeglut.h>
#include "TransformableObject.h"

/**
 * @brief Klasa reprezentująca trójkąt.
 *
 * Klasa `Triangle` dziedziczy po klasie `TransformableObject` i umożliwia tworzenie i rysowanie trójkąta
 * w przestrzeni 3D. Dodatkowo, trójkąt może być obracany wokół osi Z oraz modyfikowana jest jego pozycja.
 */
class Triangle : public TransformableObject {
public:
    /**
     * @brief Konstruktor domyślny klasy Triangle.
     *
     * Inicjalizuje obiekt trójkąta z domyślnymi wartościami współrzędnych wierzchołków, kolorów oraz prędkości obrotu.
     */
    Triangle();

    /**
     * @brief Rysowanie trójkąta.
     *
     * Metoda ta rysuje trójkąt w przestrzeni 3D na podstawie jego współrzędnych wierzchołków oraz przypisanych kolorów.
     * Jest to implementacja wirtualnej funkcji `draw` dziedziczonej z klasy `TransformableObject`.
     */
    void draw() const override;

private:
    float vertices1[9]; /**< Współrzędne pierwszego wierzchołka trójkąta. */
    float vertices2[9]; /**< Współrzędne drugiego wierzchołka trójkąta. */
    float vertices3[9]; /**< Współrzędne trzeciego wierzchołka trójkąta. */
    float colors[9]; /**< Kolory przypisane do wierzchołków trójkąta. */
    bool isRotating = false; /**< Flaga informująca, czy trójkąt jest obracany. */
    float rotationAngle = 0.0f; /**< Kąt obrotu trójkąta. */
    float rotationSpeed = 1.0f; /**< Prędkość obrotu trójkąta. */

public:
    /**
     * @brief Ustawienie stanu obrotu trójkąta.
     *
     * Ta metoda ustawia wartość flagi `isRotating`, która decyduje, czy trójkąt ma być obracany.
     * @param rotate Flaga wskazująca, czy trójkąt ma być obracany.
     */
    void setRotation(bool rotate);

    /**
     * @brief Aktualizacja obrotu trójkąta.
     *
     * Metoda ta aktualizuje kąt obrotu trójkąta na podstawie upływającego czasu.
     * @param deltaTime Czas, który minął od ostatniej aktualizacji. Domyślnie 0.0f.
     */
    void updateRotation(float deltaTime = 0.0f);

    /**
     * @brief Ustawienie pozycji trójkąta.
     *
     * Ta metoda ustawia pozycję trójkąta w przestrzeni 2D, ignorując oś Z.
     * @param x Nowa współrzędna X trójkąta.
     * @param y Nowa współrzędna Y trójkąta.
     */
    void setPosition(float x, float y);

    /**
     * @brief Pobranie współrzędnej X pozycji trójkąta.
     *
     * Zwraca aktualną wartość współrzędnej X trójkąta.
     * @return Wartość współrzędnej X trójkąta.
     */
    float getPositionX() const { return posX; }

    /**
     * @brief Pobranie współrzędnej Y pozycji trójkąta.
     *
     * Zwraca aktualną wartość współrzędnej Y trójkąta.
     * @return Wartość współrzędnej Y trójkąta.
     */
    float getPositionY() const { return posY; }

};

#endif // TRIANGLE_H
