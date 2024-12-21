#include "BitmapHandler.h"

BitmapHandler::BitmapHandler()
    : textureId(0), textureWidth(0), textureHeight(0), isTextureLoaded(false) {
}

BitmapHandler::~BitmapHandler() {
    if (isTextureLoaded) {
        glDeleteTextures(1, &textureId);
    }
}

bool BitmapHandler::loadTexture(const std::string& filePath) {
    sf::Image image;
    if (!image.loadFromFile(filePath)) {
        std::cerr << "Nie mozna wczytac obrazu: " << filePath << std::endl;
        return false;
    }

    textureWidth = image.getSize().x;
    textureHeight = image.getSize().y;

    // Generowanie tekstury w OpenGL
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Za³aduj dane obrazu jako teksturê
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    // Ustawienia filtrowania tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    isTextureLoaded = true;

    std::cout << "Obraz zaladowano pomylnie: " << filePath << std::endl;
    return true;
}

void BitmapHandler::drawBackground() {
    if (!isTextureLoaded) return;

    // Save the current projection and modelview matrices
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0); // Orthographic projection for 2D drawing

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Disable depth test and enable textures
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Draw a fullscreen quad
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f); // Bottom-left
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 0.0f); // Bottom-right
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f); // Top-right
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 1.0f); // Top-left
    glEnd();

    // Restore previous settings
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
