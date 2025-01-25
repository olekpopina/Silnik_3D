#include "Player.h"
#include <iostream>

Player::Player(Triangle* triangle, Cube* cube, PrimitiveDrawer* drawer) : triangle(triangle), cube(cube), drawer(drawer), isRotating(false) {}

void Player::handleInput(unsigned char key) {
    if (key == 'i' || key == 'I') { 
        isRotating = !isRotating;
        triangle->setRotation(isRotating);
        std::cout << key;
    }
    else if (key == 'w' || key == 'W') { 
        triangle->setPosition(triangle->getPositionX(), triangle->getPositionY() + 0.1f);
    }
    else if (key == 's' || key == 'S') {
        triangle->setPosition(triangle->getPositionX(), triangle->getPositionY() - 0.1f);
    }
    else if (key == 'a' || key == 'A') { 
        triangle->setPosition(triangle->getPositionX() - 0.1f, triangle->getPositionY());
    }
    else if (key == 'd' || key == 'D') { 
        triangle->setPosition(triangle->getPositionX() + 0.1f, triangle->getPositionY());
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
    if (key == 'f') {
        drawer->setShadingMode(PrimitiveDrawer::FLAT);  
    }
    else if (key == 'g') {
        drawer->setShadingMode(PrimitiveDrawer::GOURAUD);  
    }
    else if (key == 'p') {
        drawer->setShadingMode(PrimitiveDrawer::PHONG);  
        currentShadingMode = PHONG;
        std::cout << key;
    }
    else if (key == 'q') { 
        isRotatingCube = !isRotatingCube;
        cube->setRotationC(isRotatingCube); 
        std::cout << key;
    }
}


void Player::update(float deltaTime) {

    triangle->updateRotation(deltaTime);

    cube->updateRotationC(deltaTime);

    if (currentShadingMode == FLAT) {

        cube->setShadingMode(PrimitiveDrawer::FLAT);
    }
    else if (currentShadingMode == GOURAUD) {

        cube->setShadingMode(PrimitiveDrawer::GOURAUD);
    }
    else if (currentShadingMode == PHONG) {

        cube->setShadingMode(PrimitiveDrawer::PHONG);
        currentShadingMode = PHONG; 
    }
}
