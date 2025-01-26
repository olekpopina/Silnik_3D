#ifndef BITMAPHANDLER_H
#define BITMAPHANDLER_H

#include <SFML/Graphics.hpp>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <string>


/**
 * @class BitmapHandler
 * @brief Klasa do obsługi tekstur w aplikacjach wykorzystujących OpenGL.
 *
 * Klasa umożliwia ładowanie tekstur z plików, ich rysowanie, usuwanie oraz przypisywanie tekstur do obiektów 3D,
 * takich jak tło i kostki. Może również rysować pionki przy użyciu tekstur.
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
       * Zwalnia zasoby związane z teksturami.
       */
    ~BitmapHandler(); // Destruktor

    /**
    * @brief Ładuje tekstury z podanych ścieżek.
    *
    * @param texturePaths Lista ścieżek do plików z teksturami.
    * @return true, jeśli wszystkie tekstury zostały pomyślnie załadowane, w przeciwnym razie false.
    */
    bool loadTextures(const std::vector<std::string>& texturePaths);
  

    /**
     * @brief Usuwa teksturę.
     *
     * @param texture Referencja do identyfikatora tekstury do usunięcia.
     */
    void deleteTexture(GLuint& texture);
   
    /**
     * @brief Rysuje tło przy użyciu załadowanej tekstury.
     */
    void drawBackground();

    /**
     * @brief Rysuje pionek w zadanej pozycji i rozmiarze, używając tekstury.
     *
     * @param x Współrzędna X pozycji pionka.
     * @param y Współrzędna Y pozycji pionka.
     * @param width Szerokość pionka.
     * @param height Wysokość pionka.
     * @param texture Tekstura do przypisania do pionka.
     */
    void drawPionek(float x, float y, float width, float height, GLuint texture);

    /**
      * @brief Przypisuje teksturę do konkretnej ściany kostki.
      *
      * @param faceIndex Indeks ściany kostki (0-5).
      */
    void bindCubeTexture(int faceIndex);

    // Tekstura tła
    GLuint textureBackground;

    // Tekstury ścian kostki
    GLuint texture1, texture2, texture3, texture4, texture5, texture6;

    // Tekstury pionków
    GLuint texture_pionek, texture_pionek2;

private:
    /**
     * @brief Ładuje pojedynczą teksturę z pliku.
     *
     * @param filePath Ścieżka do pliku tekstury.
     * @return Identyfikator tekstury.
     */
    GLuint loadSingleTexture(const std::string& filePath);
};

#endif // BITMAPHANDLER_H
