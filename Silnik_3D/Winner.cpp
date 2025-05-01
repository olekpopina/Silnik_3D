#include "Winner.h"

Winner::Winner(unsigned int width, unsigned int height, const std::string& winnerName)
    : window(sf::VideoMode(width, height), "Winner"), winnerName(winnerName) {
    font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

    if (!backgroundTexture.loadFromFile("images/winner.png")) {

        std::cerr << "Nie udalo sie zaladowac tla winner!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);
   
    winnerText.setFont(font);
    winnerText.setString(winnerName);
    winnerText.setCharacterSize(30);
    winnerText.setFillColor(sf::Color::White);
    winnerText.setPosition(100, 160);
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
    window.draw(winnerText);
    window.display();
}