#ifndef BITMAPHANDLER_H
#define BITMAPHANDLER_H

#include <SFML/Graphics.hpp>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <string>


/**
 * @class BitmapHandler
 * @brief Klasa do obs³ugi tekstur w aplikacjach wykorzystuj¹cych OpenGL.
 *
 * Klasa umo¿liwia ³adowanie tekstur z plików, ich rysowanie, usuwanie oraz przypisywanie tekstur do obiektów 3D,
 * takich jak t³o i kostki. Mo¿e równie¿ rysowaæ pionki przy u¿yciu tekstur.
 */
class BitmapHandler {
public:
    /**
     * @brief Konstruktor klasy BitmapHandler.
     *
     * Inicjalizuje wszystkie zasoby tekstur.
     */
    BitmapHandler(); // Konstruktor
    /**
       * @brief Destruktor klasy BitmapHandler.
       *
       * Zwalnia zasoby zwi¹zane z teksturami.
       */
    ~BitmapHandler(); // Destruktor

    /**
    * @brief £aduje tekstury z podanych œcie¿ek.
    *
    * @param texturePaths Lista œcie¿ek do plików z teksturami.
    * @return true, jeœli wszystkie tekstury zosta³y pomyœlnie za³adowane, w przeciwnym razie false.
    */
    bool loadTextures(const std::vector<std::string>& texturePaths);
  

    /**
     * @brief Usuwa teksturê.
     *
     * @param texture Referencja do identyfikatora tekstury do usuniêcia.
     */
    void deleteTexture(GLuint& texture);
   
    /**
     * @brief Rysuje t³o przy u¿yciu za³adowanej tekstury.
     */
    void drawBackground();

    /**
     * @brief Rysuje pionek w zadanej pozycji i rozmiarze, u¿ywaj¹c tekstury.
     *
     * @param x Wspó³rzêdna X pozycji pionka.
     * @param y Wspó³rzêdna Y pozycji pionka.
     * @param width Szerokoœæ pionka.
     * @param height Wysokoœæ pionka.
     * @param texture Tekstura do przypisania do pionka.
     */
    void drawPionek(float x, float y, float width, float height, GLuint texture);

    /**
      * @brief Przypisuje teksturê do konkretnej œciany kostki.
      *
      * @param faceIndex Indeks œciany kostki (0-5).
      */
    void bindCubeTexture(int faceIndex);

    // Tekstura t³a
    GLuint textureBackground;

    // Tekstury œcian kostki
    GLuint texture1, texture2, texture3, texture4, texture5, texture6;

    // Tekstury pionków
    GLuint texture_pionek, texture_pionek2;

private:
    /**
     * @brief £aduje pojedyncz¹ teksturê z pliku.
     *
     * @param filePath Œcie¿ka do pliku tekstury.
     * @return Identyfikator tekstury.
     */
    GLuint loadSingleTexture(const std::string& filePath);
};

#endif // BITMAPHANDLER_H
