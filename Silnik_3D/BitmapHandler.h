#ifndef BITMAPHANDLER_H
#define BITMAPHANDLER_H

#include <SFML/Graphics.hpp>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <string>

class BitmapHandler {
public:
    BitmapHandler();
    ~BitmapHandler();

    bool loadTextures(const std::vector<std::string>& texturePaths); // £adowanie tekstur
    void deleteTexture(GLuint& texture, bool& isLoaded); // Usuwanie tekstur
    void drawBackground(); // Rysowanie t³a
    void drawPionek(float x, float y, float width, float height, GLuint texture);
    void bindCubeTexture(int faceIndex); // Przypisanie tekstury do œciany kostki
    bool isTextureLoaded(GLuint texture); // Sprawdzenie, czy tekstura zosta³a za³adowana
    GLuint texture2, texture3, texture4, texture5, texture6, texture7; // Tekstury œcian kostki

    GLuint texture1; // Tekstura t³a
    GLuint texture_pionek; // Tekstura dla pionka 1
    GLuint texture_pionek2; // Tekstura dla pionka 2

private:
    
    bool isTextureLoaded_1, isTextureLoaded_2, isTextureLoaded_3, isTextureLoaded_4;
    bool isTextureLoaded_5, isTextureLoaded_6, isTextureLoaded_7;
    bool isTextureLoaded_pionek, isTextureLoaded_pionek2;

    GLuint loadSingleTexture(const std::string& filePath); // £adowanie pojedynczej tekstury
};

#endif // BITMAPHANDLER_H
