#include "Menu.h"

Menu::Menu(unsigned int width, unsigned int height)
    : window(sf::VideoMode(width, height), "Menu") {
    font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

    if (!backgroundTexture.loadFromFile("images/tlo_menu.png")) {
   
        std::cerr << "Nie udalo sie zaladowac tla menu!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);
    /*
    startText.setFont(font);
    startText.setString("Start gry");
    startText.setCharacterSize(40);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(300, 190);
    */
    startButton.setSize(sf::Vector2f(300, 50));
    startButton.setPosition(150, 150);
    startButton.setFillColor(sf::Color(0, 0, 0, 0));//przezroczysty kolor 

    loginButton1.setSize(sf::Vector2f(300, 70));
    loginButton1.setPosition(150, 210);
    loginButton1.setFillColor(sf::Color(0, 0, 0, 0));
    /*
    loginText1.setFont(font);
    loginText1.setString("Zaloguj sie Gracz 1");
    loginText1.setCharacterSize(24);
    loginText1.setFillColor(sf::Color::Black);
    loginText1.setPosition(275, 355);
    */
    loginButton2.setSize(sf::Vector2f(300, 70));
    loginButton2.setPosition(150, 300);
    loginButton2.setFillColor(sf::Color(0, 0, 0, 0));
    /*
    loginText2.setFont(font);
    loginText2.setString("Zaloguj sie Gracz 2");
    loginText2.setCharacterSize(24);
    loginText2.setFillColor(sf::Color::Black);
    loginText2.setPosition(275, 425);
    */
    dialogBox.setSize(sf::Vector2f(400, 200));
    dialogBox.setFillColor(sf::Color(50, 50, 50, 230));
    dialogBox.setOutlineColor(sf::Color::White);
    dialogBox.setOutlineThickness(3);
    dialogBox.setPosition(100, 200);

    dialogPrompt.setFont(font);
    dialogPrompt.setString("Wpisz nick:");
    dialogPrompt.setCharacterSize(24);
    dialogPrompt.setFillColor(sf::Color::White);
    dialogPrompt.setPosition(120, 220);

    dialogInputText.setFont(font);
    dialogInputText.setCharacterSize(20);
    dialogInputText.setFillColor(sf::Color::Yellow);
    dialogInputText.setPosition(120, 270);

    dialogOkButton.setSize(sf::Vector2f(80, 40));
    dialogOkButton.setFillColor(sf::Color::Green);
    dialogOkButton.setPosition(400, 320);

    dialogOkText.setFont(font);
    dialogOkText.setString("OK");
    dialogOkText.setCharacterSize(20);
    dialogOkText.setFillColor(sf::Color::Black);
    dialogOkText.setPosition(425, 325);
}

bool Menu::show() {
    bool gameShouldStart = false;

    while (window.isOpen()) {
        processEvents(gameShouldStart);
        render();

        if (gameShouldStart) {
            window.close();
        }
    }

    return gameShouldStart;
}

void Menu::processEvents(bool& gameShouldStart) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            auto mx = static_cast<float>(event.mouseButton.x);
            auto my = static_cast<float>(event.mouseButton.y);

            if (startButton.getGlobalBounds().contains(mx, my)){
                
                gameShouldStart = true;
            }
            if (!showDialog && loginButton1.getGlobalBounds().contains(mx, my)) {
                showDialog = true;
                activeDialogPlayer = 1;
                dialogInput.clear();
                dialogInputText.setString("");
            }

            if (!showDialog && loginButton2.getGlobalBounds().contains(mx, my)) {
                showDialog = true;
                activeDialogPlayer = 2;
                dialogInput.clear();
                dialogInputText.setString("");
            }

            if (showDialog && dialogOkButton.getGlobalBounds().contains(mx, my)) {
                if (activeDialogPlayer == 1) {
                    nickname1 = dialogInput;
                    std::cout << "Gracz 1: " << nickname1 << std::endl;
                }
                else if (activeDialogPlayer == 2) {
                    nickname2 = dialogInput;
                    std::cout << "Gracz 2: " << nickname2 << std::endl;
                }
                showDialog = false;
            }   
        }
       
        if (showDialog && event.type == sf::Event::TextEntered && event.text.unicode < 128) {
            if (event.text.unicode == 8 && !dialogInput.empty()) // Backspace
                dialogInput.pop_back();
            else if (event.text.unicode != 8 && event.text.unicode != 13) // Nie Enter
                dialogInput += static_cast<char>(event.text.unicode);
            dialogInputText.setString(dialogInput);
        }
    }
}

void Menu::render() {
    window.clear(sf::Color::Blue);
    window.draw(backgroundSprite);
    window.draw(startButton);
    window.draw(startText);
    window.draw(loginButton1);
    window.draw(loginText1);
    window.draw(loginButton2);
    window.draw(loginText2);
    if (showDialog) {
        window.draw(dialogBox);
        window.draw(dialogPrompt);
        window.draw(dialogInputText);
        window.draw(dialogOkButton);
        window.draw(dialogOkText);
    }
    window.display();
}
