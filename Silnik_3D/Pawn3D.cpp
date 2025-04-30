#include "Pawn3D.h"
#include <GL/glew.h>
#include <iostream>

Pawn3D::Pawn3D() : scene(nullptr) {}

Pawn3D::~Pawn3D() {}

bool Pawn3D::loadModel() {
    std::string path = "images/pionek.obj"; // <<--- tutaj wpisujesz �cie�k�

    scene = importer.ReadFile(path,
        aiProcess_Triangulate | aiProcess_GenSmoothNormals);

    if (!scene) {
        std::cerr << "B��d �adowania modelu: " << importer.GetErrorString() << std::endl;
        return false;
    }
    return true;
}

void Pawn3D::draw() const {
    if (!scene) return;

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh* mesh = scene->mMeshes[i];
        const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        aiColor3D diffuse(0.f, 0.f, 0.f);
        if (material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS) {
            std::cout << "[INFO] Kolor z materia�u: "
                << diffuse.r << ", " << diffuse.g << ", " << diffuse.b << std::endl;
            float brightnessScale = 3.0f; // mo�esz zwi�kszy�, np. do 5.0
            glColor3f(
                std::min(1.0f, diffuse.r * brightnessScale),
                std::min(1.0f, diffuse.g * brightnessScale),
                std::min(1.0f, diffuse.b * brightnessScale));
        }
        else {
            std::cout << "[WARN] Brak koloru w materiale � ustawiam szary domy�lny." << std::endl;
            glColor3f(0.8f, 0.8f, 0.8f);
        }

        glBegin(GL_TRIANGLES);
        for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
            const aiFace& face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                unsigned int index = face.mIndices[k];
                aiVector3D vertex = mesh->mVertices[index];

                // Dodaj normalne (pomagaj�, gdyby� chcia� �wiat�o)
                if (mesh->HasNormals()) {
                    aiVector3D normal = mesh->mNormals[index];
                    glNormal3f(normal.x, normal.y, normal.z);
                }

                glVertex3f(vertex.x, vertex.y, vertex.z);
            }
        }
        glEnd();
    }
}
