#ifndef POINT_H
#define POINT_H

#include "TransformableObject.h"

/**
 * @class Point
 * @brief Reprezentuje punkt w przestrzeni 3D.
 *
 * Klasa umożliwia przechowywanie współrzędnych punktu oraz operacje na nim, takie jak ustawianie pozycji,
 * przesuwanie, pobieranie współrzędnych i rysowanie.
 */
class Point : public TransformableObject {
public:
    /**
     * @brief Konstruktor z parametrami dla współrzędnych punktu.
     *
     * Tworzy punkt o zadanych współrzędnych (x, y, z).
     *
     * @param x Współrzędna X punktu.
     * @param y Współrzędna Y punktu.
     * @param z Współrzędna Z punktu.
     */
    Point(float x, float y, float z);

    /**
     * @brief Konstruktor domyślny.
     *
     * Tworzy punkt o współrzędnych (0, 0, 0).
     */
    Point();

    /**
     * @brief Ustawia współrzędne punktu.
     *
     * Zmienia pozycję punktu na zadane współrzędne (x, y, z).
     *
     * @param x Nowa współrzędna X.
     * @param y Nowa współrzędna Y.
     * @param z Nowa współrzędna Z.
     */
    void set(float x, float y, float z);

    /**
     * @brief Przesuwa punkt o zadane wektory.
     *
     * Zmienia pozycję punktu dodając przesunięcie (dx, dy, dz) do obecnych współrzędnych.
     *
     * @param dx Przemieszczenie w osi X.
     * @param dy Przemieszczenie w osi Y.
     * @param dz Przemieszczenie w osi Z.
     */
    void translate(float dx, float dy, float dz);

    /**
     * @brief Pobiera współrzędną X punktu.
     *
     * @return Współrzędna X punktu.
     */
    float getX() const;

    /**
     * @brief Pobiera współrzędną Y punktu.
     *
     * @return Współrzędna Y punktu.
     */
    float getY() const;

    /**
     * @brief Pobiera współrzędną Z punktu.
     *
     * @return Współrzędna Z punktu.
     */
    float getZ() const;

    /**
     * @brief Rysuje punkt.
     *
     * Używa metod z klasy bazowej `TransformableObject` do zastosowania transformacji i rysowania punktu.
     * Ta funkcja jest nadpisana z klasy bazowej.
     */
    void draw() const override;
};

#endif // POINT_H
