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

/**
 * @class Light
 * @brief Klasa zarz�dzaj�ca o�wietleniem w scenie 3D.
 *
 * Umo�liwia konfiguracj� i prze��czanie trybu o�wietlenia.
 * Obs�uguje r�ne tryby (np. �wiat�o punktowe, kierunkowe),
 * zale�nie od warto�ci typu LightingMode.
 */
class Light {
public:
    void configureLighting();
    void switchLightingMode();

    LightingMode currentLightingMode = LightingMode::POINT_LIGHT;
};

#endif // LIGHT_H
