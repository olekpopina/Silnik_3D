#include "BitmapHandler.h"

BitmapHandler::BitmapHandler()
    : texture1(0), texture2(1), texture3(2), texture4(3), texture5(4), texture6(5), texture7(6), texture_pionek(7), texture_pionek2(8), textureWidth(9), textureHeight(10),
    isTextureLoaded_1(false), isTextureLoaded_2(false), isTextureLoaded_3(false), isTextureLoaded_4(false), isTextureLoaded_5(false), isTextureLoaded_6(false), isTextureLoaded_7(false), isTextureLoaded_pionek(false), isTextureLoaded_pionek2(false) {
   
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
    if (isTextureLoaded_pionek) {
        glDeleteTextures(1, &texture_pionek);
    }
    if (isTextureLoaded_pionek2) {
        glDeleteTextures(1, &texture_pionek2);
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

bool BitmapHandler::loadTextures(const std::string& filePath1, const std::string& filePath2, const std::string& filePath3, const std::string& filePath4, const std::string& filePath5, const std::string& filePath6, const std::string& filePath7, const std::string& pionek, const std::string& pionek2) {
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

    texture_pionek = loadSingleTexture(pionek);
    isTextureLoaded_pionek = (texture_pionek != 0);

    texture_pionek2 = loadSingleTexture(pionek2);
    isTextureLoaded_pionek2 = (texture_pionek2 != 0);

   
    
    return isTextureLoaded_1 && isTextureLoaded_2 && isTextureLoaded_3 && isTextureLoaded_4 && isTextureLoaded_5 && isTextureLoaded_6 && isTextureLoaded_7 && isTextureLoaded_pionek && isTextureLoaded_pionek2;
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

void BitmapHandler::drawPionekGeneric(float x, float y, float width, float height, GLuint texture) {
    const float MAX_X = 750.0f;
    const float MAX_Y = 550.0f;
    const float MIN_X = 0.0f;
    const float MIN_Y = 0.0f;

    if (x < MIN_X) x = MIN_X;
    if (x > MAX_X) x = MAX_X;
    if (y < MIN_Y) y = MIN_Y;
    if (y > MAX_Y) y = MAX_Y;

    if (width + x > MAX_X) width = MAX_X - x;
    if (height + y > MAX_Y) height = MAX_Y - y;

    if (!texture) {
        std::cerr << "Texture not loaded!" << std::endl;
        return;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y + height);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y + height);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glDisable(GL_BLEND);
}

void BitmapHandler::drawPionek(float x, float y, float width, float height) {
    drawPionekGeneric(x, y, width, height, texture_pionek);
}

void BitmapHandler::drawPionek2(float x, float y, float width, float height) {
    drawPionekGeneric(x, y, width, height, texture_pionek2);
}

