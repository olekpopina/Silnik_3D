#include "BitmapHandler.h"



BitmapHandler::BitmapHandler()
    : texture1(0), texture2(0), texture3(0), texture4(0), texture5(0), texture6(0), texture7(0), textureWidth(0), textureHeight(0), 
    isTextureLoaded_1(false), isTextureLoaded_2(false), isTextureLoaded_3(false), isTextureLoaded_4(false), isTextureLoaded_5(false), isTextureLoaded_6(false), isTextureLoaded_7(false) {
}

BitmapHandler::~BitmapHandler() {
    if (isTextureLoaded_1) {
        glDeleteTextures(1, &texture1);
    }
    if (isTextureLoaded_2) {
        glDeleteTextures(1, &texture2);
    }
    if (isTextureLoaded_3) {
        glDeleteTextures(1, &texture3);
    }
    if (isTextureLoaded_4) {
        glDeleteTextures(1, &texture4);
    }
    if (isTextureLoaded_5) {
        glDeleteTextures(1, &texture5);
    }
    if (isTextureLoaded_6) {
        glDeleteTextures(1, &texture6);
    }
    if (isTextureLoaded_7) {
        glDeleteTextures(1, &texture7);
    }
 
}
GLuint BitmapHandler::loadSingleTexture(const std::string& filePath) {
    sf::Image image;
    if (!image.loadFromFile(filePath)) {
        std::cerr << "Nie mo¿na za³adowaæ obrazu: " << filePath << std::endl;
        return 0;
    }

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    return textureId;
}

bool BitmapHandler::loadTextures(const std::string& filePath1, const std::string& filePath2, const std::string& filePath3, const std::string& filePath4, const std::string& filePath5, const std::string& filePath6, const std::string& filePath7) {
    texture1 = loadSingleTexture(filePath1);
    isTextureLoaded_1 = (texture1 != 0);

    texture2 = loadSingleTexture(filePath2);
    isTextureLoaded_2 = (texture2 != 0);

    texture3 = loadSingleTexture(filePath3);
    isTextureLoaded_3 = (texture3 != 0);

    texture4 = loadSingleTexture(filePath4);
    isTextureLoaded_4 = (texture4 != 0);

    texture5 = loadSingleTexture(filePath5);
    isTextureLoaded_5 = (texture5 != 0);

    texture6 = loadSingleTexture(filePath6);
    isTextureLoaded_6 = (texture6 != 0);

    texture7 = loadSingleTexture(filePath7);
    isTextureLoaded_7 = (texture7 != 0);

    return isTextureLoaded_1 && isTextureLoaded_2 && isTextureLoaded_3 && isTextureLoaded_4 && isTextureLoaded_5 && isTextureLoaded_6 && isTextureLoaded_7;
}


void BitmapHandler::drawBackground() {
    if (!isTextureLoaded_1) return;

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
    glBindTexture(GL_TEXTURE_2D, texture1);

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
void BitmapHandler::bindTextureForCube() {
    if (!isTextureLoaded_2) {
        std::cerr << "Tekstura kostki nie zosta³a za³adowana!" << std::endl;
        return;
    }
    if (!isTextureLoaded_3) {
        std::cerr << "Tekstura kostki nie zosta³a za³adowana!" << std::endl;
        return;
    }
    if (!isTextureLoaded_4) {
        std::cerr << "Tekstura kostki nie zosta³a za³adowana!" << std::endl;
        return;
    }
    if (!isTextureLoaded_5) {
        std::cerr << "Tekstura kostki nie zosta³a za³adowana!" << std::endl;
        return;
    }
    if (!isTextureLoaded_6) {
        std::cerr << "Tekstura kostki nie zosta³a za³adowana!" << std::endl;
        return;
    }
    if (!isTextureLoaded_7) {
        std::cerr << "Tekstura kostki nie zosta³a za³adowana!" << std::endl;
        return;
    }


    glBindTexture(GL_TEXTURE_2D, texture2);
}
