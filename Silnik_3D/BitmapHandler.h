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
    // �adowanie obrazu
    bool loadTexture(const std::string& filePath);

    // Rysowanie obrazu jako t�a
    void drawBackground();

    GLuint textureId;           // Identyfikator tekstury OpenGL
  
    bool isTextureLoaded;       // Flaga wskazuj�ca, czy tekstura zosta�a za�adowana
private:
   
    int textureWidth;           // Szeroko�� tekstury
    int textureHeight;          // Wysoko�� tekstury
    
};

#endif // BITMAPHANDLER_H
