#pragma once

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(unsigned int width, unsigned int height);
    bool show(); // zwraca true, je�li u�ytkownik kliknie "Start gry"

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text startText;
    sf::RectangleShape startButton;

    void processEvents(bool& gameShouldStart);
    void render();
};
