#pragma once
#ifndef PAWN_DATA_H
#define PAWN_DATA_H

#include <vector>
#include <string>
#include <utility>
#include <GL/freeglut.h>

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
    int& houseIndex;
};

#endif // PAWN_DATA_H
