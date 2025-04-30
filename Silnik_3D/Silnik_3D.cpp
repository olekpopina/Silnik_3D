
#include "Engine.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>


int main(int argc, char** argv) {
    Menu menu(600, 600);

    if (!menu.show()) {
        return 0; // użytkownik zamknął menu bez kliknięcia "Start gry"
    }
       
    std::vector<std::string> texturePaths = {
        "images/tlo_chinczyk.png", "images/1.png", "images/2.png", "images/3.png",
        "images/4.png", "images/5.png", "images/6.png", "images/pionek1.png", "images/pionek2.png"
    };

    int frameRate = 60;
    Engine gameEngine(800, 600, "Game Engine", frameRate);
    Engine::setInstance(&gameEngine);
    gameEngine.setPlayerNicknames(menu.getNickname1(), menu.getNickname2());
    gameEngine.init(argc, argv);
    gameEngine.setClearColor(0.2f, 0.3f, 0.4f);
    gameEngine.setTextures(texturePaths);
    gameEngine.run();

    return 0;
}


/*
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

Assimp::Importer importer;
const aiScene* scene = nullptr;

// Ustawienia kamery
float angle = 0.0f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(
        7.0, 5.0, 7.0,  // Pozycja kamery: bardziej z boku, trochę z góry
        0.0, 0.0, 0.0,    // Patrzy w środek sceny
        0.0, 3.0, 0.0     // Kierunek "góry" – Y w górę
    );

    glRotatef(angle, 0, 1, 0); // Obracaj model

    if (scene) {
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
            const aiMesh* mesh = scene->mMeshes[i];
            const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            // Pobierz kolor materiału z MTL (Kd = diffuse)
            aiColor3D diffuse(0.f, 0.f, 0.f);
            if (material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS) {
                glColor3f(diffuse.r, diffuse.g, diffuse.b);
            }
            else {
                glColor3f(0.8f, 0.8f, 0.8f); // domyślny szary
            }

            glBegin(GL_TRIANGLES);
            for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
                const aiFace& face = mesh->mFaces[j];
                for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                    unsigned int index = face.mIndices[k];
                    aiVector3D vertex = mesh->mVertices[index];
                    glVertex3f(vertex.x, vertex.y, vertex.z);
                }
            }
            glEnd();
        }
    }

    glutSwapBuffers();
}

void idle() {
    angle += 0.3f; // animacja obrotu modelu
    if (angle > 360.0f) angle -= 360.0f;
    glutPostRedisplay();
}

void initGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Tło
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Model 3D z .obj i .mtl (FreeGLUT + Assimp)");

    if (glewInit() != GLEW_OK) {
        std::cerr << "Błąd GLEW!" << std::endl;
        return -1;
    }

    // Wczytaj model
    scene = importer.ReadFile("D:\\pionek.obj",
        aiProcess_Triangulate | aiProcess_GenSmoothNormals);

    if (!scene) {
        std::cerr << "Błąd ładowania modelu: " << importer.GetErrorString() << std::endl;
        return -1;
    }

    initGL();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
*/