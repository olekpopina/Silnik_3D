
#include "PrimitiveDrawer.h"
#include "Cube.h"
#include <memory>

ShadingMode PrimitiveDrawer::currentShadingMode = ShadingMode::SMOOTH;

GLuint PrimitiveDrawer::textures[6];
int PrimitiveDrawer::textureSet;

/**
 * Ustawia tryb cieniowania.
 *
 * @param mode Tryb cieniowania, który ma zostać ustawiony (SMOOTH lub FLAT).
 */
void PrimitiveDrawer::setShadingMode(ShadingMode mode) {
    currentShadingMode = mode;

    if (mode == ShadingMode::FLAT) {
        glShadeModel(GL_FLAT);
    }
    else {
        glShadeModel(GL_SMOOTH);
    }
}

/**
 * Rysuje punkt w przestrzeni 3D.
 *
 * @param x Współrzędna X punktu.
 * @param y Współrzędna Y punktu.
 * @param z Współrzędna Z punktu.
 * @param size Rozmiar punktu (domyślnie 1.0f).
 */
void PrimitiveDrawer::drawPoint(float x, float y, float z, float size) {
    glPointSize(size);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
}

/**
 * Rysuje linię między dwoma punktami w przestrzeni 3D.
 *
 * @param x1 Współrzędna X pierwszego punktu.
 * @param y1 Współrzędna Y pierwszego punktu.
 * @param z1 Współrzędna Z pierwszego punktu.
 * @param x2 Współrzędna X drugiego punktu.
 * @param y2 Współrzędna Y drugiego punktu.
 * @param z2 Współrzędna Z drugiego punktu.
 * @param width Szerokość linii (domyślnie 2.0f).
 */
void PrimitiveDrawer::drawLine(float x1, float y1, float z1, float x2, float y2, float z2, float width) {
    glLineWidth(width);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
}

/**
 * Rysuje trójkąt w przestrzeni 3D.
 *
 * @param vertices1 Tablica zawierająca wierzchołki pierwszego trójkąta.
 * @param vertices2 Tablica zawierająca wierzchołki drugiego trójkąta.
 * @param vertices3 Tablica zawierająca wierzchołki trzeciego trójkąta.
 * @param colors Tablica kolorów przypisanych do wierzchołków.
 * @param posX Przesunięcie wzdłuż osi X.
 * @param posY Przesunięcie wzdłuż osi Y.
 * @param scale Skalowanie trójkąta.
 * @param rotationAngle Kąt obrotu trójkąta.
 */
void PrimitiveDrawer::drawTriangle(const float vertices1[9], const float vertices2[9],
    const float vertices3[9], const float colors[9],
    float posX, float posY, float scale, float rotationAngle) {
    // Konfiguracja światła
    GLfloat lightPos[] = { 0.0f, 0.0f, 5.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spotDirection[] = { 0.0f, 0.0f, -1.0f };

    // Ustawienie parametrów światła za pomocą funkcji configureLight
    configureLight(GL_LIGHT0, lightPos, lightAmbient, lightDiffuse, lightSpecular, spotDirection, 25.0f, 15.0f);

    // Konfiguracja materiału
    GLfloat matAmbient[] = { 0.2f, 0.5f, 0.2f, 1.0f }; // Kolor otoczenia
    GLfloat matDiffuse[] = { 0.5f, 1.0f, 0.5f, 1.0f }; // Kolor rozproszony
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Kolor odbity
    GLfloat matShininess = 30.0f; // Połysk materiału

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

    // Transformacje: przesunięcie, obrót, skalowanie
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    glScalef(scale, scale, scale);

    // Normalne dla wierzchołków
    GLfloat normals[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    // Rysowanie trójkątów
    glVertexPointer(3, GL_FLOAT, 0, vertices1);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glVertexPointer(3, GL_FLOAT, 0, vertices2);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glVertexPointer(3, GL_FLOAT, 0, vertices3);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glPopMatrix();

    // Wyłączenie światła
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

/**
 * Konfiguruje światło w scenie.
 *
 * @param light Numer światła (np. GL_LIGHT0).
 * @param position Pozycja światła w przestrzeni 3D.
 * @param ambient Kolor otoczenia światła.
 * @param diffuse Kolor rozproszonego światła.
 * @param specular Kolor światła odbitego.
 * @param direction Kierunek światła spot (opcjonalny).
 * @param cutoff Kąt cięcia światła spot (opcjonalny).
 * @param exponent Współczynnik eksponenta dla światła spot (opcjonalny).
 */
void PrimitiveDrawer::configureLight(GLenum light, const GLfloat* position, const GLfloat* ambient, const GLfloat* diffuse, const GLfloat* specular, const GLfloat* direction, float cutoff, float exponent) {
    glEnable(GL_LIGHTING);
    glEnable(light);

    glLightfv(light, GL_POSITION, position);
    glLightfv(light, GL_AMBIENT, ambient);
    glLightfv(light, GL_DIFFUSE, diffuse);
    glLightfv(light, GL_SPECULAR, specular);

    if (direction) {
        glLightfv(light, GL_SPOT_DIRECTION, direction);
        glLightf(light, GL_SPOT_CUTOFF, cutoff);
        glLightf(light, GL_SPOT_EXPONENT, exponent);
    }
}

/**
 * Rysuje sześcian w przestrzeni 3D.
 *
 * @param scale Skalowanie sześcianu.
 * @param offsetX Przesunięcie wzdłuż osi X.
 * @param offsetY Przesunięcie wzdłuż osi Y.
 * @param vertices Tablica wierzchołków sześcianu.
 * @param indices Tablica indeksów wierzchołków.
 * @param normals Tablica normalnych wierzchołków.
 * @param colors Tablica kolorów przypisanych do wierzchołków.
 */
void PrimitiveDrawer::drawCube(float scale, float offsetX, float offsetY,
    const float* vertices, const unsigned int* indices,
    const float* normals, const float* colors) {
    // Konfiguracja światła
    GLfloat lightPos[] = { 1.0f, 1.0f, 5.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.0f, 0.0f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // Ustawienie parametrów światła za pomocą funkcji configureLight
    configureLight(GL_LIGHT0, lightPos, lightAmbient, lightDiffuse, lightSpecular);

    // Konfiguracja materiału
    GLfloat matAmbient[] = { 0.2f, 0.0f, 0.0f, 1.0f }; // Kolor otoczenia
    GLfloat matDiffuse[] = { 0.8f, 0.0f, 0.0f, 1.0f }; // Kolor rozproszony
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Kolor odbity
    GLfloat matShininess = 50.0f; // Połysk materiału

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

    // Transformacje: przesunięcie i skalowanie
    glPushMatrix();
    glTranslatef(offsetX, offsetY, 0.0f);
    glScalef(scale, scale, scale);

    // Włączenie tablic wierzchołków i normalnych
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);

    // Rysowanie elementów
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glPopMatrix();

    // Wyłączenie światła
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

/**
 * Rysuje sześcian z teksturą w przestrzeni 3D.
 *
 * Funkcja rysuje sześcian w przestrzeni 3D, przypisując odpowiednie tekstury do każdej z jego ścian.
 * Tekstury są wybierane na podstawie numeru zestawu, który jest określony przez zmienną `textureSet`.
 *
 * @param scale Skalowanie sześcianu.
 * @param offsetX Przesunięcie wzdłuż osi X.
 * @param offsetY Przesunięcie wzdłuż osi Y.
 * @param bitmapHandler Obiekt klasy `BitmapHandler` zawierający tekstury, które będą używane do renderowania sześcianu.
 */
void PrimitiveDrawer::drawCubeWithTexture(float scale, float offsetX, float offsetY, BitmapHandler& bitmapHandler) {
    glEnable(GL_TEXTURE_2D);


    switch (textureSet) {
    case 1: // Zestaw tekstur 1
        textures[0] = bitmapHandler.texture1; // Przednia
        textures[1] = bitmapHandler.texture2; // Tylna
        textures[2] = bitmapHandler.texture3; // Lewa
        textures[3] = bitmapHandler.texture4; // Prawa
        textures[4] = bitmapHandler.texture5; // Górna
        textures[5] = bitmapHandler.texture6; // Dolna
        break;
    case 2: // Zestaw tekstur 2
        textures[0] = bitmapHandler.texture2; // Przednia
        textures[1] = bitmapHandler.texture3; // Tylna
        textures[2] = bitmapHandler.texture4; // Lewa
        textures[3] = bitmapHandler.texture5; // Prawa
        textures[4] = bitmapHandler.texture6; // Górna
        textures[5] = bitmapHandler.texture1; // Dolna
        break;
    case 3: // Zestaw tekstur 2
        textures[0] = bitmapHandler.texture3; // Przednia
        textures[1] = bitmapHandler.texture2; // Tylna
        textures[2] = bitmapHandler.texture4; // Lewa
        textures[3] = bitmapHandler.texture5; // Prawa
        textures[4] = bitmapHandler.texture6; // Górna
        textures[5] = bitmapHandler.texture1; // Dolna
        break;
    case 4: // Zestaw tekstur 2
        textures[0] = bitmapHandler.texture4; // Przednia
        textures[1] = bitmapHandler.texture3; // Tylna
        textures[2] = bitmapHandler.texture2; // Lewa
        textures[3] = bitmapHandler.texture5; // Prawa
        textures[4] = bitmapHandler.texture6; // Górna
        textures[5] = bitmapHandler.texture1; // Dolna
        break;
    case 5: // Zestaw tekstur 2
        textures[0] = bitmapHandler.texture5; // Przednia
        textures[1] = bitmapHandler.texture2; // Tylna
        textures[2] = bitmapHandler.texture4; // Lewa
        textures[3] = bitmapHandler.texture3; // Prawa
        textures[4] = bitmapHandler.texture6; // Górna
        textures[5] = bitmapHandler.texture1; // Dolna
        break;
    case 6: // Zestaw tekstur 2
        textures[0] = bitmapHandler.texture6; // Przednia
        textures[1] = bitmapHandler.texture2; // Tylna
        textures[2] = bitmapHandler.texture4; // Lewa
        textures[3] = bitmapHandler.texture5; // Prawa
        textures[4] = bitmapHandler.texture3; // Górna
        textures[5] = bitmapHandler.texture1; // Dolna
        break;
    default: // Domyślny zestaw tekstur
        textures[0] = bitmapHandler.texture1;
        textures[1] = bitmapHandler.texture2;
        textures[2] = bitmapHandler.texture3;
        textures[3] = bitmapHandler.texture4;
        textures[4] = bitmapHandler.texture5;
        textures[5] = bitmapHandler.texture6;
        break;
    }

    glPushMatrix();
    glTranslatef(offsetX, offsetY, 0.0f);
    glScalef(scale, scale, scale);
    // Przednia ściana
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glEnd();
   
    // Tylna ściana
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();

    // Lewa ściana
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();

    // Prawa ściana
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();

    // Górna ściana
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();

    // Dolna ściana
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

