#include "Player.h"
#include <iostream>

Player::Player(Triangle* triangle, Cube* cube, PrimitiveDrawer* drawer) : triangle(triangle), cube(cube), drawer(drawer), isRotating(false) {}

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
    else if (key == '+') {  // Powiêkszenie szeœcioœcianu
        cube->scaleUp();
    }
    else if (key == '-') {  // Zmniejszenie szeœcioœcianu
        cube->scaleDown();
    }
    else if (key == 'm') {  // Powiêkszenie szeœcioœcianu
        triangle->scale_Up();
    }
    else if (key == 'n') {  // Zmniejszenie szeœcioœcianu
        triangle->scale_Down();
    }
 else if (key == 'U') { // Ruch w górê
     cube->move(0.0f, 0.1f);
    }
 else if (key == 'C') { // Ruch w dó³
     cube->move(0.0f, -0.1f);
    }
 else if (key == 'L') { // Ruch w lewo
     cube->move(-0.1f, 0.0f);
    }
 else if (key == 'R') { // Ruch w prawo
     cube->move(0.1f, 0.0f);
    }
    if (key == 'f') {
        drawer->setShadingMode(PrimitiveDrawer::FLAT);  // Zmieniamy tryb na FLAT
    }
    else if (key == 'g') {
        drawer->setShadingMode(PrimitiveDrawer::GOURAUD);  // Zmieniamy tryb na GOURAUD
    }
    else if (key == 'p') {
        drawer->setShadingMode(PrimitiveDrawer::PHONG);  // Zmieniamy tryb na PHONG
        currentShadingMode = PHONG;
        std::cout << key;
    }

}


void Player::update(float deltaTime) {
    triangle->updateRotation(deltaTime);
    if (currentShadingMode == FLAT) {
        // Jeœli tryb cieniowania to FLAT, mo¿emy np. zaktualizowaæ ustawienia œwiat³a itp.
        cube->setShadingMode(PrimitiveDrawer::FLAT);
    }
    else if (currentShadingMode == GOURAUD) {
        // Zaktualizuj tryb cieniowania na Gouraud
        cube->setShadingMode(PrimitiveDrawer::GOURAUD);
    }
    else if (currentShadingMode == PHONG) {
        // Zaktualizuj tryb cieniowania na Phong (przy u¿yciu shaderów)
        cube->setShadingMode(PrimitiveDrawer::PHONG);
        currentShadingMode = PHONG;  // Ustawienie PHONG
    }
}
