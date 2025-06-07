#pragma once
#ifndef PATHS_H
#define PATHS_H

#include <vector>
#include <utility>

/**
 * @brief Klasa pomocnicza zawieraj�ca wsp�rz�dne �cie�ek i domk�w graczy w grze Ludo.
 *
 * Klasa `Paths` dostarcza zestawy wsp�rz�dnych 2D reprezentuj�cych:
 * - pozycje domk�w startowych dla ka�dego z graczy,
 * - �cie�ki ruchu pionk�w po planszy od pola startowego do mety.
 *
 * Wszystkie metody s� statyczne i zwracaj� gotowe wektory wsp�rz�dnych w formacie `(x, y)`.
 */
class Paths {
public:
    static std::vector<std::pair<float, float>> getGreenHouse();
    static std::vector<std::pair<float, float>> getYellowHouse();
    static std::vector<std::pair<float, float>> getRedHouse();
    static std::vector<std::pair<float, float>> getBlueHouse();
    static std::vector<std::pair<float, float>> getRedPath();
    static std::vector<std::pair<float, float>> getBluePath();
    static std::vector<std::pair<float, float>> getYellowPath();
    static std::vector<std::pair<float, float>> getGreenPath();
};

#endif // PATHS_H
