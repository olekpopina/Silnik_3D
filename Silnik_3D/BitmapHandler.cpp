#include "BitmapHandler.h"

BitmapHandler::BitmapHandler()
    : texture1(0), texture2(0), texture3(0), texture4(0), texture5(0), texture6(0), texture7(0),
    texture_pionek(0), texture_pionek2(0),
    isTextureLoaded_1(false), isTextureLoaded_2(false), isTextureLoaded_3(false),
    isTextureLoaded_4(false), isTextureLoaded_5(false), isTextureLoaded_6(false),
    isTextureLoaded_7(false), isTextureLoaded_pionek(false), isTextureLoaded_pionek2(false) {}

BitmapHandler::~BitmapHandler() {
    deleteTexture(texture1, isTextureLoaded_1);
    deleteTexture(texture2, isTextureLoaded_2);
    deleteTexture(texture3, isTextureLoaded_3);
    deleteTexture(texture4, isTextureLoaded_4);
    deleteTexture(texture5, isTextureLoaded_5);
    deleteTexture(texture6, isTextureLoaded_6);
    deleteTexture(texture7, isTextureLoaded_7);
    deleteTexture(texture_pionek, isTextureLoaded_pionek);
    deleteTexture(texture_pionek2, isTextureLoaded_pionek2);
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

bool BitmapHandler::loadTextures(const std::vector<std::string>& texturePaths) {
    std::vector<GLuint*> textures = {
        &texture1, &texture2, &texture3, &texture4, &texture5, &texture6, &texture7, &texture_pionek, &texture_pionek2
    };

    if (texturePaths.size() != textures.size()) {
        std::cerr << "B³êdna liczba œcie¿ek do tekstur!" << std::endl;
        return false;
    }

    bool allLoaded = true;
    for (size_t i = 0; i < texturePaths.size(); ++i) {
        *textures[i] = loadSingleTexture(texturePaths[i]);
        bool isLoaded = (*textures[i] != 0);
        if (!isLoaded) {
            std::cerr << "Nie uda³o siê za³adowaæ tekstury: " << texturePaths[i] << std::endl;
            allLoaded = false;
        }
    }
    return allLoaded;
}

void BitmapHandler::deleteTexture(GLuint& texture, bool& isLoaded) {
    if (isLoaded) {
        glDeleteTextures(1, &texture);
        isLoaded = false;
    }
}

bool BitmapHandler::isTextureLoaded(GLuint texture) {
    return glIsTexture(texture) == GL_TRUE;
}

void BitmapHandler::bindCubeTexture(int faceIndex) {
    std::vector<GLuint> cubeTextures = { texture2, texture3, texture4, texture5, texture6, texture7 };

    if (faceIndex >= 0 && faceIndex < cubeTextures.size() && isTextureLoaded(cubeTextures[faceIndex])) {
        glBindTexture(GL_TEXTURE_2D, cubeTextures[faceIndex]);
    }
    else {
        std::cerr << "Nieprawid³owy indeks tekstury lub tekstura nieza³adowana!" << std::endl;
    }
}

void BitmapHandler::drawBackground() {
    if (!isTextureLoaded(texture1)) return;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 1.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void BitmapHandler::drawPionek(float x, float y, float width, float height, GLuint texture) {
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
        std::cerr << "Tekstura nieza³adowana!" << std::endl;
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
