#ifndef LINE_H
#define LINE_H

#include "TransformableObject.h"

/**
 * @class Line
 * @brief Klasa reprezentuj�ca lini� w przestrzeni 3D.
 *
 * Klasa dziedziczy po TransformableObject i zawiera wsp�rz�dne punkt�w pocz�tkowego
 * i ko�cowego. Umo�liwia manipulacj� tymi punktami oraz rysowanie linii w przestrzeni 3D.
 */
class Line : public TransformableObject {
public:

    /**
     * @brief Konstruktor domy�lny.
     *
     * Inicjalizuje lini� na (0, 0, 0) -> (0, 0, 0).
     */
    Line();

    /**
     * @brief Konstruktor, kt�ry inicjalizuje lini� na podstawie punkt�w pocz�tkowego i ko�cowego.
     *
     * @param startX Wsp�rz�dna X punktu pocz�tkowego.
     * @param startY Wsp�rz�dna Y punktu pocz�tkowego.
     * @param startZ Wsp�rz�dna Z punktu pocz�tkowego.
     * @param endX Wsp�rz�dna X punktu ko�cowego.
     * @param endY Wsp�rz�dna Y punktu ko�cowego.
     * @param endZ Wsp�rz�dna Z punktu ko�cowego.
     */
    Line(float startX, float startY, float startZ, float endX, float endY, float endZ);

    /**
     * @brief Ustawia wsp�rz�dne punktu pocz�tkowego linii.
     *
     * @param x Wsp�rz�dna X punktu pocz�tkowego.
     * @param y Wsp�rz�dna Y punktu pocz�tkowego.
     * @param z Wsp�rz�dna Z punktu pocz�tkowego.
     */
    void setStart(float x, float y, float z);
    
    /**
     * @brief Ustawia wsp�rz�dne punktu ko�cowego linii.
     *
     * @param x Wsp�rz�dna X punktu ko�cowego.
     * @param y Wsp�rz�dna Y punktu ko�cowego.
     * @param z Wsp�rz�dna Z punktu ko�cowego.
     */
    void setEnd(float x, float y, float z);

    /**
     * @brief Pobiera wsp�rz�dne punktu pocz�tkowego linii.
     *
     * @param x Wsp�rz�dna X punktu pocz�tkowego.
     * @param y Wsp�rz�dna Y punktu pocz�tkowego.
     * @param z Wsp�rz�dna Z punktu pocz�tkowego.
     */
    void getStart(float& x, float& y, float& z) const;
    
    /**
     * @brief Pobiera wsp�rz�dne punktu ko�cowego linii.
     *
     * @param x Wsp�rz�dna X punktu ko�cowego.
     * @param y Wsp�rz�dna Y punktu ko�cowego.
     * @param z Wsp�rz�dna Z punktu ko�cowego.
     */
    void getEnd(float& x, float& y, float& z) const;
    
    /**
     * @brief Pobiera wsp�rz�dn� X punktu pocz�tkowego linii.
     *
     * @return Wsp�rz�dna X punktu pocz�tkowego.
     */
    float getStartX() const;
    
    /**
    * @brief Pobiera wsp�rz�dn� Y punktu pocz�tkowego linii.
    *
    * @return Wsp�rz�dna Y punktu pocz�tkowego.
    */
    float getStartY() const;
    
    /**
     * @brief Pobiera wsp�rz�dn� Z punktu pocz�tkowego linii.
     *
     * @return Wsp�rz�dna Z punktu pocz�tkowego.
     */
    float getStartZ() const;

    /**
     * @brief Pobiera wsp�rz�dn� X punktu ko�cowego linii.
     *
     * @return Wsp�rz�dna X punktu ko�cowego.
     */
    float getEndX() const;
   
    /**
   * @brief Pobiera wsp�rz�dn� Y punktu ko�cowego linii.
   *
   * @return Wsp�rz�dna Y punktu ko�cowego.
   */
    float getEndY() const;
   
    /**
     * @brief Pobiera wsp�rz�dn� Z punktu ko�cowego linii.
     *
     * @return Wsp�rz�dna Z punktu ko�cowego.
     */
    float getEndZ() const;

    /**
     * @brief Metoda do rysowania linii.
     *
     * Przes�oni�cie metody z klasy bazowej TransformableObject. Odpowiada za rysowanie linii
     * na ekranie.
     */
    void draw() const override; 

private:
    // Tablice przechowuj�ce wsp�rz�dne punktu pocz�tkowego i ko�cowego linii
    float start[3]; ///< Wsp�rz�dne punktu pocz�tkowego (X, Y, Z).
    float end[3]; ///< Wsp�rz�dne punktu ko�cowego (X, Y, Z).
};

#endif // LINE_H
