
#ifndef PRIMITIVE_DRAWER_H
#define PRIMITIVE_DRAWER_H

#include <GL/freeglut.h>
#include "BitmapHandler.h"
#include "ShadingMode.h"

/**
 * @class PrimitiveDrawer
 * @brief Klasa służąca do rysowania różnych prymitywów w przestrzeni 3D przy użyciu OpenGL.
 *
 * Klasa zapewnia statyczne metody do rysowania punktów, linii, trójkątów, sześcianów z teksturami,
 * konfigurowania oświetlenia oraz ustalania trybu cieniowania.
 */
class PrimitiveDrawer {

public:

    /**
     * @brief Ustawia tryb cieniowania dla obiektów.
     *
     * Zmienia tryb cieniowania w OpenGL na określony tryb.
     *
     * @param mode Tryb cieniowania (np. Phong, Gouraud).
     */
    static void setShadingMode(ShadingMode mode);
    
    /**
    * @brief Rysuje punkt w przestrzeni 3D.
    *
    * Używa OpenGL do rysowania punktu o zadanej pozycji (x, y, z) oraz rozmiarze.
    *
    * @param x Współrzędna X punktu.
    * @param y Współrzędna Y punktu.
    * @param z Współrzędna Z punktu.
    * @param size Rozmiar punktu (domyślnie 1.0f).
    */
    static void drawPoint(float x, float y, float z, float size = 1.0f);
   
    /**
     * @brief Rysuje linię między dwoma punktami w przestrzeni 3D.
     *
     * Rysuje linię od punktu (x1, y1, z1) do punktu (x2, y2, z2) o zadanej szerokości.
     *
     * @param x1 Współrzędna X pierwszego punktu.
     * @param y1 Współrzędna Y pierwszego punktu.
     * @param z1 Współrzędna Z pierwszego punktu.
     * @param x2 Współrzędna X drugiego punktu.
     * @param y2 Współrzędna Y drugiego punktu.
     * @param z2 Współrzędna Z drugiego punktu.
     * @param width Szerokość linii (domyślnie 2.0f).
     */
    static void drawLine(float x1, float y1, float z1, float x2, float y2, float z2, float width = 2.0f);
    
    /**
    * @brief Rysuje trójkąt w przestrzeni 3D.
    *
    * Rysuje trójkąt złożony z trzech wierzchołków, określonych przez tablice `vertices1`, `vertices2`, `vertices3`
    * oraz przypisanych kolorów z tablicy `colors`. Można ustawić również pozycję, skalę i kąt obrotu.
    *
    * @param vertices1 Współrzędne pierwszego wierzchołka trójkąta.
    * @param vertices2 Współrzędne drugiego wierzchołka trójkąta.
    * @param vertices3 Współrzędne trzeciego wierzchołka trójkąta.
    * @param colors Kolory wierzchołków.
    * @param posX Współrzędna X pozycji trójkąta.
    * @param posY Współrzędna Y pozycji trójkąta.
    * @param scale Skala trójkąta.
    * @param rotationAngle Kąt obrotu trójkąta.
    */
    static void drawTriangle(const float vertices1[9], const float vertices2[9],
        const float vertices3[9], const float colors[9],
        float posX, float posY, float scale, float rotationAngle);
    
    /**
    * @brief Rysuje sześcian z teksturą.
    *
    * Rysuje sześcian o zadanej skali i przesunięciu, używając tekstury wczytanej przy pomocy obiektu `BitmapHandler`.
    *
    * @param scale Skala sześcianu.
    * @param offsetX Przesunięcie w osi X.
    * @param offsetY Przesunięcie w osi Y.
    * @param bitmapHandler Obiekt do obsługi bitmapy (tekstury).
    */
    static void drawCubeWithTexture(float scale, float offsetX, float offsetY, BitmapHandler& bitmapHandler);
   
    /**
     * @brief Konfiguruje światło w OpenGL.
     *
     * Ustawia parametry światła, takie jak pozycja, kolor ambient, kolor rozproszenia, kolor odbicia, kąt i współczynnik wygładzenia.
     *
     * @param light Identyfikator źródła światła (np. GL_LIGHT0).
     * @param position Pozycja źródła światła.
     * @param ambient Kolor ambient źródła światła.
     * @param diffuse Kolor rozproszenia źródła światła.
     * @param specular Kolor odbicia źródła światła.
     * @param direction Kierunek światła (opcjonalnie).
     * @param cutoff Kąt odcięcia światła (opcjonalnie, domyślnie 180.0f).
     * @param exponent Współczynnik wygładzenia światła (opcjonalnie, domyślnie 0.0f).
     */
    static void configureLight(GLenum light, const GLfloat* position, const GLfloat* ambient, const GLfloat* diffuse, const GLfloat* specular, const GLfloat* direction = nullptr, float cutoff = 180.0f, float exponent = 0.0f);

    /**
    * @brief Rysuje sześcian w przestrzeni 3D.
    *
    * Rysuje sześcian przy użyciu zadanych wierzchołków, indeksów, normalnych i kolorów.
    *
    * @param scale Skala sześcianu.
    * @param offsetX Przesunięcie w osi X.
    * @param offsetY Przesunięcie w osi Y.
    * @param vertices Tablica wierzchołków sześcianu.
    * @param indices Tablica indeksów wierzchołków sześcianu.
    * @param normals Tablica normalnych dla każdego wierzchołka.
    * @param colors Tablica kolorów dla każdego wierzchołka.
    */
    static void drawCube(float scale, float offsetX, float offsetY, const float* vertices, const unsigned int* indices, const float* normals, const float* colors);

    /**
     * @brief Zmienna statyczna do przechowywania ustawionego trybu cieniowania.
     */
   static int textureSet;

   /**
   * @brief Tablica przechowująca tekstury dla sześcianu.
   */
   static GLuint textures[6];

private:

    /**
    * @brief Zmienna statyczna przechowująca bieżący tryb cieniowania.
    */
    static ShadingMode currentShadingMode;
};

#endif // PRIMITIVE_DRAWER_H