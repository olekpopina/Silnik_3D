#include "Engine.h"
#include <SFML/Graphics.hpp>



int main(int argc, char** argv) {
    const std::string texture1Path = "images/tlowin.png";
    const std::string texture2Path = "images/1.png";
    const std::string texture3Path = "images/2.png";
    const std::string texture4Path = "images/3.png";
    const std::string texture5Path = "images/4.png";
    const std::string texture6Path = "images/5.png";
    const std::string texture7Path = "images/6.png";
    const std::string texture_pionek = "images/pionek.png";

    Engine gameEngine(800, 600, "Game Engine");

    Engine::setInstance(&gameEngine);
    
    BitmapHandler bitmapHandler;
    if (!bitmapHandler.loadTextures(texture1Path, texture2Path, texture3Path, texture4Path, texture5Path, texture6Path, texture7Path, texture_pionek)) {
        std::cerr << "Nie udało się załadować tekstury tła!" << std::endl;
        return -1;
    }
    gameEngine.init(argc, argv);
    gameEngine.setClearColor(0.2f, 0.3f, 0.4f);
    gameEngine.setFrameRate(60);

    gameEngine.setTextures(texture1Path, texture2Path, texture3Path, texture4Path, texture5Path, texture6Path, texture7Path, texture_pionek);

    BitmapHandler cubeBitmapHandler;
    if (!cubeBitmapHandler.loadTextures(texture2Path, texture3Path, texture4Path, texture5Path, texture6Path, texture7Path, texture1Path, texture_pionek)) {
        std::cerr << "Nie udało się załadować tekstury dla sześcianu!" << std::endl;
        return -1;
    }
    gameEngine.run();

   //gameEngine.cleanup();
    return 0;
}

