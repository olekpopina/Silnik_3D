#include "Player.h"

Player::Player(Triangle* triangle, Cube* cube) : triangle(triangle), cube(cube), isRotating(false) {}

void Player::handleInput(unsigned char key) {
    if (key == 'i' || key == 'I') { // W��cz/wy��cz obr�t
        isRotating = !isRotating;
        triangle->setRotation(isRotating);
    }
    else if (key == 'w' || key == 'W') { // Przesuni�cie w g�r�
        triangle->setPosition(triangle->getPositionX(), triangle->getPositionY() + 0.1f);
    }
    else if (key == 's' || key == 'S') { // Przesuni�cie w d�
        triangle->setPosition(triangle->getPositionX(), triangle->getPositionY() - 0.1f);
    }
    else if (key == 'a' || key == 'A') { // Przesuni�cie w lewo
        triangle->setPosition(triangle->getPositionX() - 0.1f, triangle->getPositionY());
    }
    else if (key == 'd' || key == 'D') { // Przesuni�cie w prawo
        triangle->setPosition(triangle->getPositionX() + 0.1f, triangle->getPositionY());
    }
    else if (key == '+') {  // Powi�kszenie sze�cio�cianu
        cube->scaleUp();
    }
    else if (key == '-') {  // Zmniejszenie sze�cio�cianu
        cube->scaleDown();
    }
}

void Player::update(float deltaTime) {
    triangle->updateRotation(deltaTime);
}
