#include "Engine.h"
#include <SFML/Graphics.hpp>



int main(int argc, char** argv) {
    std::vector<std::string> texturePaths = {
    "images/tlo.png", "images/1.png", "images/2.png", "images/3.png",
    "images/4.png", "images/5.png", "images/6.png", "images/pionek2.png", "images/pionek1.png"
    };
    int frameRate = 60;

    Engine gameEngine(800, 600, "Game Engine", frameRate);

    Engine::setInstance(&gameEngine);
    
    gameEngine.init(argc, argv);
    gameEngine.setClearColor(0.2f, 0.3f, 0.4f);
    gameEngine.setTextures(texturePaths);
    gameEngine.run();

    return 0;
}

