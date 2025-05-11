#pragma once


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "Paths.h"
#include <iostream>


class Pawn3D {
public:
    Pawn3D();
    ~Pawn3D();

    bool loadModel();
    void draw() const;

    void draw3DPawnAtBlue(float x, float y);
    void draw3DPawnAtRed(float x, float y);
    void draw3DPawnAtYellow(float x, float y);
    void draw3DPawnAtGreen(float x, float y);
    void drawPawns();
    void drawPawnsPlay();
    void PlayPawnsPointers(bool *RedPlay, float *pawnXred, float *pawnYred, bool* RedPlay2, float* pawnXred2, float* pawnYred2,
    bool* RedPlay3, float* pawnXred3, float* pawnYred3, bool* RedPlay4, float* pawnXred4, float* pawnYred4,
    bool* BluePlay, float* pawnXblue, float* pawnYblue, bool* BluePlay2, float* pawnXblue2, float* pawnYblue2,
    bool* Blueblue3, float* pawnXblue3, float* pawnYblue3, bool* Redblue4, float* pawnXblue4, float* pawnYblue4);

    void setHousePointers(
        std::vector<std::pair<float, float>>* red,
        std::vector<std::pair<float, float>>* blue,
        std::vector<std::pair<float, float>>* yellow,
        std::vector<std::pair<float, float>>* green
    );
    std::vector<std::pair<float, float>>* redHouse = nullptr;
    std::vector<std::pair<float, float>>* blueHouse = nullptr;
    std::vector<std::pair<float, float>>* yellowHouse = nullptr;
    std::vector<std::pair<float, float>>* greenHouse = nullptr;
    bool* redPawnInPlay = nullptr;
    float* pawnX = nullptr;
    float* pawnY = nullptr;

    bool* redPawnInPlay2 = nullptr;
    float* pawnX_R2 = nullptr;
    float* pawnY_R2 = nullptr;

    bool* redPawnInPlay3 = nullptr;
    float* pawnX_R3 = nullptr;
    float* pawnY_R3 = nullptr;

    bool* redPawnInPlay4 = nullptr;
    float* pawnX_R4 = nullptr;
    float* pawnY_R4 = nullptr;

    bool* bluePawnInPlay = nullptr;
    float* pawnX2 = nullptr;
    float* pawnY2 = nullptr;

    bool* bluePawnInPlay2 = nullptr;
    float* pawnX_B2 = nullptr;
    float* pawnY_B2 = nullptr;

    bool* bluePawnInPlay3 = nullptr;
    float* pawnX_B3 = nullptr;
    float* pawnY_B3 = nullptr;

    bool* bluePawnInPlay4 = nullptr;
    float* pawnX_B4 = nullptr;
    float* pawnY_B4 = nullptr;

private:
    Assimp::Importer importer;
    const aiScene* scene;
   
};
