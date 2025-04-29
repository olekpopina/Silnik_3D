#include "Player.h"
#include <iostream>

Player::Player(Triangle* triangle, Cube* cube, PrimitiveDrawer* drawer)
    : triangle(triangle), cube(cube), drawer(drawer), isRotating(false) {
    isRotatingCube = false;
}
Light& Player::getLight() {
    return light;
}

/**
 * @brief Obsługuje wejście od użytkownika (naciśnięcie klawisza).
 *
 * Reaguje na różne klawisze, zmieniając stan gracza, np. rotację, ruch czy skalowanie figur.
 *
 * @param key Kod naciśniętego klawisza.
 */
void Player::handleInput(unsigned char key) {
    if (key == 'i' || key == 'I') {
        isRotating = !isRotating;
        triangle->setRotation(isRotating);
        std::cout << key;
    }
    else if (key == 'w' || key == 'W') {
        triangle->move(0.0f, 0.1f);
    }
    else if (key == 's' || key == 'S') {
        triangle->move(0.0f, -0.1f);
    }
    else if (key == 'a' || key == 'A') {
        triangle->move(-0.1f, 0.0f);
    }
    else if (key == 'd' || key == 'D') {
        triangle->move(0.1f, 0.0f);
    }
    else if (key == '+') {
        cube->scale(1.1f);
    }
    else if (key == '-') {
        cube->scale(0.9f);
    }
    else if (key == 'm') {
        triangle->scale(1.1f);
    }
    else if (key == 'n') {
        triangle->scale(0.9f);
    }
    else if (key == 'U') {
        cube->move(0.0f, 0.1f);
    }
    else if (key == 'C') {
        cube->move(0.0f, -0.1f);
    }
    else if (key == 'L') {
        cube->move(-0.1f, 0.0f);
    }
    else if (key == 'R') {
        cube->move(0.1f, 0.0f);
    }
    else if (key == 'q') {
        isRotatingCube = !isRotatingCube;
        cube->setRotationC(isRotatingCube);
        std::cout << key;
    }
    else if (key == 'O' || key == 'o') {
        light.switchLightingMode();
        std::cout << key;
    }
}

/**
 * @brief Aktualizuje stan gracza na podstawie upływu czasu.
 *
 * Aktualizuje rotację obiektów (trójkąta i sześcianu) na podstawie czasu, który upłynął od ostatniej klatki.
 *
 * @param deltaTime Czas, który upłynął od ostatniej klatki (w sekundach).
 */
void Player::update(float deltaTime) {
    // Aktualizuj rotację trójkąta
    triangle->updateRotation(deltaTime);

    // Aktualizuj rotację sześcianu
    cube->updateRotationC(deltaTime);
}
void Player::configureLighting() {
    light.configureLighting();
}
