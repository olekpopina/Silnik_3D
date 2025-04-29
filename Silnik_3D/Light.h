#pragma once  
#ifndef LIGHT_H  
#define LIGHT_H  

#include <GL/freeglut.h>

// Enum reprezentuj�cy tryby o�wietlenia
enum class LightingMode {
    NONE,            ///< Brak o�wietlenia
    POINT_LIGHT,     ///< �wiat�o punktowe
    DIRECTIONAL_LIGHT, ///< �wiat�o kierunkowe
    SPOTLIGHT        ///< �wiat�o punktowe o w�skim k�cie
};

class Light {
public:
    void configureLighting();
    void switchLightingMode();

    LightingMode currentLightingMode = LightingMode::NONE;
};

#endif // LIGHT_H
