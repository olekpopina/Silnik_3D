#include "Line.h"
#include "PrimitiveDrawer.h"

/**
 * @brief Konstruktor domyślny linii.
 *
 * Inicjalizuje punkt początkowy linii na (0.0f, 0.0f, 0.0f) oraz punkt końcowy na (1.0f, 0.0f, 0.0f).
 */
Line::Line() {
    start[0] = 0.0f; start[1] = 0.0f; start[2] = 0.0f;
    end[0] = 1.0f; end[1] = 0.0f; end[2] = 0.0f;
}

/**
 * @brief Konstruktor inicjalizujący linię na podstawie punktów początkowego i końcowego.
 *
 * @param startX Współrzędna X punktu początkowego.
 * @param startY Współrzędna Y punktu początkowego.
 * @param startZ Współrzędna Z punktu początkowego.
 * @param endX Współrzędna X punktu końcowego.
 * @param endY Współrzędna Y punktu końcowego.
 * @param endZ Współrzędna Z punktu końcowego.
 */
Line::Line(float startX, float startY, float startZ, float endX, float endY, float endZ) {
    start[0] = startX;
    start[1] = startY;
    start[2] = startZ;
    end[0] = endX;
    end[1] = endY;
    end[2] = endZ;
}

/**
 * @brief Ustawia współrzędne punktu początkowego linii.
 *
 * @param x Współrzędna X punktu początkowego.
 * @param y Współrzędna Y punktu początkowego.
 * @param z Współrzędna Z punktu początkowego.
 */
void Line::setStart(float x, float y, float z) {
    start[0] = x;
    start[1] = y;
    start[2] = z;
}

/**
 * @brief Ustawia współrzędne punktu końcowego linii.
 *
 * @param x Współrzędna X punktu końcowego.
 * @param y Współrzędna Y punktu końcowego.
 * @param z Współrzędna Z punktu końcowego.
 */
void Line::setEnd(float x, float y, float z) {
    end[0] = x;
    end[1] = y;
    end[2] = z;
}

/**
 * @brief Pobiera współrzędne punktu początkowego linii.
 *
 * @param x Współrzędna X punktu początkowego.
 * @param y Współrzędna Y punktu początkowego.
 * @param z Współrzędna Z punktu początkowego.
 */
void Line::getStart(float& x, float& y, float& z) const {
    x = start[0];
    y = start[1];
    z = start[2];
}

/**
 * @brief Pobiera współrzędne punktu końcowego linii.
 *
 * @param x Współrzędna X punktu końcowego.
 * @param y Współrzędna Y punktu końcowego.
 * @param z Współrzędna Z punktu końcowego.
 */
void Line::getEnd(float& x, float& y, float& z) const {
    x = end[0];
    y = end[1];
    z = end[2];
}

/**
 * @brief Pobiera współrzędną X punktu początkowego linii.
 *
 * @return Współrzędna X punktu początkowego.
 */
float Line::getStartX() const {
    return start[0];
}

/**
 * @brief Pobiera współrzędną Y punktu początkowego linii.
 *
 * @return Współrzędna Y punktu początkowego.
 */
float Line::getStartY() const {
    return start[1];
}

/**
 * @brief Pobiera współrzędną Z punktu początkowego linii.
 *
 * @return Współrzędna Z punktu początkowego.
 */
float Line::getStartZ() const {
    return start[2];
}

/**
 * @brief Pobiera współrzędną X punktu końcowego linii.
 *
 * @return Współrzędna X punktu końcowego.
 */
float Line::getEndX() const {
    return end[0];
}

/**
 * @brief Pobiera współrzędną Y punktu końcowego linii.
 *
 * @return Współrzędna Y punktu końcowego.
 */
float Line::getEndY() const {
    return end[1];
}

/**
 * @brief Pobiera współrzędną Z punktu końcowego linii.
 *
 * @return Współrzędna Z punktu końcowego.
 */
float Line::getEndZ() const {
    return end[2];
}

/**
 * @brief Rysuje linię w przestrzeni 3D.
 *
 * Funkcja rysuje linię na podstawie współrzędnych punktów początkowego i końcowego,
 * uwzględniając transformacje (pozycję, skalowanie i rotację) obiektu.
 */
void Line::draw() const {
    glPushMatrix();
    glTranslatef(posX, posY, posZ); // Pozycja
    glScalef(scaleFactor, scaleFactor, scaleFactor); // Skalowanie
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f); // Rotacja

    PrimitiveDrawer::drawLine(start[0], start[1], start[2], end[0], end[1], end[2], 5.0f);

    glPopMatrix();
}
