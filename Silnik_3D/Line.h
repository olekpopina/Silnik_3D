#ifndef LINE_H
#define LINE_H

#include "TransformableObject.h"

/**
 * @class Line
 * @brief Klasa reprezentująca linię w przestrzeni 3D.
 *
 * Klasa dziedziczy po TransformableObject i zawiera współrzędne punktów początkowego
 * i końcowego. Umożliwia manipulację tymi punktami oraz rysowanie linii w przestrzeni 3D.
 */
class Line : public TransformableObject {
public:

    /**
     * @brief Konstruktor domyślny.
     *
     * Inicjalizuje linię na (0, 0, 0) -> (0, 0, 0).
     */
    Line();

    /**
     * @brief Konstruktor, który inicjalizuje linię na podstawie punktów początkowego i końcowego.
     *
     * @param startX Współrzędna X punktu początkowego.
     * @param startY Współrzędna Y punktu początkowego.
     * @param startZ Współrzędna Z punktu początkowego.
     * @param endX Współrzędna X punktu końcowego.
     * @param endY Współrzędna Y punktu końcowego.
     * @param endZ Współrzędna Z punktu końcowego.
     */
    Line(float startX, float startY, float startZ, float endX, float endY, float endZ);

    /**
     * @brief Ustawia współrzędne punktu początkowego linii.
     *
     * @param x Współrzędna X punktu początkowego.
     * @param y Współrzędna Y punktu początkowego.
     * @param z Współrzędna Z punktu początkowego.
     */
    void setStart(float x, float y, float z);
    
    /**
     * @brief Ustawia współrzędne punktu końcowego linii.
     *
     * @param x Współrzędna X punktu końcowego.
     * @param y Współrzędna Y punktu końcowego.
     * @param z Współrzędna Z punktu końcowego.
     */
    void setEnd(float x, float y, float z);

    /**
     * @brief Pobiera współrzędne punktu początkowego linii.
     *
     * @param x Współrzędna X punktu początkowego.
     * @param y Współrzędna Y punktu początkowego.
     * @param z Współrzędna Z punktu początkowego.
     */
    void getStart(float& x, float& y, float& z) const;
    
    /**
     * @brief Pobiera współrzędne punktu końcowego linii.
     *
     * @param x Współrzędna X punktu końcowego.
     * @param y Współrzędna Y punktu końcowego.
     * @param z Współrzędna Z punktu końcowego.
     */
    void getEnd(float& x, float& y, float& z) const;
    
    /**
     * @brief Pobiera współrzędną X punktu początkowego linii.
     *
     * @return Współrzędna X punktu początkowego.
     */
    float getStartX() const;
    
    /**
    * @brief Pobiera współrzędną Y punktu początkowego linii.
    *
    * @return Współrzędna Y punktu początkowego.
    */
    float getStartY() const;
    
    /**
     * @brief Pobiera współrzędną Z punktu początkowego linii.
     *
     * @return Współrzędna Z punktu początkowego.
     */
    float getStartZ() const;

    /**
     * @brief Pobiera współrzędną X punktu końcowego linii.
     *
     * @return Współrzędna X punktu końcowego.
     */
    float getEndX() const;
   
    /**
   * @brief Pobiera współrzędną Y punktu końcowego linii.
   *
   * @return Współrzędna Y punktu końcowego.
   */
    float getEndY() const;
   
    /**
     * @brief Pobiera współrzędną Z punktu końcowego linii.
     *
     * @return Współrzędna Z punktu końcowego.
     */
    float getEndZ() const;

    /**
     * @brief Metoda do rysowania linii.
     *
     * Przesłonięcie metody z klasy bazowej TransformableObject. Odpowiada za rysowanie linii
     * na ekranie.
     */
    void draw() const override; 

private:
    // Tablice przechowujące współrzędne punktu początkowego i końcowego linii
    float start[3]; ///< Współrzędne punktu początkowego (X, Y, Z).
    float end[3]; ///< Współrzędne punktu końcowego (X, Y, Z).
};

#endif // LINE_H
