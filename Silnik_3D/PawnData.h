#pragma once
#ifndef PAWN_DATA_H
#define PAWN_DATA_H

#include <vector>
#include <string>
#include <utility>
#include <GL/freeglut.h>

/**
 * @brief Struktura przechowująca wszystkie dane i wskaźniki związane z jednym pionkiem w grze.
 *
 * Struktura `PawnData` grupuje dane potrzebne do obsługi logiki, animacji i rysowania pojedynczego pionka.
 * Przechowuje odniesienia (referencje) do pozycji, stanu ruchu, tekstury i ścieżki, co pozwala zarządzać pionkami dynamicznie.
 */
struct PawnData {
    float& pawnX;
    float& pawnY;
    int& pawnStepsRemaining;
    float pawnStepSize;
    GLuint texture;
    bool& isMoving;
    const std::string winnerName;
    bool& crossedBottomBoundary;
    std::vector<std::pair<float, float>>& house;
    int& currentStep;
    const std::vector<std::pair<float, float>>& path;
    bool isRed;
    bool isBlue;
    bool isYellow;
    bool isGreen;
    int& houseIndex;
};

#endif // PAWN_DATA_H
