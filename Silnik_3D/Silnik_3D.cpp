#include "Engine.h"
#include <SFML/Graphics.hpp>



int main(int argc, char** argv) {
    std::vector<std::string> texturePaths = {
    "images/tlo.png", "images/1.png", "images/2.png", "images/3.png",
    "images/4.png", "images/5.png", "images/6.png", "images/pionek2.png", "images/pionek.png"
    };
    int frameRate = 60;

    Engine gameEngine(800, 600, "Game Engine");

    Engine::setInstance(&gameEngine);
    
    BitmapHandler bitmapHandler;
    if (!bitmapHandler.loadTextures(texturePaths)) {
        std::cerr << "Nie udało się załadować tekstury tła!" << std::endl;
        return -1;
    }
    gameEngine.init(argc, argv);
    gameEngine.setClearColor(0.2f, 0.3f, 0.4f);
    gameEngine.setFrameRate(60);

    gameEngine.setTextures(texturePaths);

    BitmapHandler cubeBitmapHandler;
    if (!cubeBitmapHandler.loadTextures(texturePaths)) {
        std::cerr << "Nie udało się załadować tekstury dla sześcianu!" << std::endl;
        return -1;
    }
    gameEngine.setFrameRate(frameRate); // Bez ograniczeń
    gameEngine.run();

    return 0;
}

