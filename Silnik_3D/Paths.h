#pragma once
#ifndef PATHS_H
#define PATHS_H

#include <vector>
#include <utility>

/**
 * @brief Klasa pomocnicza zawieraj¹ca wspó³rzêdne œcie¿ek i domków graczy w grze Ludo.
 *
 * Klasa `Paths` dostarcza zestawy wspó³rzêdnych 2D reprezentuj¹cych:
 * - pozycje domków startowych dla ka¿dego z graczy,
 * - œcie¿ki ruchu pionków po planszy od pola startowego do mety.
 *
 * Wszystkie metody s¹ statyczne i zwracaj¹ gotowe wektory wspó³rzêdnych w formacie `(x, y)`.
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
