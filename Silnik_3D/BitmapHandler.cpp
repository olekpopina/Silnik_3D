#include "BitmapHandler.h"

BitmapHandler::BitmapHandler() : textureID(0) {}

BitmapHandler::~BitmapHandler() {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
    }
}

bool BitmapHandler::loadTextureFromFile(const std::string& filename) {
    if (!image.loadFromFile(filename)) {
        std::cerr << "Error: Failed to load image: " << filename << std::endl;
        return false;
    }

    texture.loadFromImage(image); // Za³aduj teksturê z obrazu SFML
    generateTexture(); // Konwersja SFML tekstury na FreeGLUT teksturê
    return true;
}

void BitmapHandler::generateTexture() {
    glGenTextures(1, &textureID);
    if (textureID == 0) {
        std::cerr << "Error: Failed to generate texture ID" << std::endl;
        return;
    }
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        image.getSize().x,
        image.getSize().y,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        image.getPixelsPtr()
    );

    // Logowanie rozmiarów obrazu
    std::cout << "Image size: " << image.getSize().x << "x" << image.getSize().y << std::endl;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    

}


void BitmapHandler::drawBackground() {
    if (textureID == 0) {
        std::cerr << "Error: No texture loaded for background." << std::endl;
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f); // Lewy dolny
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, -1.0f);  // Prawy dolny
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 1.0f);   // Prawy górny
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);  // Lewy górny
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}
