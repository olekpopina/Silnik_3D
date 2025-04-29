#pragma once  
#ifndef LIGHT_H  
#define LIGHT_H  

#include <GL/freeglut.h>

// Enum reprezentuj¹cy tryby oœwietlenia
enum class LightingMode {
    NONE,            ///< Brak oœwietlenia
    POINT_LIGHT,     ///< Œwiat³o punktowe
    DIRECTIONAL_LIGHT, ///< Œwiat³o kierunkowe
    SPOTLIGHT        ///< Œwiat³o punktowe o w¹skim k¹cie
};

class Light {
public:
    void configureLighting();
    void switchLightingMode();

    LightingMode currentLightingMode = LightingMode::NONE;
};

#endif // LIGHT_H
