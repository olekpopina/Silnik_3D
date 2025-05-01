#include "Light.h"


/**
 * @brief Konfiguruje oœwietlenie w grze.
 *
 * Funkcja ta ustawia odpowiedni typ oœwietlenia (punktowe, kierunkowe, spot) w zale¿noœci od aktualnego trybu.
 */
void Light::configureLighting()
{
    glEnable(GL_LIGHTING);

    switch (currentLightingMode) {
    case LightingMode::POINT_LIGHT: {
        glEnable(GL_LIGHT0);
        GLfloat pointLightPos[] = { 1.0f, 1.0f, 2.0f, 1.0f };
        GLfloat pointLightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat pointLightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat pointLightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, pointLightPos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, pointLightDiffuse);
        glLightfv(GL_LIGHT0, GL_AMBIENT, pointLightAmbient);
        glLightfv(GL_LIGHT0, GL_SPECULAR, pointLightSpecular);
        break;
    }

    case LightingMode::DIRECTIONAL_LIGHT: {
        glEnable(GL_LIGHT1);

        GLfloat dirLightDir[] = { -0.3f, -1.0f, -0.7f, 0.0f }; // œwiat³o z góry pod k¹tem
        GLfloat dirLightDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };   // mniej intensywne
        GLfloat dirLightAmbient[] = { 0.15f, 0.15f, 0.15f, 1.0f }; // subtelne t³o
        GLfloat dirLightSpecular[] = { 0.1f, 0.1f, 0.1f, 1.0f };  // prawie brak b³ysku

        glLightfv(GL_LIGHT1, GL_POSITION, dirLightDir);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, dirLightDiffuse);
        glLightfv(GL_LIGHT1, GL_AMBIENT, dirLightAmbient);
        glLightfv(GL_LIGHT1, GL_SPECULAR, dirLightSpecular);

        break;
    }

    case LightingMode::SPOTLIGHT: {
        glEnable(GL_LIGHT2);
        GLfloat spotLightPos[] = { 0.0f, 0.0f, 5.0f, 1.0f };
        GLfloat spotLightDir[] = { 0.0f, 0.0f, -1.0f };
        GLfloat spotLightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat spotLightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat spotLightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glLightfv(GL_LIGHT2, GL_POSITION, spotLightPos);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotLightDir);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0f);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, spotLightDiffuse);
        glLightfv(GL_LIGHT2, GL_AMBIENT, spotLightAmbient);
        glLightfv(GL_LIGHT2, GL_SPECULAR, spotLightSpecular);
        break;
    }

    case LightingMode::NONE:
    default:
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        break;
    }
}

/**
 * @brief Prze³¹cza tryb oœwietlenia.
 *
 * Funkcja ta prze³¹cza pomiêdzy ró¿nymi trybami oœwietlenia (brak, punktowe, kierunkowe, spot).
 */
void Light::switchLightingMode()
{
    switch (currentLightingMode) {
    case LightingMode::NONE:
        currentLightingMode = LightingMode::POINT_LIGHT;
        break;
    case LightingMode::POINT_LIGHT:
        currentLightingMode = LightingMode::DIRECTIONAL_LIGHT;
        break;
    case LightingMode::DIRECTIONAL_LIGHT:
        currentLightingMode = LightingMode::SPOTLIGHT;
        break;
    case LightingMode::SPOTLIGHT:
        currentLightingMode = LightingMode::NONE;
        break;
    }

    configureLighting();
}
