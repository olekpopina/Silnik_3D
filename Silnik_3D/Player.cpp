#include "Player.h"
#include <iostream>

Player::Player(Triangle* triangle, Cube* cube, PrimitiveDrawer* drawer) : triangle(triangle), cube(cube), drawer(drawer), isRotating(false) {
    isRotatingCube = false;
    currentShadingMode = FLAT;
}

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
}


void Player::update(float deltaTime) {

    triangle->updateRotation(deltaTime);

    cube->updateRotationC(deltaTime);

}
