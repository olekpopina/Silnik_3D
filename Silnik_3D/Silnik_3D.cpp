
#include "Engine.h"
#include "Menu.h"
#include "Pawn3D.h"
#include <SFML/Graphics.hpp>

/**
 * @brief Punkt wejścia do gry Chińczyk 3D z menu, pionkami 3D i silnikiem gry.
 */
int main(int argc, char** argv) {
    Menu menu(600, 600);
    Pawn3D pawn3D;

    if (!menu.show()) {
        return 0; // użytkownik zamknął menu bez kliknięcia "Start gry"
    }
       
    std::vector<std::string> texturePaths = {
        "images/tlo_chinczyk.png", "images/1.png", "images/2.png", "images/3.png",
        "images/4.png", "images/5.png", "images/6.png", "images/pionek1.png", "images/pionek2.png"
    };

    int frameRate = 60;
    Engine gameEngine(800, 600, "Gra Chinczyk", frameRate);
    Engine::setInstance(&gameEngine);
    gameEngine.setPlayerNicknames(menu.getNickname1(), menu.getNickname2(), menu.getNickname3(), menu.getNickname4());
    gameEngine.init(argc, argv);
    gameEngine.setClearColor(0.2f, 0.3f, 0.4f);
    gameEngine.setTextures(texturePaths);
    gameEngine.run();

    return 0;
}