#ifndef PLAYER_H
#define PLAYER_H

#include "Triangle.h"
#include "Cube.h"
#include "PrimitiveDrawer.h"

/**
 * @class Player
 * @brief Klasa reprezentuj�ca gracza.
 *
 * Klasa zarz�dza obiektami gracza, w tym rysowaniem, ruchem i rotacj� figur 3D (tr�jk�t i sze�cian).
 */
class Player {
public:
    /**
     * @brief Konstruktor klasy Player.
     *
     * Inicjalizuje obiekt gracza, przypisuj�c odpowiednie obiekty (tr�jk�t, sze�cian i rysownik).
     *
     * @param triangle Wska�nik na obiekt typu Triangle reprezentuj�cy tr�jk�t gracza.
     * @param cube Wska�nik na obiekt typu Cube reprezentuj�cy sze�cian gracza.
     * @param drawer Wska�nik na obiekt PrimitiveDrawer, kt�ry s�u�y do rysowania obiekt�w.
     */
    Player(Triangle* triangle, Cube* cube, PrimitiveDrawer* drawer);

    /**
     * @brief Obs�uguje wej�cie od u�ytkownika (naci�ni�cie klawisza).
     *
     * Metoda ta reaguje na naci�ni�cie klawiszy i zmienia stan gracza, np. uruchamia rotacj�.
     *
     * @param key Kod naci�ni�tego klawisza.
     */
    void handleInput(unsigned char key);

    /**
     * @brief Aktualizuje stan gracza na podstawie up�ywu czasu.
     *
     * Metoda ta jest wywo�ywana co klatk� i odpowiada za aktualizacj� animacji oraz rotacji.
     *
     * @param deltaTime Czas, kt�ry up�yn�� od ostatniej klatki (w sekundach).
     */
    void update(float deltaTime);

private:
    Triangle* triangle; ///< Wska�nik na obiekt typu Triangle (tr�jk�t) reprezentuj�cy gracza.
    Cube* cube; ///< Wska�nik na obiekt typu Cube (sze�cian) reprezentuj�cy gracza.
    PrimitiveDrawer* drawer; ///< Wska�nik na obiekt PrimitiveDrawer, kt�ry rysuje obiekty.

    bool isRotating; ///< Flaga informuj�ca, czy gracz wykonuje rotacj� tr�jk�ta.
    bool isRotatingCube; ///< Flaga informuj�ca, czy gracz wykonuje rotacj� sze�cianu.
};

#endif // PLAYER_H
