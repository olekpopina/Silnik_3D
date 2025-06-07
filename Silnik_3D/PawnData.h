#pragma once
#ifndef PAWN_DATA_H
#define PAWN_DATA_H

#include <vector>
#include <string>
#include <utility>
#include <GL/freeglut.h>

/**
 * @brief Struktura przechowuj�ca wszystkie dane i wska�niki zwi�zane z jednym pionkiem w grze.
 *
 * Struktura `PawnData` grupuje dane potrzebne do obs�ugi logiki, animacji i rysowania pojedynczego pionka.
 * Przechowuje odniesienia (referencje) do pozycji, stanu ruchu, tekstury i �cie�ki, co pozwala zarz�dza� pionkami dynamicznie.
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
