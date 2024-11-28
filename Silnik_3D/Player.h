#ifndef PLAYER_H
#define PLAYER_H

#include "Triangle.h"

class Player {
public:
    Player(Triangle* triangle);

    void handleInput(unsigned char key);
    void update(float deltaTime);

private:
    Triangle* triangle;
    bool isRotating;
};

#endif // PLAYER_H
