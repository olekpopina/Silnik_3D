
#ifndef PRIMITIVE_DRAWER_H
#define PRIMITIVE_DRAWER_H

#include <GL/freeglut.h>
#include "BitmapHandler.h"
#include "ShadingMode.h"

/**
 * @class PrimitiveDrawer
 * @brief Klasa s³u¿¹ca do rysowania ró¿nych prymitywów w przestrzeni 3D przy u¿yciu OpenGL.
 *
 * Klasa zapewnia statyczne metody do rysowania punktów, linii, trójk¹tów, szeœcianów z teksturami,
 * konfigurowania oœwietlenia oraz ustalania trybu cieniowania.
 */
class PrimitiveDrawer {

public:

    /**
     * @brief Ustawia tryb cieniowania dla obiektów.
     *
     * Zmienia tryb cieniowania w OpenGL na okreœlony tryb.
     *
     * @param mode Tryb cieniowania (np. Phong, Gouraud).
     */
    static void setShadingMode(ShadingMode mode);
    
    /**
    * @brief Rysuje punkt w przestrzeni 3D.
    *
    * U¿ywa OpenGL do rysowania punktu o zadanej pozycji (x, y, z) oraz rozmiarze.
    *
    * @param x Wspó³rzêdna X punktu.
    * @param y Wspó³rzêdna Y punktu.
    * @param z Wspó³rzêdna Z punktu.
    * @param size Rozmiar punktu (domyœlnie 1.0f).
    */
    static void drawPoint(float x, float y, float z, float size = 1.0f);
   
    /**
     * @brief Rysuje liniê miêdzy dwoma punktami w przestrzeni 3D.
     *
     * Rysuje liniê od punktu (x1, y1, z1) do punktu (x2, y2, z2) o zadanej szerokoœci.
     *
     * @param x1 Wspó³rzêdna X pierwszego punktu.
     * @param y1 Wspó³rzêdna Y pierwszego punktu.
     * @param z1 Wspó³rzêdna Z pierwszego punktu.
     * @param x2 Wspó³rzêdna X drugiego punktu.
     * @param y2 Wspó³rzêdna Y drugiego punktu.
     * @param z2 Wspó³rzêdna Z drugiego punktu.
     * @param width Szerokoœæ linii (domyœlnie 2.0f).
     */
    static void drawLine(float x1, float y1, float z1, float x2, float y2, float z2, float width = 2.0f);
    
    /**
    * @brief Rysuje trójk¹t w przestrzeni 3D.
    *
    * Rysuje trójk¹t z³o¿ony z trzech wierzcho³ków, okreœlonych przez tablice `vertices1`, `vertices2`, `vertices3`
    * oraz przypisanych kolorów z tablicy `colors`. Mo¿na ustawiæ równie¿ pozycjê, skalê i k¹t obrotu.
    *
    * @param vertices1 Wspó³rzêdne pierwszego wierzcho³ka trójk¹ta.
    * @param vertices2 Wspó³rzêdne drugiego wierzcho³ka trójk¹ta.
    * @param vertices3 Wspó³rzêdne trzeciego wierzcho³ka trójk¹ta.
    * @param colors Kolory wierzcho³ków.
    * @param posX Wspó³rzêdna X pozycji trójk¹ta.
    * @param posY Wspó³rzêdna Y pozycji trójk¹ta.
    * @param scale Skala trójk¹ta.
    * @param rotationAngle K¹t obrotu trójk¹ta.
    */
    static void drawTriangle(const float vertices1[9], const float vertices2[9],
        const float vertices3[9], const float colors[9],
        float posX, float posY, float scale, float rotationAngle);
    
    /**
    * @brief Rysuje szeœcian z tekstur¹.
    *
    * Rysuje szeœcian o zadanej skali i przesuniêciu, u¿ywaj¹c tekstury wczytanej przy pomocy obiektu `BitmapHandler`.
    *
    * @param scale Skala szeœcianu.
    * @param offsetX Przesuniêcie w osi X.
    * @param offsetY Przesuniêcie w osi Y.
    * @param bitmapHandler Obiekt do obs³ugi bitmapy (tekstury).
    */
    static void drawCubeWithTexture(float scale, float offsetX, float offsetY, BitmapHandler& bitmapHandler);
   
    /**
     * @brief Konfiguruje œwiat³o w OpenGL.
     *
     * Ustawia parametry œwiat³a, takie jak pozycja, kolor ambient, kolor rozproszenia, kolor odbicia, k¹t i wspó³czynnik wyg³adzenia.
     *
     * @param light Identyfikator Ÿród³a œwiat³a (np. GL_LIGHT0).
     * @param position Pozycja Ÿród³a œwiat³a.
     * @param ambient Kolor ambient Ÿród³a œwiat³a.
     * @param diffuse Kolor rozproszenia Ÿród³a œwiat³a.
     * @param specular Kolor odbicia Ÿród³a œwiat³a.
     * @param direction Kierunek œwiat³a (opcjonalnie).
     * @param cutoff K¹t odciêcia œwiat³a (opcjonalnie, domyœlnie 180.0f).
     * @param exponent Wspó³czynnik wyg³adzenia œwiat³a (opcjonalnie, domyœlnie 0.0f).
     */
    static void configureLight(GLenum light, const GLfloat* position, const GLfloat* ambient, const GLfloat* diffuse, const GLfloat* specular, const GLfloat* direction = nullptr, float cutoff = 180.0f, float exponent = 0.0f);

    /**
    * @brief Rysuje szeœcian w przestrzeni 3D.
    *
    * Rysuje szeœcian przy u¿yciu zadanych wierzcho³ków, indeksów, normalnych i kolorów.
    *
    * @param scale Skala szeœcianu.
    * @param offsetX Przesuniêcie w osi X.
    * @param offsetY Przesuniêcie w osi Y.
    * @param vertices Tablica wierzcho³ków szeœcianu.
    * @param indices Tablica indeksów wierzcho³ków szeœcianu.
    * @param normals Tablica normalnych dla ka¿dego wierzcho³ka.
    * @param colors Tablica kolorów dla ka¿dego wierzcho³ka.
    */
    static void drawCube(float scale, float offsetX, float offsetY, const float* vertices, const unsigned int* indices, const float* normals, const float* colors);

    /**
     * @brief Zmienna statyczna do przechowywania ustawionego trybu cieniowania.
     */
   static int textureSet;

   /**
   * @brief Tablica przechowuj¹ca tekstury dla szeœcianu.
   */
   static GLuint textures[6];

private:

    /**
    * @brief Zmienna statyczna przechowuj¹ca bie¿¹cy tryb cieniowania.
    */
    static ShadingMode currentShadingMode;
};

#endif // PRIMITIVE_DRAWER_H