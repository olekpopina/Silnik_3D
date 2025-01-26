#include "BitmapHandler.h"

// Konstruktor - inicjalizuje wszystkie tekstury jako niezainicjalizowane (0)
/**
 * @brief Konstruktor klasy BitmapHandler.
 * Inicjalizuje wszystkie tekstury jako niezainicjalizowane.
 */
BitmapHandler::BitmapHandler() {}

// Destruktor - usuwa wszystkie za�adowane tekstury
/**
 * @brief Destruktor klasy BitmapHandler.
 * Usuwa wszystkie za�adowane tekstury, zwalniaj�c zasoby.
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

// Funkcja �aduj�ca jedn� tekstur� z podanej �cie�ki
/**
 * @brief �aduje pojedyncz� tekstur� z pliku.
 *
 * @param filePath �cie�ka do pliku tekstury.
 * @return GLuint Identyfikator za�adowanej tekstury.
 *
 * Funkcja �aduje tekstur� z podanej �cie�ki, generuje identyfikator tekstury
 * w OpenGL, a nast�pnie �aduje obrazek do tej tekstury.
 */
GLuint BitmapHandler::loadSingleTexture(const std::string& filePath) {
    sf::Image image;
    if (!image.loadFromFile(filePath)) {
        std::cerr << "Nie mo�na za�adowa� tekstury: " << filePath << std::endl;
        return 0;
    }

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0); // Od��cz tekstur� po za�adowaniu
    return textureId;
}

// Funkcja �aduj�ca wszystkie tekstury z listy �cie�ek
/**
 * @brief �aduje tekstury z listy �cie�ek.
 *
 * @param texturePaths Lista �cie�ek do plik�w z teksturami.
 * @return true Je�li wszystkie tekstury zosta�y pomy�lnie za�adowane.
 * @return false Je�li przynajmniej jedna tekstura nie zosta�a za�adowana.
 *
 * Funkcja �aduje wszystkie tekstury z listy �cie�ek i przypisuje je
 * do odpowiednich zmiennych. Je�li nie uda si� za�adowa� kt�rejkolwiek tekstury,
 * zwr�ci false.
 */
bool BitmapHandler::loadTextures(const std::vector<std::string>& texturePaths) {
    std::vector<GLuint*> textures = {
        &textureBackground, &texture1, &texture2, &texture3, &texture4, &texture5, &texture6, &texture_pionek, &texture_pionek2
    };

    if (texturePaths.size() != textures.size()) {
        std::cerr << "Niepoprawna liczba �cie�ek do tekstur!" << std::endl;
        return false;
    }

    bool allLoaded = true;
    for (size_t i = 0; i < texturePaths.size(); ++i) {
        *textures[i] = loadSingleTexture(texturePaths[i]);
        if (!glIsTexture(*textures[i])) { // Sprawd�, czy tekstura zosta�a poprawnie za�adowana
            std::cerr << "Nie uda�o si� za�adowa� tekstury: " << texturePaths[i] << std::endl;
            allLoaded = false;
        }
    }
    return allLoaded;
}

// Usuwa tekstur�, je�li jest za�adowana
/**
 * @brief Usuwa tekstur�, je�li jest za�adowana.
 *
 * @param texture Referencja do identyfikatora tekstury do usuni�cia.
 *
 * Funkcja sprawdza, czy tekstura jest za�adowana, a nast�pnie usuwa j�,
 * zwalniaj�c zasoby.
 */
void BitmapHandler::deleteTexture(GLuint& texture) {
    if (glIsTexture(texture)) { // Sprawd�, czy tekstura jest za�adowana
        glDeleteTextures(1, &texture);
        texture = 0;
    }
}

// Funkcja przypisuj�ca tekstur� do �ciany kostki
/**
 * @brief Przypisuje tekstur� do jednej �ciany kostki.
 *
 * @param faceIndex Indeks �ciany kostki (0-5).
 *
 * Funkcja przypisuje odpowiedni� tekstur� do danej �ciany kostki na podstawie
 * indeksu. Sprawdza r�wnie�, czy tekstura jest za�adowana.
 */
void BitmapHandler::bindCubeTexture(int faceIndex) {
    std::vector<GLuint> cubeTextures = { texture1, texture2, texture3, texture4, texture5, texture6 };

    if (faceIndex >= 0 && faceIndex < cubeTextures.size() && glIsTexture(cubeTextures[faceIndex])) {
        glBindTexture(GL_TEXTURE_2D, cubeTextures[faceIndex]);
    }
    else {
        std::cerr << "Nieprawid�owy indeks tekstury lub tekstura nieza�adowana!" << std::endl;
    }
}

// Rysowanie t�a w widoku 3D
/**
 * @brief Rysuje t�o w widoku 3D.
 *
 * Funkcja rysuje t�o za pomoc� za�adowanej tekstury. Ustawia widok 3D,
 * wy��cza test g��boko�ci oraz rysuje prostok�t z tekstur� t�a.
 */
void BitmapHandler::drawBackground() {
    if (!glIsTexture(textureBackground)) return; // Sprawd�, czy tekstura jest za�adowana

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0); // Ustaw uk�ad wsp�rz�dnych dla widoku 2D

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); // Wy��cz test g��boko�ci
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureBackground);

    glBegin(GL_QUADS); // Rysowanie prostok�ta z tekstur�
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 1.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0); // Od��cz tekstur�
    glEnable(GL_DEPTH_TEST); // W��cz test g��boko�ci

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

// Rysowanie pionka z tekstur�
/**
 * @brief Rysuje pionka w zadanej pozycji z tekstur�.
 *
 * @param x Wsp�rz�dna X pozycji pionka.
 * @param y Wsp�rz�dna Y pozycji pionka.
 * @param width Szeroko�� pionka.
 * @param height Wysoko�� pionka.
 * @param texture Tekstura do przypisania do pionka.
 *
 * Funkcja rysuje pionka w okre�lonym miejscu, wy��czaj�c test g��boko�ci i w��czaj�c
 * blending dla przezroczysto�ci.
 */
void BitmapHandler::drawPionek(float x, float y, float width, float height, GLuint texture) {
    if (!glIsTexture(texture)) { // Sprawd�, czy tekstura jest za�adowana
        std::cerr << "Tekstura nieza�adowana!" << std::endl;
        return;
    }

    glEnable(GL_BLEND); // W��cz blending dla przezroczysto�ci
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0); // Ustaw uk�ad wsp�rz�dnych dla widoku 2D

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); // Wy��cz test g��boko�ci
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS); // Rysowanie prostok�ta z tekstur�
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y + height);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y + height);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0); // Od��cz tekstur�
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST); // W��cz test g��boko�ci

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glDisable(GL_BLEND); // Wy��cz blending
}
