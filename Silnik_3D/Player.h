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
    void move(float dx, float dy); // Deklaracja metody move

private:
    Triangle* triangle;
    Cube* cube;
    PrimitiveDrawer* drawer;
    bool isRotating;
    int currentShadingMode; // Dodajemy zmienn¹ przechowuj¹c¹ aktualny tryb cieniowania
    enum ShadingMode {
        FLAT,
        GOURAUD,
        PHONG
    };
};

#endif // PLAYER_H
