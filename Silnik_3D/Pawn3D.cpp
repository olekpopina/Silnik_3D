#include "Pawn3D.h"
#include <GL/glew.h>
#include <iostream>

Pawn3D::Pawn3D() : scene(nullptr) {}

Pawn3D::~Pawn3D() {}

bool Pawn3D::loadModel() {
    std::string path = "images/pionek.obj"; // <<--- tutaj wpisujesz œcie¿kê

    scene = importer.ReadFile(path,
        aiProcess_Triangulate | aiProcess_GenSmoothNormals);

    if (!scene) {
        std::cerr << "B³¹d ³adowania modelu: " << importer.GetErrorString() << std::endl;
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
            //std::cout << "[INFO] Kolor z materia³u: "
               // << diffuse.r << ", " << diffuse.g << ", " << diffuse.b << std::endl;
            float brightnessScale = 3.0f; // mo¿esz zwiêkszyæ, np. do 5.0
            glColor3f(
                std::min(1.0f, diffuse.r * brightnessScale),
                std::min(1.0f, diffuse.g * brightnessScale),
                std::min(1.0f, diffuse.b * brightnessScale));
        }
        else {
            std::cout << "[WARN] Brak koloru w materiale – ustawiam szary domyœlny." << std::endl;
            glColor3f(0.8f, 0.8f, 0.8f);
        }

        glBegin(GL_TRIANGLES);
        for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
            const aiFace& face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                unsigned int index = face.mIndices[k];
                aiVector3D vertex = mesh->mVertices[index];

                // Dodaj normalne (pomagaj¹, gdybyœ chcia³ œwiat³o)
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
void Pawn3D::draw3DPawnAtBlue(float x, float y) {
    static float angle = 0.0f; // zapamiêtuje wartoœæ miêdzy wywo³aniami
    angle += 0.5f;
    if (angle >= 360.0f) angle -= 360.0f;


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 10.0);  // poprawna perspektywa

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    gluLookAt(0.5f, 0.8f, 1.5f,  // kamera: trochê z góry i z przodu
        0.5f, 0.3f, 0.0f,  // cel: œrodek planszy (na pionek)
        0.0f, 1.0f, 0.0f); // oœ Y w górê

    // Przesuniêcie i skalowanie modelu 3D w uk³adzie 2D
   // glTranslatef(0.5f, 0.3f, 0.0f);  // Pozycja na ekranie 2D (wspó³rzêdne od 0 do 1)
    glTranslatef(x, y, 0.0f);
    // glRotatef(-10, 1.2f, 0.0f, 0.0f);
    // glRotatef(angle, 0.0f, 1.0f, 0.0f);    // Obrót wokó³ osi Y
    glScalef(0.17f, 0.17f, 0.17f);      // Skalowanie modelu
    GLfloat matAmbient[] = { 0.0f, 0.0f, 0.2f, 1.0f };  // jeszcze ciemniejszy niebieski
    GLfloat matDiffuse[] = { 0.0f, 0.0f, 0.4f, 1.0f };  // mniej intensywny
    GLfloat matSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // brak b³ysku
    GLfloat matShininess = 0.0f;                       // ca³kowicie matowy


    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

    draw();                  // Rysowanie modelu

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);



}