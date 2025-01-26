#ifndef BITMAPHANDLER_H
#define BITMAPHANDLER_H

#include <SFML/Graphics.hpp>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <string>


/**
 * @class BitmapHandler
 * @brief Klasa do obs�ugi tekstur w aplikacjach wykorzystuj�cych OpenGL.
 *
 * Klasa umo�liwia �adowanie tekstur z plik�w, ich rysowanie, usuwanie oraz przypisywanie tekstur do obiekt�w 3D,
 * takich jak t�o i kostki. Mo�e r�wnie� rysowa� pionki przy u�yciu tekstur.
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
       * Zwalnia zasoby zwi�zane z teksturami.
       */
    ~BitmapHandler(); // Destruktor

    /**
    * @brief �aduje tekstury z podanych �cie�ek.
    *
    * @param texturePaths Lista �cie�ek do plik�w z teksturami.
    * @return true, je�li wszystkie tekstury zosta�y pomy�lnie za�adowane, w przeciwnym razie false.
    */
    bool loadTextures(const std::vector<std::string>& texturePaths);
  

    /**
     * @brief Usuwa tekstur�.
     *
     * @param texture Referencja do identyfikatora tekstury do usuni�cia.
     */
    void deleteTexture(GLuint& texture);
   
    /**
     * @brief Rysuje t�o przy u�yciu za�adowanej tekstury.
     */
    void drawBackground();

    /**
     * @brief Rysuje pionek w zadanej pozycji i rozmiarze, u�ywaj�c tekstury.
     *
     * @param x Wsp�rz�dna X pozycji pionka.
     * @param y Wsp�rz�dna Y pozycji pionka.
     * @param width Szeroko�� pionka.
     * @param height Wysoko�� pionka.
     * @param texture Tekstura do przypisania do pionka.
     */
    void drawPionek(float x, float y, float width, float height, GLuint texture);

    /**
      * @brief Przypisuje tekstur� do konkretnej �ciany kostki.
      *
      * @param faceIndex Indeks �ciany kostki (0-5).
      */
    void bindCubeTexture(int faceIndex);

    // Tekstura t�a
    GLuint textureBackground;

    // Tekstury �cian kostki
    GLuint texture1, texture2, texture3, texture4, texture5, texture6;

    // Tekstury pionk�w
    GLuint texture_pionek, texture_pionek2;

private:
    /**
     * @brief �aduje pojedyncz� tekstur� z pliku.
     *
     * @param filePath �cie�ka do pliku tekstury.
     * @return Identyfikator tekstury.
     */
    GLuint loadSingleTexture(const std::string& filePath);
};

#endif // BITMAPHANDLER_H
