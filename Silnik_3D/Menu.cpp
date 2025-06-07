#include "Menu.h"

/**
 * @brief Konstruktor klasy Menu.
 *
 * Inicjalizuje okno menu, ładuje czcionkę i tekstury, ustawia pozycje oraz style przycisków
 * i elementów dialogowych do wpisywania nazw graczy.
 *
 * @param width Szerokość okna menu w pikselach.
 * @param height Wysokość okna menu w pikselach.
 */
Menu::Menu(unsigned int width, unsigned int height)
    : window(sf::VideoMode(width, height), "Menu") {
    font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

    if (!backgroundTexture.loadFromFile("images/tlo_menu2.png")) {
   
        std::cerr << "Nie udalo sie zaladowac tla menu!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);
    
    startButton.setSize(sf::Vector2f(300, 50));
    startButton.setPosition(150, 150);
    startButton.setFillColor(sf::Color(0, 0, 0, 0));//przezroczysty kolor 

    loginButton1.setSize(sf::Vector2f(300, 70));
    loginButton1.setPosition(150, 210);
    loginButton1.setFillColor(sf::Color(0, 0, 0, 0));
   
    loginButton2.setSize(sf::Vector2f(300, 70));
    loginButton2.setPosition(150, 300);
    loginButton2.setFillColor(sf::Color(0, 0, 0, 0));

    loginButton3.setSize(sf::Vector2f(300, 70));
    loginButton3.setPosition(150, 380);
    loginButton3.setFillColor(sf::Color(0, 0, 0, 0));

    loginButton4.setSize(sf::Vector2f(300, 70));
    loginButton4.setPosition(150, 466);
    loginButton4.setFillColor(sf::Color(0, 0, 0, 0));
    
    dialogBox.setSize(sf::Vector2f(400, 200));
    dialogBox.setFillColor(sf::Color(50, 50, 50, 230));
    dialogBox.setOutlineColor(sf::Color(0, 0, 0, 0));
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

    dialogCommunicat.setSize(sf::Vector2f(480, 40));
    dialogCommunicat.setFillColor(sf::Color::Red);
    dialogCommunicat.setPosition(65, 7);
    errorText.setFont(font);
    errorText.setCharacterSize(30);
    errorText.setFillColor(sf::Color::Black);
    errorText.setString("Podaj nicki przynajmniej 2 graczy!");
    
    errorText.setPosition(70, 7);
    showError = false;

}

/**
 * @brief Wyświetla okno menu i obsługuje główną pętlę zdarzeń do momentu rozpoczęcia gry.
 *
 * Funkcja działa w pętli dopóki okno menu jest otwarte. Obsługuje zdarzenia wejściowe
 * oraz renderowanie. Zamyka okno i zwraca true, jeśli kliknięto „Start” i podano co najmniej 2 nicki.
 *
 * @return true jeśli gracz rozpoczął grę, false jeśli zamknięto okno bez rozpoczęcia gry.
 */

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

/**
 * @brief Obsługuje zdarzenia użytkownika w oknie menu (mysz, klawiatura, interakcje).
 *
 * Reaguje na:
 * - kliknięcie przycisku „Start” — sprawdza, czy podano nicki dla co najmniej 2 graczy,
 * - kliknięcia przycisków logowania — otwiera dialog do wpisania nicku,
 * - kliknięcie przycisku „OK” w dialogu — przypisuje nick do odpowiedniego gracza,
 * - wpisywanie tekstu — rejestruje nicki graczy,
 * - najeżdżanie kursorem na przyciski — zmienia ich kolor, by podkreślić interakcję.
 *
 * @param gameShouldStart Referencja do flagi, która zostanie ustawiona na true,
 *                        jeśli użytkownik kliknie „Start” z co najmniej dwoma podanymi nickami.
 */
void Menu::processEvents(bool& gameShouldStart) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            auto mx = static_cast<float>(event.mouseButton.x);
            auto my = static_cast<float>(event.mouseButton.y);

            if (startButton.getGlobalBounds().contains(mx, my)){

             
                int nickCount = 0;
                if (!nickname1.empty()) nickCount++;
                if (!nickname2.empty()) nickCount++;
                if (!nickname3.empty()) nickCount++;
                if (!nickname4.empty()) nickCount++;

                if (nickCount >= 2) {
                    gameShouldStart = true;
                    showError = false;
                }
                else {
                    showError = true;
                }
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
            if (!showDialog && loginButton3.getGlobalBounds().contains(mx, my)) {
                showDialog = true;
                activeDialogPlayer = 3;
                dialogInput.clear();
                dialogInputText.setString("");
            }

            if (!showDialog && loginButton4.getGlobalBounds().contains(mx, my)) {
                showDialog = true;
                activeDialogPlayer = 4;
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
                if (activeDialogPlayer == 3) {
                    nickname3 = dialogInput;
                    std::cout << "Gracz 3: " << nickname3 << std::endl;
                }
                else if (activeDialogPlayer == 4) {
                    nickname4 = dialogInput;
                    std::cout << "Gracz 4: " << nickname4 << std::endl;
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
        // Pobierz pozycję kursora
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // Jeśli kursor jest nad przyciskiem Start, zmień kolor
        if (startButton.getGlobalBounds().contains(mousePosF)) {
            startButton.setFillColor(sf::Color(255, 255, 255, 100)); // lekko przezroczysty biały
        }
        else {
            startButton.setFillColor(sf::Color(0, 0, 0, 0)); // całkowicie przezroczysty
        }
        if (loginButton1.getGlobalBounds().contains(mousePosF)) {
            loginButton1.setFillColor(sf::Color(255, 255, 255, 100)); // lekko przezroczysty biały
        }
        else {
            loginButton1.setFillColor(sf::Color(0, 0, 0, 0)); // całkowicie przezroczysty
        }
        if (loginButton2.getGlobalBounds().contains(mousePosF)) {
            loginButton2.setFillColor(sf::Color(255, 255, 255, 100)); // lekko przezroczysty biały
        }
        else {
            loginButton2.setFillColor(sf::Color(0, 0, 0, 0)); // całkowicie przezroczysty
        }
        if (loginButton3.getGlobalBounds().contains(mousePosF)) {
            loginButton3.setFillColor(sf::Color(255, 255, 255, 100)); // lekko przezroczysty biały
        }
        else {
            loginButton3.setFillColor(sf::Color(0, 0, 0, 0)); // całkowicie przezroczysty
        }
        if (loginButton4.getGlobalBounds().contains(mousePosF)) {
            loginButton4.setFillColor(sf::Color(255, 255, 255, 100)); // lekko przezroczysty biały
        }
        else {
            loginButton4.setFillColor(sf::Color(0, 0, 0, 0)); // całkowicie przezroczysty
        }
        if (dialogOkButton.getGlobalBounds().contains(mousePosF)) {
            dialogOkButton.setFillColor(sf::Color(255, 255, 255, 100)); // lekko przezroczysty biały
        }
        else {
            dialogOkButton.setFillColor(sf::Color::Green); 
        }

    }
}

/**
 * @brief Renderuje wszystkie widoczne elementy interfejsu menu do okna.
 *
 * Rysuje tło, przyciski do logowania, przycisk startu, dialog do wpisywania nicku
 * oraz ewentualny komunikat o błędzie, jeśli nie podano wystarczającej liczby graczy.
 */
void Menu::render() {
    window.clear(sf::Color::Blue);
    window.draw(backgroundSprite);
    window.draw(startButton);
    window.draw(startText);
    window.draw(loginButton1);
    window.draw(loginButton2);

    window.draw(loginButton3);
    window.draw(loginButton4);

    if (showDialog) {
        window.draw(dialogBox);
        window.draw(dialogPrompt);
        window.draw(dialogInputText);
        window.draw(dialogOkButton);
        window.draw(dialogOkText);
    }
    if (showError) {
        window.draw(dialogCommunicat);
        window.draw(errorText);
    }
    window.display();
}
