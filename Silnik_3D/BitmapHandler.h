#ifndef BITMAP_HANDLER_H
#define BITMAP_HANDLER_H

#include <SFML/Graphics.hpp>
#include <GL/freeglut.h>
#include <iostream>

class BitmapHandler {
public:
    BitmapHandler();
    ~BitmapHandler();

    bool loadTextureFromFile(const std::string& filename);
    void drawBackground();

private:
    GLuint textureID;
    sf::Texture texture; // SFML texture for loading image
    sf::Image image;     // SFML image for pixel access

    void generateTexture();
};

#endif // BITMAPHANDLER_H

