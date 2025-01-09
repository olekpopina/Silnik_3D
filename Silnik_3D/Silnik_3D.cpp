#include "Engine.h"
#include <SFML/Graphics.hpp>



int main(int argc, char** argv) {
    const std::string texture1Path = "D:/Silnik_3D/images/tlowin.png";
    const std::string texture2Path = "D:/Silnik_3D/images/1.png";
    const std::string texture3Path = "D:/Silnik_3D/images/2.png";
    const std::string texture4Path = "D:/Silnik_3D/images/3.png";
    const std::string texture5Path = "D:/Silnik_3D/images/4.png";
    const std::string texture6Path = "D:/Silnik_3D/images/5.png";
    const std::string texture7Path = "D:/Silnik_3D/images/6.png";
    const std::string texture_pionek = "D:/Silnik_3D/images/pionek.png";

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

