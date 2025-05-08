#include "PawnManager.h"

PawnManager::PawnManager()
{
    initializePawnPaths();
}

void PawnManager::renderPawns()
{
    for (const auto& pos : greenHouse) {
        pawn3D.draw3DPawnAtGreen(pos.first, pos.second);
        std::cout << "position" << pos.first << " " << pos.second;
    }
}

void PawnManager::updatePawnsPosition(const std::string& id)
{
}
void PawnManager::initializePawnPaths(){
  
    greenHouse = Paths::getGreenHouse();

}