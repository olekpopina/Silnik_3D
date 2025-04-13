#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
public:
    Menu(unsigned int width, unsigned int height);
    bool show(); 

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text startText;
    sf::RectangleShape startButton;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    void processEvents(bool& gameShouldStart);
    void render();
};
