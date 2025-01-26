#include "Point.h"

Point::Point(float x, float y, float z) {
    setPosition(x, y, z); ///< Użycie metody z klasy bazowej TransformableObject do ustawienia pozycji punktu.
}

Point::Point() {
    setPosition(0.0f, 0.0f, 0.0f); ///< Użycie metody z klasy bazowej TransformableObject do ustawienia domyślnej pozycji punktu.
}

/**
 * @brief Ustawia pozycję punktu na zadane współrzędne.
 *
 * Zmienia współrzędne punktu na (x, y, z) przy użyciu metody setPosition z klasy bazowej.
 *
 * @param x Nowa współrzędna X.
 * @param y Nowa współrzędna Y.
 * @param z Nowa współrzędna Z.
 */
void Point::set(float x, float y, float z) {
    setPosition(x, y, z); ///< Użycie metody z klasy bazowej TransformableObject do ustawienia pozycji punktu.
}

/**
 * @brief Przesuwa punkt o zadane wartości w przestrzeni 3D.
 *
 * Punkt jest przesuwany w płaszczyźnie XY przy użyciu metody `move` z klasy bazowej,
 * a współrzędna Z jest ręcznie dostosowywana.
 *
 * @param dx Przemieszczenie w osi X.
 * @param dy Przemieszczenie w osi Y.
 * @param dz Przemieszczenie w osi Z.
 */
void Point::translate(float dx, float dy, float dz) {
    move(dx, dy); ///< Użycie metody `move` z klasy bazowej TransformableObject do przesunięcia w płaszczyźnie XY.
    posZ += dz;   ///< Dodatkowa manipulacja współrzędną Z.
}

/**
 * @brief Pobiera współrzędną X punktu.
 *
 * Zwraca aktualną współrzędną X punktu.
 *
 * @return Współrzędna X punktu.
 */
float Point::getX() const {
    return posX; ///< Zwraca współrzędną X punktu, korzystając z danych przechowywanych w klasie bazowej.
}

/**
 * @brief Pobiera współrzędną Y punktu.
 *
 * Zwraca aktualną współrzędną Y punktu.
 *
 * @return Współrzędna Y punktu.
 */
float Point::getY() const {
    return posY; ///< Zwraca współrzędną Y punktu, korzystając z danych przechowywanych w klasie bazowej.
}

/**
 * @brief Pobiera współrzędną Z punktu.
 *
 * Zwraca aktualną współrzędną Z punktu.
 *
 * @return Współrzędna Z punktu.
 */
float Point::getZ() const {
    return posZ; ///< Zwraca współrzędną Z punktu, korzystając z danych przechowywanych w klasie bazowej.
}

/**
 * @brief Rysuje punkt w przestrzeni 3D.
 *
 * Używa klasy `PrimitiveDrawer` do narysowania punktu w zadanej pozycji (X, Y, Z).
 */
void Point::draw() const {
    PrimitiveDrawer::drawPoint(this->getX(), this->getY(), this->getZ(), 8); ///< Rysowanie punktu przy użyciu klasy PrimitiveDrawer.
}
