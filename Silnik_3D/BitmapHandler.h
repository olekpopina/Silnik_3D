#ifndef BITMAPHANDLER_H
#define BITMAPHANDLER_H

#include <SFML/Graphics.hpp>
#include <GL/freeglut.h>
#include <iostream>

class BitmapHandler {
public:
    BitmapHandler();
    ~BitmapHandler();

    // �adowanie obrazu
    bool loadTexture(const std::string& filePath);

    // Rysowanie obrazu jako t�a
    void drawBackground();

private:
    GLuint textureId;           // Identyfikator tekstury OpenGL
    int textureWidth;           // Szeroko�� tekstury
    int textureHeight;          // Wysoko�� tekstury
    bool isTextureLoaded;       // Flaga wskazuj�ca, czy tekstura zosta�a za�adowana
};

#endif // BITMAPHANDLER_H
