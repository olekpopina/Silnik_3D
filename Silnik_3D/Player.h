#ifndef PLAYER_H
#define PLAYER_H

#include "Triangle.h"
#include "Cube.h"
#include "PrimitiveDrawer.h"

/**
 * @class Player
 * @brief Klasa reprezentująca gracza.
 *
 * Klasa zarządza obiektami gracza, w tym rysowaniem, ruchem i rotacją figur 3D (trójkąt i sześcian).
 */
class Player {
public:
    /**
     * @brief Konstruktor klasy Player.
     *
     * Inicjalizuje obiekt gracza, przypisując odpowiednie obiekty (trójkąt, sześcian i rysownik).
     *
     * @param triangle Wskaźnik na obiekt typu Triangle reprezentujący trójkąt gracza.
     * @param cube Wskaźnik na obiekt typu Cube reprezentujący sześcian gracza.
     * @param drawer Wskaźnik na obiekt PrimitiveDrawer, który służy do rysowania obiektów.
     */
    Player(Triangle* triangle, Cube* cube, PrimitiveDrawer* drawer);

    /**
     * @brief Obsługuje wejście od użytkownika (naciśnięcie klawisza).
     *
     * Metoda ta reaguje na naciśnięcie klawiszy i zmienia stan gracza, np. uruchamia rotację.
     *
     * @param key Kod naciśniętego klawisza.
     */
    void handleInput(unsigned char key);

    /**
     * @brief Aktualizuje stan gracza na podstawie upływu czasu.
     *
     * Metoda ta jest wywoływana co klatkę i odpowiada za aktualizację animacji oraz rotacji.
     *
     * @param deltaTime Czas, który upłynął od ostatniej klatki (w sekundach).
     */
    void update(float deltaTime);

private:
    Triangle* triangle; ///< Wskaźnik na obiekt typu Triangle (trójkąt) reprezentujący gracza.
    Cube* cube; ///< Wskaźnik na obiekt typu Cube (sześcian) reprezentujący gracza.
    PrimitiveDrawer* drawer; ///< Wskaźnik na obiekt PrimitiveDrawer, który rysuje obiekty.

    bool isRotating; ///< Flaga informująca, czy gracz wykonuje rotację trójkąta.
    bool isRotatingCube; ///< Flaga informująca, czy gracz wykonuje rotację sześcianu.
};

#endif // PLAYER_H
