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
private:
    Assimp::Importer importer;
    const aiScene* scene;

};
