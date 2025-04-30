#pragma once


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

class Pawn3D {
public:
    Pawn3D();
    ~Pawn3D();

    bool loadModel();
    void draw() const;

private:
    Assimp::Importer importer;
    const aiScene* scene;
};
