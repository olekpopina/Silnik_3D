#ifndef BITMAPHANDLER_H
#define BITMAPHANDLER_H

#include <SFML/Graphics.hpp>
#include <GL/freeglut.h>
#include <iostream>

class BitmapHandler {
public:
    BitmapHandler();
    ~BitmapHandler();

    // £adowanie obrazu
    bool loadTexture(const std::string& filePath);

    // Rysowanie obrazu jako t³a
    void drawBackground();

    void drawCubeFace(float x, float y, float z, float width, float height, GLfloat textureCoordinates[4][2]);

  
    bool isTextureLoaded;       // Flaga wskazuj¹ca, czy tekstura zosta³a za³adowana
private:
    GLuint textureId;           // Identyfikator tekstury OpenGL
    int textureWidth;           // Szerokoœæ tekstury
    int textureHeight;          // Wysokoœæ tekstury
    
};

#endif // BITMAPHANDLER_H
