#ifndef PLAYER_H
#define PLAYER_H

#include "Triangle.h"
#include "Cube.h"

class Player {
public:
    Player(Triangle* triangle, Cube* cube);

    void handleInput(unsigned char key);
    void update(float deltaTime);

private:
    Triangle* triangle;
    Cube* cube;
    bool isRotating;
};

#endif // PLAYER_H
