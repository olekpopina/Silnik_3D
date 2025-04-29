#include <SFML/Graphics.hpp>
#include <iostream>

class Winner {
public:
	Winner(unsigned int width, unsigned int height);
	bool showWinnerScreen();

private:
	sf::RenderWindow window;
	sf::Font font;
	sf::Text startText;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	bool showDialog = false;
	unsigned int screenWidth = 0;
	unsigned int screenHeight = 0;
	void processEvents(bool& gameShouldFinish);
	void render();
};
