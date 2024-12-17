#ifndef PLAYER_H
#define PLAYER_H

#include "Triangle.h"
#include "Cube.h"
#include "PrimitiveDrawer.h"


class Player {
public:
    Player(Triangle* triangle, Cube* cube, PrimitiveDrawer* drawer);

    void handleInput(unsigned char key);
    void update(float deltaTime);
    void move(float dx, float dy); 

private:
    Triangle* triangle;
    Cube* cube;
    PrimitiveDrawer* drawer;
    bool isRotating;
   
    bool isRotatingCube; 
    int currentShadingMode;
    enum ShadingMode {
        FLAT,
        GOURAUD,
        PHONG
    };
};

#endif // PLAYER_H
