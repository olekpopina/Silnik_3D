#ifndef BITMAPHANDLER_H
#define BITMAPHANDLER_H

#include <SFML/Graphics.hpp>
#include <GL/freeglut.h>
#include <iostream>

class BitmapHandler {
public:
    BitmapHandler();
    ~BitmapHandler();
     void bindTexture();

   

    // Rysowanie obrazu jako t³a
    void drawBackground();

    void bindTextureForCube();


    GLuint texture1;           // Identyfikator tekstury OpenGL
    bool isTextureLoaded_1;       // Flaga wskazuj¹ca, czy tekstura zosta³a za³adowana
    GLuint texture2;           // Identyfikator tekstury OpenGL
    bool isTextureLoaded_2;       // Flaga wskazuj¹ca, czy tekstura zosta³a za³adowana
    GLuint loadSingleTexture(const std::string& filePath);
    bool loadTextures(const std::string& filePath1, const std::string& filePath2);
private:
   
    int textureWidth;           // Szerokoœæ tekstury
    int textureHeight;          // Wysokoœæ tekstury
    
};

#endif // BITMAPHANDLER_H
