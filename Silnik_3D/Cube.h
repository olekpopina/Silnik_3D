#ifndef CUBE_H
#define CUBE_H

#include <GL/freeglut.h>
#include "TransformableObject.h"
#include "BitmapHandler.h"

/**
 * @brief Klasa reprezentująca sześcian 3D, dziedzicząca po TransformableObject.
 *
 * Klasa ta odpowiada za rysowanie sześcianu, obsługę jego obrotu oraz przypisanie tekstur.
 * Umożliwia także ustawianie rotacji sześcianu oraz aktualizację jego obrotu na podstawie upływającego czasu.
 */
class Cube : public TransformableObject {
public:
    /**
     * @brief Konstruktor klasy Cube.
     *
     * Inicjalizuje domyślne wartości zmiennych i przygotowuje sześcian do rysowania.
     */
    Cube();

    /**
     * @brief Funkcja rysująca sześcian.
     *
     * Funkcja ta jest odpowiedzialna za rysowanie sześcianu z wykorzystaniem OpenGL.
     * Jest wywoływana w kontekście renderowania, uwzględniając przekształcenia (przesunięcie, skalowanie, obrót).
     */
    void draw() const override;

    /**
     * @brief Ustawia flagę rotacji sześcianu.
     *
     * @param rotating Określa, czy sześcian ma się obracać (true) czy nie (false).
     */
    void setRotationC(bool rotating);

    /**
     * @brief Aktualizuje kąt rotacji sześcianu na podstawie upływającego czasu.
     *
     * @param deltaTime Czas, który upłynął od ostatniej aktualizacji w sekundach.
     *
     * Funkcja ta zwiększa kąt rotacji sześcianu w zależności od ustawionej prędkości obrotu.
     * Kąt rotacji jest ograniczany do zakresu [0, 360] stopni.
     */
    void updateRotationC(float deltaTime);

    // Współrzędne wierzchołków sześcianu
    float vertices[24];

    // Indeksy wierzchołków do rysowania powierzchni sześcianu
    unsigned int indices[36];

    // Normale dla wierzchołków sześcianu
    float normals[24];

    // Kolory wierzchołków sześcianu
    float colors[24];

    // Flaga określająca, czy sześcian jest w trakcie rotacji
    bool isRotating = false;

    // Kąt rotacji sześcianu
    float rotationAngle = 0.0f;

    // Prędkość rotacji sześcianu
    float rotationSpeed = 0.4f;

    // Obiekt klasy BitmapHandler do zarządzania teksturami
    BitmapHandler bitmapHandler;
};

#endif // CUBE_H
 