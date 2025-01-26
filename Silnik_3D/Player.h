#ifndef PLAYER_H
#define PLAYER_H

#include "Triangle.h"
#include "Cube.h"
#include "PrimitiveDrawer.h"

/**
 * @class Player
 * @brief Klasa reprezentuj¹ca gracza.
 *
 * Klasa zarz¹dza obiektami gracza, w tym rysowaniem, ruchem i rotacj¹ figur 3D (trójk¹t i szeœcian).
 */
class Player {
public:
    /**
     * @brief Konstruktor klasy Player.
     *
     * Inicjalizuje obiekt gracza, przypisuj¹c odpowiednie obiekty (trójk¹t, szeœcian i rysownik).
     *
     * @param triangle WskaŸnik na obiekt typu Triangle reprezentuj¹cy trójk¹t gracza.
     * @param cube WskaŸnik na obiekt typu Cube reprezentuj¹cy szeœcian gracza.
     * @param drawer WskaŸnik na obiekt PrimitiveDrawer, który s³u¿y do rysowania obiektów.
     */
    Player(Triangle* triangle, Cube* cube, PrimitiveDrawer* drawer);

    /**
     * @brief Obs³uguje wejœcie od u¿ytkownika (naciœniêcie klawisza).
     *
     * Metoda ta reaguje na naciœniêcie klawiszy i zmienia stan gracza, np. uruchamia rotacjê.
     *
     * @param key Kod naciœniêtego klawisza.
     */
    void handleInput(unsigned char key);

    /**
     * @brief Aktualizuje stan gracza na podstawie up³ywu czasu.
     *
     * Metoda ta jest wywo³ywana co klatkê i odpowiada za aktualizacjê animacji oraz rotacji.
     *
     * @param deltaTime Czas, który up³yn¹³ od ostatniej klatki (w sekundach).
     */
    void update(float deltaTime);

private:
    Triangle* triangle; ///< WskaŸnik na obiekt typu Triangle (trójk¹t) reprezentuj¹cy gracza.
    Cube* cube; ///< WskaŸnik na obiekt typu Cube (szeœcian) reprezentuj¹cy gracza.
    PrimitiveDrawer* drawer; ///< WskaŸnik na obiekt PrimitiveDrawer, który rysuje obiekty.

    bool isRotating; ///< Flaga informuj¹ca, czy gracz wykonuje rotacjê trójk¹ta.
    bool isRotatingCube; ///< Flaga informuj¹ca, czy gracz wykonuje rotacjê szeœcianu.
};

#endif // PLAYER_H
