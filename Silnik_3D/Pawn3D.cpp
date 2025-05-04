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
    //gluPerspective(60.0, 1.0, 0.1, 10.0);  // poprawna perspektywa
    gluOrtho2D(0.0, 1.0, 0.0, 1.0); // Ustawienie ortograficzne (2D)

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //gluLookAt(x * 1.75f, y * 1.75f, 1.75f,  // kamera: trochê z góry i z przodu
    //    x* 1.75f, y * 1.75f, 0.0f,  // cel: œrodek planszy (na pionek)
    //    0.0f, 1.0f, 0.0f); // oœ Y w górê

    float xc = x + 0.1/2;// * 2.0f - 1.0f + 0.17/2;
    float yc = y + 0.07/2;// * 2.0f - 1.0f;
    float vx = 0.0;//0.8 * 1.75;
    float vy = 0.0;//0.8 * 1.75;
    
    gluLookAt(0, 0, 0.5f,  // kamera: trochê z góry i z przodu
        0, 0, 0.0f,  // cel: œrodek planszy (na pionek)
        0.0f, 1.0f, 0.0f); // oœ Y w górê

   

    // Przesuniêcie i skalowanie modelu 3D w uk³adzie 2D
   // glTranslatef(0.5f, 0.3f, 0.0f);  // Pozycja na ekranie 2D (wspó³rzêdne od 0 do 1)
    float x1 = 0.0;

    //std::cin >> x1;
    glTranslatef(xc,yc, 0.0f);
    // glRotatef(-10, 1.2f, 0.0f, 0.0f);
    angle = 25.0f;
    glRotatef(angle, 1.0f, 0.0f, 0.0f);    // Obrót wokó³ osi Y
    glScalef(0.1f, 0.1f, 0.1f);      // Skalowanie modelu
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

void Pawn3D::draw3DPawnAtRed(float x, float y)
{
    static float angle = 0.0f; // zapamiêtuje wartoœæ miêdzy wywo³aniami
    angle += 0.5f;
    if (angle >= 360.0f) angle -= 360.0f;


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
   // gluPerspective(60.0, 1.0, 0.1, 10.0);  // poprawna perspektywa
    gluOrtho2D(0.0, 1.0, 0.0, 1.0); // Ustawienie ortograficzne (2D)

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    /*
    gluLookAt(0.5f, 0.8f, 1.5f,  // kamera: trochê z góry i z przodu
        0.0f, 0.0f, 0.0f,  // cel: œrodek planszy (na pionek)
        0.0f, 0.0f, 0.0f); // oœ Y w górê
*/
    float xc = x + 0.1 / 2;// * 2.0f - 1.0f + 0.17/2;
    float yc = y + 0.07 / 2;// * 2.0f - 1.0f;
    float vx = 0.0;//0.8 * 1.75;
    float vy = 0.0;//0.8 * 1.75;
    gluLookAt(0, 0, 0.5f,  // kamera: troch? z góry i z przodu
        0, 0, 0.0f,  // cel: ?rodek planszy (na pionek)
        0.0f, 1.0f, 0.0f); // o? Y w gór?


    float x1 = 0.0;

    glTranslatef(xc, yc, 0.0f);
    angle = 25.0f;
    glRotatef(angle, 1.0f, 0.0f, 0.0f);    // Obrót wokó³ osi Y
    glScalef(0.1f, 0.1f, 0.1f);      // Skalowanie modelu
    GLfloat matAmbient[] = { 0.4f, 0.0f, 0.0f, 1.0f };// jeszcze ciemniejszy czerwony
    GLfloat matDiffuse[] = { 0.4f, 0.0f, 0.0f, 1.0f };  // mniej intensywny
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

void Pawn3D::draw3DPawnAtYellow(float x, float y)
{
    static float angle = 0.0f; // zapamiêtuje wartoœæ miêdzy wywo³aniami
    angle += 0.5f;
    if (angle >= 360.0f) angle -= 360.0f;


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
 
    gluOrtho2D(0.0, 1.0, 0.0, 1.0); // Ustawienie ortograficzne (2D)

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
   
    float xc = x + 0.1 / 2;// * 2.0f - 1.0f + 0.17/2;
    float yc = y + 0.07 / 2;// * 2.0f - 1.0f;
    float vx = 0.0;//0.8 * 1.75;
    float vy = 0.0;//0.8 * 1.75;
    gluLookAt(0, 0, 0.5f,  // kamera: troch? z góry i z przodu
        0, 0, 0.0f,  // cel: ?rodek planszy (na pionek)
        0.0f, 1.0f, 0.0f); // o? Y w gór?


    float x1 = 0.0;

    glTranslatef(xc, yc, 0.0f);
    angle = 25.0f;
    glRotatef(angle, 1.0f, 0.0f, 0.0f);    // Obrót wokó³ osi Y
    glScalef(0.1f, 0.1f, 0.1f);      // Skalowanie modelu
    GLfloat matAmbient[] = { 0.1f, 0.1f, 0.0f, 1.0f };  // bardzo ciemna ¿ó³æ w cieniu
    GLfloat matDiffuse[] = { 0.15f, 0.15f, 0.0f, 1.0f }; // bardzo ciemna ¿ó³æ w œwietle
    GLfloat matSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   // brak po³ysku
    GLfloat matShininess = 0.0f;                         // ca³kowicie matowy

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

void Pawn3D::draw3DPawnAtGreen(float x, float y)
{
    static float angle = 0.0f; // zapamiêtuje wartoœæ miêdzy wywo³aniami
    angle += 0.5f;
    if (angle >= 360.0f) angle -= 360.0f;


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    gluOrtho2D(0.0, 1.0, 0.0, 1.0); // Ustawienie ortograficzne (2D)

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    float xc = x + 0.1 / 2;// * 2.0f - 1.0f + 0.17/2;
    float yc = y + 0.07 / 2;// * 2.0f - 1.0f;
    float vx = 0.0;//0.8 * 1.75;
    float vy = 0.0;//0.8 * 1.75;
    gluLookAt(0, 0, 0.5f,  // kamera: troch? z góry i z przodu
        0, 0, 0.0f,  // cel: ?rodek planszy (na pionek)
        0.0f, 1.0f, 0.0f); // o? Y w gór?


    float x1 = 0.0;

    glTranslatef(xc, yc, 0.0f);
    angle = 25.0f;
    glRotatef(angle, 1.0f, 0.0f, 0.0f);    // Obrót wokó³ osi Y
    glScalef(0.1f, 0.1f, 0.1f);      // Skalowanie modelu
    GLfloat matAmbient[] = { 0.0f, 0.1f, 0.0f, 1.0f };  // bardzo ciemna zieleñ w cieniu
    GLfloat matDiffuse[] = { 0.0f, 0.15f, 0.0f, 1.0f }; // bardzo ciemna zieleñ w œwietle
    GLfloat matSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };  // brak po³ysku
    GLfloat matShininess = 0.0f;                        // matowy wygl¹d

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
