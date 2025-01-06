#include "Engine.h"
#include <SFML/Graphics.hpp>



int main(int argc, char** argv) {
    const std::string texture1Path = "D:/Silnik_3D/images/tlo.png";
    const std::string texture2Path = "D:/win10/tlo.png";

    Engine gameEngine(800, 600, "Game Engine");

    Engine::setInstance(&gameEngine);
    
    BitmapHandler bitmapHandler;
    if (!bitmapHandler.loadTextures(texture1Path, texture2Path)) {
        std::cerr << "Nie udało się załadować tekstury tła!" << std::endl;
        return -1;
    }
    gameEngine.init(argc, argv);
    gameEngine.setClearColor(0.2f, 0.3f, 0.4f);
    gameEngine.setFrameRate(60);

    gameEngine.setTextures(texture1Path, texture2Path);

    BitmapHandler cubeBitmapHandler;
    if (!cubeBitmapHandler.loadTextures(texture2Path, texture1Path)) {
        std::cerr << "Nie udało się załadować tekstury dla sześcianu!" << std::endl;
        return -1;
    }
    gameEngine.run();

    gameEngine.cleanup();
    return 0;
}

/*
#include <GL/freeglut.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

GLuint textureID;

// Funkcja do ładowania tekstury za pomocą SFML
bool loadTexture(const std::string& filePath, GLuint& textureID) {
    sf::Image image;
    if (!image.loadFromFile(filePath)) {
        std::cerr << "Nie udało się załadować tekstury: " << filePath << std::endl;
        return false;
    }

    // Odwrócenie obrazu w pionie (OpenGL oczekuje innego układu współrzędnych)
    image.flipVertically();

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

// Funkcja do rysowania sześcianu
void drawCube() {
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);

    // Przednia ściana
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

    // Tylna ściana
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);

    // Lewa ściana
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

    // Prawa ściana
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);

    // Górna ściana
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

    // Dolna ściana
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Ustawienie kamery
    gluLookAt(0.0, 0.0, 5.0,   // Pozycja kamery
        0.0, 0.0, 0.0,   // Punkt, na który patrzy
        0.0, 1.0, 0.0);  // Wektor "w górę"

    static float angle = 0.0f;
    angle += 0.2f;

    glRotatef(angle, 0.1f, 0.1f, 0.0f); // Obrót sześcianu
    drawCube();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Szescian z tekstura");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    if (!loadTexture("D:/win10/tlo.png", textureID)) {
        return -1;
    }

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);

    glutMainLoop();

    return 0;
}
*/