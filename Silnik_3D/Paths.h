#pragma once
#ifndef PATHS_H
#define PATHS_H

#include <vector>
#include <utility>

/**
 * @brief Klasa pomocnicza zawierająca współrzędne ścieżek i domków graczy w grze Ludo.
 *
 * Klasa `Paths` dostarcza zestawy współrzędnych 2D reprezentujących:
 * - pozycje domków startowych dla każdego z graczy,
 * - ścieżki ruchu pionków po planszy od pola startowego do mety.
 *
 * Wszystkie metody są statyczne i zwracają gotowe wektory współrzędnych w formacie `(x, y)`.
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
