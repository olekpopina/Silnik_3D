#pragma once  
#ifndef LIGHT_H  
#define LIGHT_H  

#include <GL/freeglut.h>

// Enum reprezentujący tryby oświetlenia
enum class LightingMode {
    NONE,            ///< Brak oświetlenia
    POINT_LIGHT,     ///< Światło punktowe
    DIRECTIONAL_LIGHT, ///< Światło kierunkowe
    SPOTLIGHT        ///< Światło punktowe o wąskim kącie
};

/**
 * @class Light
 * @brief Klasa zarządzająca oświetleniem w scenie 3D.
 *
 * Umożliwia konfigurację i przełączanie trybu oświetlenia.
 * Obsługuje różne tryby (np. światło punktowe, kierunkowe),
 * zależnie od wartości typu LightingMode.
 */
class Light {
public:
    void configureLighting();
    void switchLightingMode();

    LightingMode currentLightingMode = LightingMode::POINT_LIGHT;
};

#endif // LIGHT_H
