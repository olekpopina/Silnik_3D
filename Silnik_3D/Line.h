#ifndef LINE_H
#define LINE_H

#include "TransformableObject.h"

/**
 * @class Line
 * @brief Klasa reprezentuj¹ca liniê w przestrzeni 3D.
 *
 * Klasa dziedziczy po TransformableObject i zawiera wspó³rzêdne punktów pocz¹tkowego
 * i koñcowego. Umo¿liwia manipulacjê tymi punktami oraz rysowanie linii w przestrzeni 3D.
 */
class Line : public TransformableObject {
public:

    /**
     * @brief Konstruktor domyœlny.
     *
     * Inicjalizuje liniê na (0, 0, 0) -> (0, 0, 0).
     */
    Line();

    /**
     * @brief Konstruktor, który inicjalizuje liniê na podstawie punktów pocz¹tkowego i koñcowego.
     *
     * @param startX Wspó³rzêdna X punktu pocz¹tkowego.
     * @param startY Wspó³rzêdna Y punktu pocz¹tkowego.
     * @param startZ Wspó³rzêdna Z punktu pocz¹tkowego.
     * @param endX Wspó³rzêdna X punktu koñcowego.
     * @param endY Wspó³rzêdna Y punktu koñcowego.
     * @param endZ Wspó³rzêdna Z punktu koñcowego.
     */
    Line(float startX, float startY, float startZ, float endX, float endY, float endZ);

    /**
     * @brief Ustawia wspó³rzêdne punktu pocz¹tkowego linii.
     *
     * @param x Wspó³rzêdna X punktu pocz¹tkowego.
     * @param y Wspó³rzêdna Y punktu pocz¹tkowego.
     * @param z Wspó³rzêdna Z punktu pocz¹tkowego.
     */
    void setStart(float x, float y, float z);
    
    /**
     * @brief Ustawia wspó³rzêdne punktu koñcowego linii.
     *
     * @param x Wspó³rzêdna X punktu koñcowego.
     * @param y Wspó³rzêdna Y punktu koñcowego.
     * @param z Wspó³rzêdna Z punktu koñcowego.
     */
    void setEnd(float x, float y, float z);

    /**
     * @brief Pobiera wspó³rzêdne punktu pocz¹tkowego linii.
     *
     * @param x Wspó³rzêdna X punktu pocz¹tkowego.
     * @param y Wspó³rzêdna Y punktu pocz¹tkowego.
     * @param z Wspó³rzêdna Z punktu pocz¹tkowego.
     */
    void getStart(float& x, float& y, float& z) const;
    
    /**
     * @brief Pobiera wspó³rzêdne punktu koñcowego linii.
     *
     * @param x Wspó³rzêdna X punktu koñcowego.
     * @param y Wspó³rzêdna Y punktu koñcowego.
     * @param z Wspó³rzêdna Z punktu koñcowego.
     */
    void getEnd(float& x, float& y, float& z) const;
    
    /**
     * @brief Pobiera wspó³rzêdn¹ X punktu pocz¹tkowego linii.
     *
     * @return Wspó³rzêdna X punktu pocz¹tkowego.
     */
    float getStartX() const;
    
    /**
    * @brief Pobiera wspó³rzêdn¹ Y punktu pocz¹tkowego linii.
    *
    * @return Wspó³rzêdna Y punktu pocz¹tkowego.
    */
    float getStartY() const;
    
    /**
     * @brief Pobiera wspó³rzêdn¹ Z punktu pocz¹tkowego linii.
     *
     * @return Wspó³rzêdna Z punktu pocz¹tkowego.
     */
    float getStartZ() const;

    /**
     * @brief Pobiera wspó³rzêdn¹ X punktu koñcowego linii.
     *
     * @return Wspó³rzêdna X punktu koñcowego.
     */
    float getEndX() const;
   
    /**
   * @brief Pobiera wspó³rzêdn¹ Y punktu koñcowego linii.
   *
   * @return Wspó³rzêdna Y punktu koñcowego.
   */
    float getEndY() const;
   
    /**
     * @brief Pobiera wspó³rzêdn¹ Z punktu koñcowego linii.
     *
     * @return Wspó³rzêdna Z punktu koñcowego.
     */
    float getEndZ() const;

    /**
     * @brief Metoda do rysowania linii.
     *
     * Przes³oniêcie metody z klasy bazowej TransformableObject. Odpowiada za rysowanie linii
     * na ekranie.
     */
    void draw() const override; 

private:
    // Tablice przechowuj¹ce wspó³rzêdne punktu pocz¹tkowego i koñcowego linii
    float start[3]; ///< Wspó³rzêdne punktu pocz¹tkowego (X, Y, Z).
    float end[3]; ///< Wspó³rzêdne punktu koñcowego (X, Y, Z).
};

#endif // LINE_H
