#include "Engine.h"
#include <SFML/Graphics.hpp>



int main(int argc, char** argv) {
    Engine gameEngine(800, 600, "Game Engine");

    Engine::setInstance(&gameEngine);

    gameEngine.init(argc, argv);
    gameEngine.setClearColor(0.2f, 0.3f, 0.4f);
    gameEngine.setFrameRate(60);

    gameEngine.setBackgroundTexture("D:/Silnik_3D/images/tlo.png");

    gameEngine.run();

    gameEngine.cleanup();
    return 0;
}


