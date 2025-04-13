#include "Menu.h"

Menu::Menu(unsigned int width, unsigned int height)
    : window(sf::VideoMode(width, height), "Menu") {
    font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

    if (!backgroundTexture.loadFromFile("D:\\Silnik_3D\\\Silnik_3D\\\images\\tlo.png")) {
   
        std::cerr << "Nie udalo sie zaladowac tla menu!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);


    startText.setFont(font);
    startText.setString("Start gry");
    startText.setCharacterSize(40);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(300, 250);

    startButton.setSize(sf::Vector2f(200, 80));
    startButton.setPosition(290, 240);
    startButton.setFillColor(sf::Color(100, 100, 255));
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
            if (startButton.getGlobalBounds().contains(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y))) {
                gameShouldStart = true;
            }
        }
    }
}

void Menu::render() {
    window.clear(sf::Color::Blue);
    window.draw(backgroundSprite);
    window.draw(startButton);
    window.draw(startText);
    window.display();
}
