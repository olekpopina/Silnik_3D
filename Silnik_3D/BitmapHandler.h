#ifndef BITMAPHANDLER_H
#define BITMAPHANDLER_H

#include <SFML/Graphics.hpp>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <string>

class BitmapHandler {
public:
    BitmapHandler(); // Konstruktor
    ~BitmapHandler(); // Destruktor

    // �adowanie tekstur z podanych �cie�ek
    bool loadTextures(const std::vector<std::string>& texturePaths);
    void deleteTexture(GLuint& texture);
    void drawBackground();

    // Rysowanie pionka
    void drawPionek(float x, float y, float width, float height, GLuint texture);

    // Przypisanie tekstury do �ciany kostki
    void bindCubeTexture(int faceIndex);

    // Tekstura t�a
    GLuint textureBackground;

    // Tekstury �cian kostki
    GLuint texture1, texture2, texture3, texture4, texture5, texture6;

    // Tekstury pionk�w
    GLuint texture_pionek, texture_pionek2;

private:
    // �adowanie pojedynczej tekstury z pliku
    GLuint loadSingleTexture(const std::string& filePath);
};

#endif // BITMAPHANDLER_H
