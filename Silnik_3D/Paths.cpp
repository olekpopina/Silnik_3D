#include "Paths.h"

/**
 * @brief Zwraca współrzędne domku gracza zielonego.
 *
 * @return Wektor współrzędnych 2D (x, y) dla pozycji startowych pionków zielonych.
 */
std::vector<std::pair<float, float>> Paths::getGreenHouse()
{
    return {
        {0.12f, 0.72f}, {0.12f, 0.82f}, {0.22f, 0.72f}, {0.22f, 0.82f}
    };
}

/**
 * @brief Zwraca współrzędne domku gracza żółtego.
 *
 * @return Wektor współrzędnych 2D (x, y) dla pozycji startowych pionków żółtych.
 */
std::vector<std::pair<float, float>> Paths::getYellowHouse()
{
    return {
        {0.80f, 0.72f}, {0.80f, 0.82f}, {0.70f, 0.72f}, {0.70f, 0.82f}
    };
}

/**
 * @brief Zwraca współrzędne domku gracza czerwonego.
 *
 * @return Wektor współrzędnych 2D (x, y) dla pozycji startowych pionków czerwonych.
 */
std::vector<std::pair<float, float>> Paths::getRedHouse() {
    return {
        {0.12f, 0.12f}, {0.12f, 0.22f}, {0.22f, 0.12f}, {0.22f, 0.22f}
    };
}

/**
 * @brief Zwraca współrzędne domku gracza niebieskiego.
 *
 * @return Wektor współrzędnych 2D (x, y) dla pozycji startowych pionków niebieskich.
 */
std::vector<std::pair<float, float>> Paths::getBlueHouse() {
    return {
        {0.80f, 0.13f}, {0.80f, 0.23f}, {0.70f, 0.13f}, {0.70f, 0.23f}

    };
}

/**
 * @brief Zwraca ścieżkę ruchu dla gracza czerwonego.
 *
 * @return Wektor współrzędnych 2D reprezentujących kolejne pola ścieżki czerwonego gracza.
 */
std::vector<std::pair<float, float>> Paths::getRedPath() {
    return {
        {0.38f, 0.06f},{0.38f, 0.14f}, {0.38f, 0.21f}, {0.38f, 0.28f}, {0.38f, 0.35f}, {0.31f, 0.4f}, {0.25f, 0.4f},
        {0.18f, 0.4f}, {0.11f, 0.4f}, {0.04f, 0.4f}, {0.00f, 0.4f}, {0.00f, 0.47f}, {0.00f, 0.54f},
        {0.06f, 0.54f}, {0.13f, 0.54f}, {0.20f, 0.54f}, {0.26f, 0.54f}, {0.33f, 0.54f}, {0.39f, 0.61f},
        {0.39f, 0.68f}, {0.39f, 0.75f}, {0.39f, 0.82f}, {0.39f, 0.89f}, {0.39f, 0.94f}, {0.46f, 0.94f},
        {0.52f, 0.94f}, {0.52f, 0.87f}, {0.52f, 0.80f}, {0.52f, 0.73f}, {0.52f, 0.66f}, {0.52f, 0.59f},
        {0.59f, 0.53f}, {0.66f, 0.53f}, {0.72f, 0.53f}, {0.79f, 0.53f}, {0.86f, 0.53f}, {0.91f, 0.53f},
        {0.91f, 0.46f}, {0.91f, 0.4f}, {0.85f, 0.4f}, {0.78f, 0.4f}, {0.71f, 0.4f}, {0.64f, 0.4f},
        {0.58f, 0.4f}, {0.52f, 0.33f}, {0.52f, 0.26f}, {0.52f, 0.19f}, {0.52f, 0.12f}, {0.52f, 0.05f},
        {0.52f, 0.00f}, {0.45f, 0.00f}, {0.45f, 0.07f}, {0.45f, 0.14f}, {0.45f, 0.21f}, {0.45f, 0.28f},
        {0.45f, 0.35f}, {0.45f, 0.42f}
    };
}

/**
 * @brief Zwraca ścieżkę ruchu dla gracza niebieskiego.
 *
 * @return Wektor współrzędnych 2D reprezentujących kolejne pola ścieżki niebieskiego gracza.
 */
std::vector<std::pair<float, float>> Paths::getBluePath() {
    return {
        {0.85f, 0.4f},{0.78f, 0.4f}, {0.71f, 0.4f}, {0.64f, 0.4f}, {0.58f, 0.4f}, {0.52f, 0.33f}, {0.52f, 0.26f},
        {0.52f, 0.19f}, {0.52f, 0.12f}, {0.52f, 0.05f}, {0.52f, 0.00f}, {0.45f, 0.00f}, {0.38f, 0.00f},
        {0.38f, 0.07f}, {0.38f, 0.14f}, {0.38f, 0.21f}, {0.38f, 0.28f}, {0.38f, 0.35f}, {0.31f, 0.4f},
        {0.25f, 0.4f}, {0.18f, 0.4f}, {0.11f, 0.4f}, {0.04f, 0.4f}, {0.00f, 0.4f}, {0.00f, 0.47f},
        {0.00f, 0.54f}, {0.06f, 0.54f}, {0.13f, 0.54f}, {0.20f, 0.54f}, {0.26f, 0.54f}, {0.33f, 0.54f},
        {0.39f, 0.61f}, {0.39f, 0.68f}, {0.39f, 0.75f}, {0.39f, 0.82f}, {0.39f, 0.89f}, {0.39f, 0.94f},
        {0.46f, 0.94f}, {0.52f, 0.94f}, {0.52f, 0.87f}, {0.52f, 0.80f}, {0.52f, 0.73f}, {0.52f, 0.66f},
        {0.52f, 0.59f}, {0.59f, 0.53f}, {0.66f, 0.53f}, {0.72f, 0.53f}, {0.79f, 0.53f}, {0.86f, 0.53f},
        {0.91f, 0.53f}, {0.91f, 0.46f}, {0.84f, 0.46f}, {0.77f, 0.46f}, {0.70f, 0.46f}, {0.64f, 0.46f},
        {0.58f, 0.46f}, {0.51f, 0.46f}
    };
}

/**
 * @brief Zwraca ścieżkę ruchu dla gracza żółtego.
 *
 * @return Wektor współrzędnych 2D reprezentujących kolejne pola ścieżki żółtego gracza.
 */
std::vector<std::pair<float, float>> Paths::getYellowPath()
{
    return {
    { 0.52f, 0.87f }, { 0.52f, 0.80f }, { 0.52f, 0.73f }, { 0.52f, 0.66f },
    { 0.52f, 0.59f }, { 0.59f, 0.53f }, {0.66f, 0.53f}, {0.72f, 0.53f}, {0.79f, 0.53f}, 
    {0.86f, 0.53f},  {0.91f, 0.53f}, {0.91f, 0.46f}, {0.91f, 0.4f}, {0.85f, 0.4f}, {0.78f, 0.4f}, {0.71f, 0.4f}, {0.64f, 0.4f},
    {0.58f, 0.4f}, {0.52f, 0.33f}, {0.52f, 0.26f}, {0.52f, 0.19f}, {0.52f, 0.12f}, {0.52f, 0.05f},
    {0.52f, 0.00f}, {0.45f, 0.00f},{0.38f, 0.00f}, {0.38f, 0.06f},{0.38f, 0.14f}, {0.38f, 0.21f}, {0.38f, 0.28f}, {0.38f, 0.35f}, {0.31f, 0.4f}, {0.25f, 0.4f},
    {0.18f, 0.4f}, {0.11f, 0.4f}, {0.04f, 0.4f}, {0.00f, 0.4f}, {0.00f, 0.47f}, {0.00f, 0.54f},
    {0.06f, 0.54f}, {0.13f, 0.54f}, {0.20f, 0.54f}, {0.26f, 0.54f}, {0.33f, 0.54f}, {0.39f, 0.61f},
    {0.39f, 0.68f}, {0.39f, 0.75f}, {0.39f, 0.82f}, {0.39f, 0.89f}, {0.39f, 0.94f}, {0.46f, 0.94f},
    {0.45f, 0.87f},{0.45f, 0.80f},{0.45f, 0.73f},{0.45f, 0.66f},{0.45f, 0.59f}, {0.45f, 0.52f}
    };
}

/**
 * @brief Zwraca ścieżkę ruchu dla gracza zielonego.
 *
 * @return Wektor współrzędnych 2D reprezentujących kolejne pola ścieżki zielonego gracza.
 */
std::vector<std::pair<float, float>> Paths::getGreenPath()
{
    return {
        {0.06f, 0.54f}, {0.13f, 0.54f}, {0.20f, 0.54f}, {0.26f, 0.54f}, {0.33f, 0.54f}, {0.39f, 0.61f},
        {0.39f, 0.68f}, {0.39f, 0.75f}, {0.39f, 0.82f}, {0.39f, 0.89f}, {0.39f, 0.94f}, {0.46f, 0.94f},
        {0.52f, 0.94f}, {0.52f, 0.87f}, {0.52f, 0.80f}, {0.52f, 0.73f}, {0.52f, 0.66f}, {0.52f, 0.59f},
        {0.59f, 0.53f}, {0.66f, 0.53f}, {0.72f, 0.53f}, {0.79f, 0.53f}, {0.86f, 0.53f}, {0.91f, 0.53f},
        {0.91f, 0.46f}, {0.91f, 0.4f}, {0.85f, 0.4f}, {0.78f, 0.4f}, {0.71f, 0.4f}, {0.64f, 0.4f},
        {0.58f, 0.4f}, {0.52f, 0.33f}, {0.52f, 0.26f}, {0.52f, 0.19f}, {0.52f, 0.12f}, {0.52f, 0.05f},
        {0.52f, 0.00f}, {0.45f, 0.00f}, {0.38f, 0.00f}, {0.38f, 0.07f}, {0.38f, 0.14f}, {0.38f, 0.21f}, {0.38f, 0.28f}, {0.38f, 0.35f}, {0.31f, 0.4f},
        {0.25f, 0.4f}, {0.18f, 0.4f}, {0.11f, 0.4f}, {0.04f, 0.4f}, {0.00f, 0.4f}, {0.00f, 0.47f}, {0.06f, 0.47f}, {0.13f, 0.47f},{0.20f, 0.47f}, {0.26f, 0.47f}, {0.32f, 0.47f},{0.38f, 0.47f}
    };
}
