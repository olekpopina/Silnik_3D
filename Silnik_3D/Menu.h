#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
public:
    Menu(unsigned int width, unsigned int height);
    bool show(); 
    std::string getNickname1() const { return nickname1; }
    std::string getNickname2() const { return nickname2; }
    std::string getNickname3() const { return nickname3; }
    std::string getNickname4() const { return nickname4; }

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text startText;
    sf::RectangleShape startButton;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::RectangleShape loginButton1;
    sf::RectangleShape loginButton2;
    sf::RectangleShape loginButton3;
    sf::RectangleShape loginButton4;
    sf::Text loginText1;
    sf::Text loginText2;

    bool enteringName1 = false;
    bool enteringName2 = false;
    bool enteringName3 = false;
    bool enteringName4 = false;
    sf::Text inputText1;
    sf::Text inputText2;
    std::string nickname1;
    std::string nickname2;
    std::string nickname3;
    std::string nickname4;

    bool showDialog = false;
    int activeDialogPlayer = 0; // 1 = gracz 1, 2 = gracz 2
    sf::RectangleShape dialogBox;
    sf::Text dialogPrompt;
    sf::RectangleShape dialogOkButton;
    sf::Text dialogOkText;
    sf::Text dialogInputText;
    std::string dialogInput;
    sf::Text errorText;
    bool showError = false;


    void processEvents(bool& gameShouldStart);
    void render();
};
