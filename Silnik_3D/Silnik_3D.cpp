//
//#include "Engine.h"
//#include <SFML/Graphics.hpp>
//
///**
// * @brief Punkt wejścia do programu.
// *
// * Funkcja main odpowiada za konfigurację i uruchomienie silnika gry.
// * Przygotowuje listę tekstur, ustawia parametry, a następnie inicjalizuje
// * i uruchamia główną pętlę gry.
// *
// * @param argc Liczba argumentów wiersza poleceń.
// * @param argv Tablica argumentów wiersza poleceń.
// * @return int Kod zakończenia programu (zwraca 0 w przypadku powodzenia).
// */
//int main(int argc, char** argv) {
//    /**
//     * @brief Ścieżki do tekstur używanych w grze.
//     *
//     * Wektor zawiera ścieżki do plików obrazów, które będą ładowane
//     * i używane jako tekstury w silniku gry.
//     */
//   std::vector<std::string> texturePaths = {
//       "images/tlo_chinczyk.png", "images/1.png", "images/2.png", "images/3.png",
//       "images/4.png", "images/5.png", "images/6.png", "images/pionek1.png", "images/pionek2.png"
//    };
//
//    /**
//     * @brief Liczba klatek na sekundę (FPS).
//     *
//     * Określa liczbę klatek, które silnik gry powinien renderować w ciągu jednej sekundy.
//     */
//    int frameRate = 60;
//
//    /**
//     * @brief Inicjalizacja silnika gry.
//     *
//     * Tworzy obiekt silnika gry o zadanych wymiarach okna, tytule i liczbie FPS.
//     *
//     * @param width Szerokość okna gry (800 px).
//     * @param height Wysokość okna gry (600 px).
//     * @param title Tytuł okna gry ("Game Engine").
//     * @param frameRate Liczba klatek na sekundę (60 FPS).
//     */
//    Engine gameEngine(800, 600, "Game Engine", frameRate);
//
//    /**
//     * @brief Ustawienie instancji silnika gry.
//     *
//     * Umożliwia globalny dostęp do obiektu silnika gry.
//     *
//     * @param instance Wskaźnik do obiektu silnika gry.
//     */
//    Engine::setInstance(&gameEngine);
//
//    /**
//     * @brief Inicjalizacja silnika gry.
//     *
//     * Wywołuje funkcję inicjalizującą silnik gry z argumentami wiersza poleceń.
//     *
//     * @param argc Liczba argumentów wiersza poleceń.
//     * @param argv Tablica argumentów wiersza poleceń.
//     */
//    gameEngine.init(argc, argv);
//
//    /**
//     * @brief Ustawienie koloru czyszczenia okna.
//     *
//     * Kolor tła dla okna gry, podany w formacie RGB z zakresu [0.0, 1.0].
//     *
//     * @param red Składowa czerwona (0.2f).
//     * @param green Składowa zielona (0.3f).
//     * @param blue Składowa niebieska (0.4f).
//     */
//   gameEngine.setClearColor(0.2f, 0.3f, 0.4f);
//
//    /**
//     * @brief Ustawienie ścieżek tekstur.
//     *
//     * Przekazuje wektor ścieżek do tekstur, które mają być załadowane przez silnik gry.
//     *
//     * @param texturePaths Wektor zawierający ścieżki do plików z teksturami.
//     */
//   gameEngine.setTextures(texturePaths);
//
//    /**
//     * @brief Uruchomienie głównej pętli gry.
//     *
//     * Rozpoczyna działanie silnika gry, w tym renderowanie i obsługę zdarzeń.
//     */
//   gameEngine.run();
//
//   return 0;
//}
//
#include "Engine.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>

int main(int argc, char** argv) {
    Menu menu(800, 600);
    if (!menu.show()) {
        return 0; // użytkownik zamknął menu bez kliknięcia "Start gry"
    }

    std::vector<std::string> texturePaths = {
        "images/tlo_chinczyk.png", "images/1.png", "images/2.png", "images/3.png",
        "images/4.png", "images/5.png", "images/6.png", "images/pionek1.png", "images/pionek2.png"
    };

    int frameRate = 60;
    Engine gameEngine(800, 600, "Game Engine", frameRate);
    Engine::setInstance(&gameEngine);
    gameEngine.init(argc, argv);
    gameEngine.setClearColor(0.2f, 0.3f, 0.4f);
    gameEngine.setTextures(texturePaths);
    gameEngine.run();

    return 0;
}
