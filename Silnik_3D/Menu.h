#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @brief Klasa reprezentuj¹ca menu startowe gry Ludo (Chiñczyk).
 *
 * Klasa `Menu` odpowiada za wyœwietlenie okna startowego, pobranie nazw (nicków)
 * graczy oraz rozpoczêcie gry po klikniêciu przycisku „Start”.
 *
 * Umo¿liwia wpisanie nazw dla maksymalnie 4 graczy i przekazuje je dalej
 * do silnika gry (`Engine`). Obs³uguje te¿ proste okno dialogowe do wprowadzania tekstu.
 *
 * @note Klasa u¿ywa biblioteki SFML do obs³ugi okna, renderowania i zdarzeñ.
 */
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
    sf::RectangleShape dialogCommunicat;
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
