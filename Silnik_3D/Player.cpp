#include "Player.h"

Player::Player(Triangle* triangle) : triangle(triangle), isRotating(false) {}

void Player::handleInput(unsigned char key) {
    if (key == 'i' || key == 'I') { // W³¹cz/wy³¹cz obrót
        isRotating = !isRotating;
        triangle->setRotation(isRotating);
    }
    else if (key == 'w' || key == 'W') { // Przesuniêcie w górê
        triangle->setPosition(triangle->getPositionX(), triangle->getPositionY() + 0.1f);
    }
    else if (key == 's' || key == 'S') { // Przesuniêcie w dó³
        triangle->setPosition(triangle->getPositionX(), triangle->getPositionY() - 0.1f);
    }
    else if (key == 'a' || key == 'A') { // Przesuniêcie w lewo
        triangle->setPosition(triangle->getPositionX() - 0.1f, triangle->getPositionY());
    }
    else if (key == 'd' || key == 'D') { // Przesuniêcie w prawo
        triangle->setPosition(triangle->getPositionX() + 0.1f, triangle->getPositionY());
    }
}

void Player::update(float deltaTime) {
    triangle->updateRotation(deltaTime);
}
