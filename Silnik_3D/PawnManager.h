#pragma once

#include "Pawn3D.h"
#include "Paths.h"
#include <iostream>

class PawnManager {
public:
	PawnManager();
	void renderPawns();
	void updatePawnsPosition(const std::string& id);
	void initializePawnPaths();

private:
	Pawn3D pawn3D;
	std::vector<std::pair<float, float>> greenHouse = Paths::getGreenHouse();
};