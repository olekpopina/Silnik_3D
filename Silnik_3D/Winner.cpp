#include "Winner.h"

Winner::Winner(unsigned int width, unsigned int height)
    : window(sf::VideoMode(width, height), "Winner") {
    font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

    if (!backgroundTexture.loadFromFile("images/tlo.png")) {

        std::cerr << "Nie udalo sie zaladowac tla winner!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    startText.setFont(font);
    startText.setString("Wygrywa");
    startText.setCharacterSize(40);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(150, 150);
}

bool Winner::showWinnerScreen() {
    bool gameShouldFinish = false;

    while (window.isOpen()) {
        processEvents(gameShouldFinish);
        render();

        if (gameShouldFinish) {
            window.close();
        }
    }
    return gameShouldFinish;
}
void Winner::processEvents(bool& gameShouldStart) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) 
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            auto mx = static_cast<float>(event.mouseButton.x);
            auto my = static_cast<float>(event.mouseButton.y);
        }
    }
}

void Winner::render() {
    window.clear(sf::Color::Blue);
    window.draw(backgroundSprite);
    window.draw(startText);
    
    window.display();
}