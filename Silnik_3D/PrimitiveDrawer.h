
#ifndef PRIMITIVE_DRAWER_H
#define PRIMITIVE_DRAWER_H

#include <GL/freeglut.h>
#include "BitmapHandler.h"
#include "ShadingMode.h"

/**
 * @class PrimitiveDrawer
 * @brief Klasa s�u��ca do rysowania r�nych prymityw�w w przestrzeni 3D przy u�yciu OpenGL.
 *
 * Klasa zapewnia statyczne metody do rysowania punkt�w, linii, tr�jk�t�w, sze�cian�w z teksturami,
 * konfigurowania o�wietlenia oraz ustalania trybu cieniowania.
 */
class PrimitiveDrawer {

public:

    /**
     * @brief Ustawia tryb cieniowania dla obiekt�w.
     *
     * Zmienia tryb cieniowania w OpenGL na okre�lony tryb.
     *
     * @param mode Tryb cieniowania (np. Phong, Gouraud).
     */
    static void setShadingMode(ShadingMode mode);
    
    /**
    * @brief Rysuje punkt w przestrzeni 3D.
    *
    * U�ywa OpenGL do rysowania punktu o zadanej pozycji (x, y, z) oraz rozmiarze.
    *
    * @param x Wsp�rz�dna X punktu.
    * @param y Wsp�rz�dna Y punktu.
    * @param z Wsp�rz�dna Z punktu.
    * @param size Rozmiar punktu (domy�lnie 1.0f).
    */
    static void drawPoint(float x, float y, float z, float size = 1.0f);
   
    /**
     * @brief Rysuje lini� mi�dzy dwoma punktami w przestrzeni 3D.
     *
     * Rysuje lini� od punktu (x1, y1, z1) do punktu (x2, y2, z2) o zadanej szeroko�ci.
     *
     * @param x1 Wsp�rz�dna X pierwszego punktu.
     * @param y1 Wsp�rz�dna Y pierwszego punktu.
     * @param z1 Wsp�rz�dna Z pierwszego punktu.
     * @param x2 Wsp�rz�dna X drugiego punktu.
     * @param y2 Wsp�rz�dna Y drugiego punktu.
     * @param z2 Wsp�rz�dna Z drugiego punktu.
     * @param width Szeroko�� linii (domy�lnie 2.0f).
     */
    static void drawLine(float x1, float y1, float z1, float x2, float y2, float z2, float width = 2.0f);
    
    /**
    * @brief Rysuje tr�jk�t w przestrzeni 3D.
    *
    * Rysuje tr�jk�t z�o�ony z trzech wierzcho�k�w, okre�lonych przez tablice `vertices1`, `vertices2`, `vertices3`
    * oraz przypisanych kolor�w z tablicy `colors`. Mo�na ustawi� r�wnie� pozycj�, skal� i k�t obrotu.
    *
    * @param vertices1 Wsp�rz�dne pierwszego wierzcho�ka tr�jk�ta.
    * @param vertices2 Wsp�rz�dne drugiego wierzcho�ka tr�jk�ta.
    * @param vertices3 Wsp�rz�dne trzeciego wierzcho�ka tr�jk�ta.
    * @param colors Kolory wierzcho�k�w.
    * @param posX Wsp�rz�dna X pozycji tr�jk�ta.
    * @param posY Wsp�rz�dna Y pozycji tr�jk�ta.
    * @param scale Skala tr�jk�ta.
    * @param rotationAngle K�t obrotu tr�jk�ta.
    */
    static void drawTriangle(const float vertices1[9], const float vertices2[9],
        const float vertices3[9], const float colors[9],
        float posX, float posY, float scale, float rotationAngle);
    
    /**
    * @brief Rysuje sze�cian z tekstur�.
    *
    * Rysuje sze�cian o zadanej skali i przesuni�ciu, u�ywaj�c tekstury wczytanej przy pomocy obiektu `BitmapHandler`.
    *
    * @param scale Skala sze�cianu.
    * @param offsetX Przesuni�cie w osi X.
    * @param offsetY Przesuni�cie w osi Y.
    * @param bitmapHandler Obiekt do obs�ugi bitmapy (tekstury).
    */
    static void drawCubeWithTexture(float scale, float offsetX, float offsetY, BitmapHandler& bitmapHandler);
   
    /**
     * @brief Konfiguruje �wiat�o w OpenGL.
     *
     * Ustawia parametry �wiat�a, takie jak pozycja, kolor ambient, kolor rozproszenia, kolor odbicia, k�t i wsp�czynnik wyg�adzenia.
     *
     * @param light Identyfikator �r�d�a �wiat�a (np. GL_LIGHT0).
     * @param position Pozycja �r�d�a �wiat�a.
     * @param ambient Kolor ambient �r�d�a �wiat�a.
     * @param diffuse Kolor rozproszenia �r�d�a �wiat�a.
     * @param specular Kolor odbicia �r�d�a �wiat�a.
     * @param direction Kierunek �wiat�a (opcjonalnie).
     * @param cutoff K�t odci�cia �wiat�a (opcjonalnie, domy�lnie 180.0f).
     * @param exponent Wsp�czynnik wyg�adzenia �wiat�a (opcjonalnie, domy�lnie 0.0f).
     */
    static void configureLight(GLenum light, const GLfloat* position, const GLfloat* ambient, const GLfloat* diffuse, const GLfloat* specular, const GLfloat* direction = nullptr, float cutoff = 180.0f, float exponent = 0.0f);

    /**
    * @brief Rysuje sze�cian w przestrzeni 3D.
    *
    * Rysuje sze�cian przy u�yciu zadanych wierzcho�k�w, indeks�w, normalnych i kolor�w.
    *
    * @param scale Skala sze�cianu.
    * @param offsetX Przesuni�cie w osi X.
    * @param offsetY Przesuni�cie w osi Y.
    * @param vertices Tablica wierzcho�k�w sze�cianu.
    * @param indices Tablica indeks�w wierzcho�k�w sze�cianu.
    * @param normals Tablica normalnych dla ka�dego wierzcho�ka.
    * @param colors Tablica kolor�w dla ka�dego wierzcho�ka.
    */
    static void drawCube(float scale, float offsetX, float offsetY, const float* vertices, const unsigned int* indices, const float* normals, const float* colors);

    /**
     * @brief Zmienna statyczna do przechowywania ustawionego trybu cieniowania.
     */
   static int textureSet;

   /**
   * @brief Tablica przechowuj�ca tekstury dla sze�cianu.
   */
   static GLuint textures[6];

private:

    /**
    * @brief Zmienna statyczna przechowuj�ca bie��cy tryb cieniowania.
    */
    static ShadingMode currentShadingMode;
};

#endif // PRIMITIVE_DRAWER_H