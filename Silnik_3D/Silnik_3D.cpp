#include "Engine.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>


int main(int argc, char** argv) {
    Menu menu(800, 600);

    if (!menu.show()) {
        return 0; // użytkownik zamknął menu bez kliknięcia "Start gry"
    }
       
    std::vector<std::string> texturePaths = {
        "images/tlo_chinczyk.png", "images/1.png", "images/2.png", "images/3.png",
        "images/4.png", "images/5.png", "images/6.png", "images/pionek1.png", "images/pionek2.png"
    };

    int frameRate = 60;
    Engine gameEngine(800, 600, "Game Engine", frameRate);
    Engine::setInstance(&gameEngine);
    gameEngine.setPlayerNicknames(menu.getNickname1(), menu.getNickname2());
    gameEngine.init(argc, argv);
    gameEngine.setClearColor(0.2f, 0.3f, 0.4f);
    gameEngine.setTextures(texturePaths);
    gameEngine.run();

    return 0;
}
