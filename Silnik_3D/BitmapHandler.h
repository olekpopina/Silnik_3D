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


    GLuint texture1;           
    bool isTextureLoaded_1;      
    GLuint texture2;           
    bool isTextureLoaded_2;       
    GLuint texture3;
    bool isTextureLoaded_3;
    GLuint texture4;
    bool isTextureLoaded_4;
    GLuint texture5;
    bool isTextureLoaded_5;
    GLuint texture6;
    bool isTextureLoaded_6;
    GLuint texture7;
    bool isTextureLoaded_7;
    
    GLuint loadSingleTexture(const std::string& filePath);
    bool loadTextures(const std::string& filePath1, const std::string& filePath2, const std::string& filePath3, const std::string& filePath4, const std::string& filePath5, const std::string& filePath6, const std::string& filePath7);
private:
   
    int textureWidth;           // Szerokoœæ tekstury
    int textureHeight;          // Wysokoœæ tekstury
    
};

#endif // BITMAPHANDLER_H
