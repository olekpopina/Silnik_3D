#pragma once
#ifndef PATHS_H
#define PATHS_H

#include <vector>
#include <utility>

class Paths {
public:
    static std::vector<std::pair<float, float>> getRedHouse();
    static std::vector<std::pair<float, float>> getBlueHouse();
    static std::vector<std::pair<float, float>> getRedPath();
    static std::vector<std::pair<float, float>> getBluePath();
};

#endif // PATHS_H
