#include "BitmapHandler.h"

// Konstruktor - inicjalizuje wszystkie tekstury jako niezainicjalizowane (0)
/**
 * @brief Konstruktor klasy BitmapHandler.
 * Inicjalizuje wszystkie tekstury jako niezainicjalizowane.
 */
BitmapHandler::BitmapHandler() {}

// Destruktor - usuwa wszystkie załadowane tekstury
/**
 * @brief Destruktor klasy BitmapHandler.
 * Usuwa wszystkie załadowane tekstury, zwalniając zasoby.
 */
BitmapHandler::~BitmapHandler() {
    deleteTexture(textureBackground);
    deleteTexture(texture1);
    deleteTexture(texture2);
    deleteTexture(texture3);
    deleteTexture(texture4);
    deleteTexture(texture5);
    deleteTexture(texture6);
    deleteTexture(texture_pionek);
    deleteTexture(texture_pionek2);
}

// Funkcja ładująca jedną teksturę z podanej ścieżki
/**
 * @brief Ładuje pojedynczą teksturę z pliku.
 *
 * @param filePath Ścieżka do pliku tekstury.
 * @return GLuint Identyfikator załadowanej tekstury.
 *
 * Funkcja ładuje teksturę z podanej ścieżki, generuje identyfikator tekstury
 * w OpenGL, a następnie ładuje obrazek do tej tekstury.
 */
GLuint BitmapHandler::loadSingleTexture(const std::string& filePath) {
    sf::Image image;
    if (!image.loadFromFile(filePath)) {
        std::cerr << "Nie można załadować tekstury: " << filePath << std::endl;
        return 0;
    }

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0); // Odłącz teksturę po załadowaniu
    return textureId;
}

// Funkcja ładująca wszystkie tekstury z listy ścieżek
/**
 * @brief Ładuje tekstury z listy ścieżek.
 *
 * @param texturePaths Lista ścieżek do plików z teksturami.
 * @return true Jeśli wszystkie tekstury zostały pomyślnie załadowane.
 * @return false Jeśli przynajmniej jedna tekstura nie została załadowana.
 *
 * Funkcja ładuje wszystkie tekstury z listy ścieżek i przypisuje je
 * do odpowiednich zmiennych. Jeśli nie uda się załadować którejkolwiek tekstury,
 * zwróci false.
 */
bool BitmapHandler::loadTextures(const std::vector<std::string>& texturePaths) {
    std::vector<GLuint*> textures = {
        &textureBackground, &texture1, &texture2, &texture3, &texture4, &texture5, &texture6, &texture_pionek, &texture_pionek2
    };

    if (texturePaths.size() != textures.size()) {
        std::cerr << "Niepoprawna liczba ścieżek do tekstur!" << std::endl;
        return false;
    }

    bool allLoaded = true;
    for (size_t i = 0; i < texturePaths.size(); ++i) {
        *textures[i] = loadSingleTexture(texturePaths[i]);
        if (!glIsTexture(*textures[i])) { // Sprawdź, czy tekstura została poprawnie załadowana
            std::cerr << "Nie udało się załadować tekstury: " << texturePaths[i] << std::endl;
            allLoaded = false;
        }
    }
    return allLoaded;
}

// Usuwa teksturę, jeśli jest załadowana
/**
 * @brief Usuwa teksturę, jeśli jest załadowana.
 *
 * @param texture Referencja do identyfikatora tekstury do usunięcia.
 *
 * Funkcja sprawdza, czy tekstura jest załadowana, a następnie usuwa ją,
 * zwalniając zasoby.
 */
void BitmapHandler::deleteTexture(GLuint& texture) {
    if (glIsTexture(texture)) { // Sprawdź, czy tekstura jest załadowana
        glDeleteTextures(1, &texture);
        texture = 0;
    }
}

// Funkcja przypisująca teksturę do ściany kostki
/**
 * @brief Przypisuje teksturę do jednej ściany kostki.
 *
 * @param faceIndex Indeks ściany kostki (0-5).
 *
 * Funkcja przypisuje odpowiednią teksturę do danej ściany kostki na podstawie
 * indeksu. Sprawdza również, czy tekstura jest załadowana.
 */
void BitmapHandler::bindCubeTexture(int faceIndex) {
    std::vector<GLuint> cubeTextures = { texture1, texture2, texture3, texture4, texture5, texture6 };

    if (faceIndex >= 0 && faceIndex < cubeTextures.size() && glIsTexture(cubeTextures[faceIndex])) {
        glBindTexture(GL_TEXTURE_2D, cubeTextures[faceIndex]);
    }
    else {
        std::cerr << "Nieprawidłowy indeks tekstury lub tekstura niezaładowana!" << std::endl;
    }
}

// Rysowanie tła w widoku 3D
/**
 * @brief Rysuje tło w widoku 3D.
 *
 * Funkcja rysuje tło za pomocą załadowanej tekstury. Ustawia widok 3D,
 * wyłącza test głębokości oraz rysuje prostokąt z teksturą tła.
 */
void BitmapHandler::drawBackground() {
    if (!glIsTexture(textureBackground)) return; // Sprawdź, czy tekstura jest załadowana

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0); // Ustaw układ współrzędnych dla widoku 2D

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); // Wyłącz test głębokości
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureBackground);

    glBegin(GL_QUADS); // Rysowanie prostokąta z teksturą
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 1.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0); // Odłącz teksturę
    glEnable(GL_DEPTH_TEST); // Włącz test głębokości

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

// Rysowanie pionka z teksturą
/**
 * @brief Rysuje pionka w zadanej pozycji z teksturą.
 *
 * @param x Współrzędna X pozycji pionka.
 * @param y Współrzędna Y pozycji pionka.
 * @param width Szerokość pionka.
 * @param height Wysokość pionka.
 * @param texture Tekstura do przypisania do pionka.
 *
 * Funkcja rysuje pionka w określonym miejscu, wyłączając test głębokości i włączając
 * blending dla przezroczystości.
 */
void BitmapHandler::drawPionek(float x, float y, float width, float height, GLuint texture) {
    if (!glIsTexture(texture)) { // Sprawdź, czy tekstura jest załadowana
        std::cerr << "Tekstura niezaładowana!" << std::endl;
        return;
    }

    glEnable(GL_BLEND); // Włącz blending dla przezroczystości
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0); // Ustaw układ współrzędnych dla widoku 2D

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); // Wyłącz test głębokości
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS); // Rysowanie prostokąta z teksturą
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y + height);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y + height);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0); // Odłącz teksturę
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST); // Włącz test głębokości

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glDisable(GL_BLEND); // Wyłącz blending
}
