#include "BitmapHandler.h"

// Konstruktor - inicjalizuje wszystkie tekstury jako niezainicjalizowane (0)
BitmapHandler::BitmapHandler()
    : texture1(0), texture2(0), texture3(0), texture4(0), texture5(0), texture6(0), texture7(0),
    texture_pionek(0), texture_pionek2(0) {}

// Destruktor - usuwa wszystkie za³adowane tekstury
BitmapHandler::~BitmapHandler() {
    deleteTexture(texture1);
    deleteTexture(texture2);
    deleteTexture(texture3);
    deleteTexture(texture4);
    deleteTexture(texture5);
    deleteTexture(texture6);
    deleteTexture(texture7);
    deleteTexture(texture_pionek);
    deleteTexture(texture_pionek2);
}

// Funkcja ³aduj¹ca jedn¹ teksturê z podanej œcie¿ki
GLuint BitmapHandler::loadSingleTexture(const std::string& filePath) {
    sf::Image image;
    if (!image.loadFromFile(filePath)) {
        std::cerr << "Nie mo¿na za³adowaæ tekstury: " << filePath << std::endl;
        return 0;
    }

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0); // Od³¹cz teksturê po za³adowaniu
    return textureId;
}

// Funkcja ³aduj¹ca wszystkie tekstury z listy œcie¿ek
bool BitmapHandler::loadTextures(const std::vector<std::string>& texturePaths) {
    std::vector<GLuint*> textures = {
        &texture1, &texture2, &texture3, &texture4, &texture5, &texture6, &texture7, &texture_pionek, &texture_pionek2
    };

    if (texturePaths.size() != textures.size()) {
        std::cerr << "Niepoprawna liczba œcie¿ek do tekstur!" << std::endl;
        return false;
    }

    bool allLoaded = true;
    for (size_t i = 0; i < texturePaths.size(); ++i) {
        *textures[i] = loadSingleTexture(texturePaths[i]);
        if (!glIsTexture(*textures[i])) { // SprawdŸ, czy tekstura zosta³a poprawnie za³adowana
            std::cerr << "Nie uda³o siê za³adowaæ tekstury: " << texturePaths[i] << std::endl;
            allLoaded = false;
        }
    }
    return allLoaded;
}

// Usuwa teksturê, jeœli jest za³adowana
void BitmapHandler::deleteTexture(GLuint& texture) {
    if (glIsTexture(texture)) { // SprawdŸ, czy tekstura jest za³adowana
        glDeleteTextures(1, &texture);
        texture = 0;
    }
}

// Funkcja przypisuj¹ca teksturê do œciany kostki
void BitmapHandler::bindCubeTexture(int faceIndex) {
    std::vector<GLuint> cubeTextures = { texture2, texture3, texture4, texture5, texture6, texture7 };

    if (faceIndex >= 0 && faceIndex < cubeTextures.size() && glIsTexture(cubeTextures[faceIndex])) {
        glBindTexture(GL_TEXTURE_2D, cubeTextures[faceIndex]);
    }
    else {
        std::cerr << "Nieprawid³owy indeks tekstury lub tekstura nieza³adowana!" << std::endl;
    }
}

// Rysowanie t³a w widoku 2D
void BitmapHandler::drawBackground() {
    if (!glIsTexture(texture1)) return; // SprawdŸ, czy tekstura jest za³adowana

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0); // Ustaw uk³ad wspó³rzêdnych dla widoku 2D

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); // Wy³¹cz test g³êbokoœci
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glBegin(GL_QUADS); // Rysowanie prostok¹ta z tekstur¹
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 1.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0); // Od³¹cz teksturê
    glEnable(GL_DEPTH_TEST); // W³¹cz test g³êbokoœci

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

// Rysowanie pionka z tekstur¹
void BitmapHandler::drawPionek(float x, float y, float width, float height, GLuint texture) {
    if (!glIsTexture(texture)) { // SprawdŸ, czy tekstura jest za³adowana
        std::cerr << "Tekstura nieza³adowana!" << std::endl;
        return;
    }

    glEnable(GL_BLEND); // W³¹cz blending dla przezroczystoœci
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0); // Ustaw uk³ad wspó³rzêdnych dla widoku 2D

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); // Wy³¹cz test g³êbokoœci
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS); // Rysowanie prostok¹ta z tekstur¹
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y + height);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y + height);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0); // Od³¹cz teksturê
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST); // W³¹cz test g³êbokoœci

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glDisable(GL_BLEND); // Wy³¹cz blending
}
