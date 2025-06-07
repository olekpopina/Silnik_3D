#pragma once


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "Paths.h"
#include <iostream>

/**
 * @brief Klasa odpowiedzialna za rysowanie i obs³ugê pionków 3D w grze Ludo.
 *
 * Klasa `Pawn3D` umo¿liwia:
 * - ³adowanie modeli pionków 3D przy pomocy biblioteki Assimp,
 * - rysowanie pionków w domkach i na planszy w odpowiednich kolorach,
 * - pod³¹czenie wskaŸników do wspó³rzêdnych pionków i ich stanu (czy s¹ na planszy),
 * - ustawienie œcie¿ek domków graczy i przypisanie nicków do graczy.
 *
 * Przechowuje równie¿ wskaŸniki na stany pionków i ich pozycje, co pozwala na
 * aktualizowanie pozycji z poziomu zewnêtrznego silnika gry (`Engine`).
 */
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
    void setNicknames(const std::string* red, const std::string* blue,
        const std::string* green, const std::string* yellow);
    void PlayPawnsPointers(bool *RedPlay, float *pawnXred, float *pawnYred, bool* RedPlay2, float* pawnXred2, float* pawnYred2,
    bool* RedPlay3, float* pawnXred3, float* pawnYred3, bool* RedPlay4, float* pawnXred4, float* pawnYred4,
    bool* BluePlay, float* pawnXblue, float* pawnYblue, bool* BluePlay2, float* pawnXblue2, float* pawnYblue2,
    bool* Blueblue3, float* pawnXblue3, float* pawnYblue3, bool* Redblue4, float* pawnXblue4, float* pawnYblue4,
    bool* YellowPlay, float* pawnXyellow, float* pawnYyellow, bool* GreenPlay, float*pawnXgreen, float* pawnYgreen,
    bool* YellowPlay2, float* pawnXyellow2, float* pawnYyellow2, bool* YellowPlay3, float* pawnXyellow3, float* pawnYyellow3,
    bool* YellowPlay4, float* pawnXyellow4, float* pawnYyellow4, bool* GreenPlay2, float* pawnXgreen2, float* pawnYgreen2,
    bool* GreenPlay3, float* pawnXgreen3, float* pawnYgreen3, bool* GreenPlay4, float* pawnXgreen4, float* pawnYgreen4);

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

    bool* yellowPawnInPlay = nullptr;
    float* pawnX_YE = nullptr;
    float* pawnY_YE = nullptr;

    bool* yellowPawnInPlay2 = nullptr;
    float* pawnX_YE2 = nullptr;
    float* pawnY_YE2 = nullptr;

    bool* yellowPawnInPlay3 = nullptr;
    float* pawnX_YE3 = nullptr;
    float* pawnY_YE3 = nullptr;

    bool* yellowPawnInPlay4 = nullptr;
    float* pawnX_YE4 = nullptr;
    float* pawnY_YE4 = nullptr;

    bool* greenPawnInPlay = nullptr;
    float* pawnX_G = nullptr;
    float* pawnY_G = nullptr;

    bool* greenPawnInPlay2 = nullptr;
    float* pawnX_G2 = nullptr;
    float* pawnY_G2 = nullptr;

    bool* greenPawnInPlay3 = nullptr;
    float* pawnX_G3 = nullptr;
    float* pawnY_G3 = nullptr;

    bool* greenPawnInPlay4 = nullptr;
    float* pawnX_G4 = nullptr;
    float* pawnY_G4 = nullptr;

private:
    Assimp::Importer importer;
    const aiScene* scene;
    std::string* player1Name = nullptr;
    std::string* player2Name = nullptr;
    std::string* player3Name = nullptr;
    std::string* player4Name = nullptr;
};
