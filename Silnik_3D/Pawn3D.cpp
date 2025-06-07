#include "Pawn3D.h"
#include <GL/glew.h>
#include <iostream>

/**
 * @brief Konstruktor klasy Pawn3D.
 */
Pawn3D::Pawn3D() : scene(nullptr) {}

/**
 * @brief Destruktor klasy Pawn3D.
 */
Pawn3D::~Pawn3D() {}

/**
 * @brief £aduje model pionka 3D z pliku przy u¿yciu Assimp.
 *
 * @return true jeœli model za³adowano poprawnie, false w przeciwnym razie.
 */
bool Pawn3D::loadModel() {
    std::string path = "images/pionek.obj"; // <<--- Œcie¿ka do modelu 3D pionka

    scene = importer.ReadFile(path,
        aiProcess_Triangulate | aiProcess_GenSmoothNormals);

    if (!scene) {
        std::cerr << "B³¹d ³adowania modelu: " << importer.GetErrorString() << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief Rysuje model 3D pionka w aktualnej przestrzeni OpenGL.
 */
void Pawn3D::draw() const {
    if (!scene) return;

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh* mesh = scene->mMeshes[i];
        const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        aiColor3D diffuse(0.f, 0.f, 0.f);
        if (material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS) {
            float brightnessScale = 3.0f; 
            glColor3f(
                std::min(1.0f, diffuse.r * brightnessScale),
                std::min(1.0f, diffuse.g * brightnessScale),
                std::min(1.0f, diffuse.b * brightnessScale));
        }
        else {
            std::cout << "[WARN] Brak koloru w materiale – ustawiam szary domyslny." << std::endl;
            glColor3f(0.8f, 0.8f, 0.8f);
        }
        glBegin(GL_TRIANGLES);
        for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
            const aiFace& face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                unsigned int index = face.mIndices[k];
                aiVector3D vertex = mesh->mVertices[index];

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

/**
 * @brief Rysuje niebieski pionek 3D w zadanej pozycji na planszy.
 *
 * @param x Pozycja X na planszy (od 0 do 1).
 * @param y Pozycja Y na planszy (od 0 do 1).
 */
void Pawn3D::draw3DPawnAtBlue(float x, float y) {
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

    float xc = x + 0.1/2;
    float yc = y + 0.07/2;
    float vx = 0.0;
    float vy = 0.0;
    
    gluLookAt(0, 0, 0.5f,  // kamera: trochê z góry i z przodu
        0, 0, 0.0f,  // cel: œrodek planszy (na pionek)
        0.0f, 1.0f, 0.0f); // oœ Y w górê

    float x1 = 0.0;

    glTranslatef(xc,yc, 0.0f);
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

    draw();           
   
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

/**
 * @brief Rysuje czerwony pionek 3D w zadanej pozycji na planszy.
 *
 * @param x Pozycja X na planszy (od 0 do 1).
 * @param y Pozycja Y na planszy (od 0 do 1).
 */
void Pawn3D::draw3DPawnAtRed(float x, float y)
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
   
    float xc = x + 0.1 / 2;
    float yc = y + 0.07 / 2;
    float vx = 0.0;
    float vy = 0.0;
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

/**
 * @brief Rysuje ¿ó³ty pionek 3D w zadanej pozycji na planszy.
 *
 * @param x Pozycja X na planszy (od 0 do 1).
 * @param y Pozycja Y na planszy (od 0 do 1).
 */
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
   
    float xc = x + 0.1 / 2;
    float yc = y + 0.07 / 2;
    float vx = 0.0;
    float vy = 0.0;
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

/**
 * @brief Rysuje zielony pionek 3D w zadanej pozycji na planszy.
 *
 * @param x Pozycja X na planszy (od 0 do 1).
 * @param y Pozycja Y na planszy (od 0 do 1).
 */
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

    float xc = x + 0.1 / 2;
    float yc = y + 0.07 / 2;
    float vx = 0.0;
    float vy = 0.0;
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

/**
 * @brief Rysuje wszystkie pionki znajduj¹ce siê w domkach graczy.
 */
void Pawn3D::drawPawns()
{
    if (player3Name && !player3Name->empty() && greenHouse) {
        for (const auto& pos : *greenHouse) {
            draw3DPawnAtGreen(pos.first, pos.second);

        }
    }
    if (player4Name && !player4Name->empty() && yellowHouse) {
        for (const auto& pos : *yellowHouse) {
            // bitmapHandler.drawPionek(pos.first, pos.second, 0.08f, 0.08f, bitmapHandler.texture_pionek);
            draw3DPawnAtYellow(pos.first, pos.second);
        }
    }
    if (player1Name && !player1Name->empty() && redHouse) {
        // Rysowanie czerwonych pionków w domku
        for (const auto& pos : *redHouse) {
            //bitmapHandler.drawPionek(pos.first, pos.second, 0.08f, 0.08f, bitmapHandler.texture_pionek);
            draw3DPawnAtRed(pos.first, pos.second);
        }
    }
    if (player2Name && !player2Name->empty() && blueHouse) {
        // Rysowanie niebieskich pionków w domku
        for (const auto& pos : *blueHouse) {
            //bitmapHandler.drawPionek(pos.first, pos.second, 0.08f, 0.08f, bitmapHandler.texture_pionek2);
            draw3DPawnAtBlue(pos.first, pos.second);
        }
    }
}

/**
 * @brief Rysuje wszystkie pionki bêd¹ce aktualnie na planszy.
 */
void Pawn3D::drawPawnsPlay()
{
    if (player1Name && !player1Name->empty()) {
        if (*redPawnInPlay) {
            draw3DPawnAtRed(*pawnX, *pawnY);
        }
        if (*redPawnInPlay2) {
            draw3DPawnAtRed(*pawnX_R2, *pawnY_R2);
        }
        if (*redPawnInPlay3) {
            draw3DPawnAtRed(*pawnX_R3, *pawnY_R3);
        }
        if (*redPawnInPlay4) {
            draw3DPawnAtRed(*pawnX_R4, *pawnY_R4);
        }
    }
    if (player2Name && !player2Name->empty()) {
        if (*bluePawnInPlay) {
            draw3DPawnAtBlue(*pawnX2, *pawnY2);
        }
        if (*bluePawnInPlay2) {
            draw3DPawnAtBlue(*pawnX_B2, *pawnY_B2);
        }
        if (*bluePawnInPlay3) {
            draw3DPawnAtBlue(*pawnX_B3, *pawnY_B3);
        }
        if (*bluePawnInPlay4) {
            draw3DPawnAtBlue(*pawnX_B4, *pawnY_B4);
        }
    }
    if (player4Name && !player4Name->empty()) {
        if (*yellowPawnInPlay) {
            draw3DPawnAtYellow(*pawnX_YE, *pawnY_YE);
        }
        if (*yellowPawnInPlay2) {
            draw3DPawnAtYellow(*pawnX_YE2, *pawnY_YE2);
        }
        if (*yellowPawnInPlay3) {
            draw3DPawnAtYellow(*pawnX_YE3, *pawnY_YE3);
        }
        if (*yellowPawnInPlay4) {
            draw3DPawnAtYellow(*pawnX_YE4, *pawnY_YE4);
        }
    }
    if (player3Name && !player3Name->empty()) {
        if (*greenPawnInPlay) {
            draw3DPawnAtGreen(*pawnX_G, *pawnY_G);
        }
        if (*greenPawnInPlay2) {
            draw3DPawnAtGreen(*pawnX_G2, *pawnY_G2);
        }
        if (*greenPawnInPlay3) {
            draw3DPawnAtGreen(*pawnX_G3, *pawnY_G3);
        }
        if (*greenPawnInPlay4) {
            draw3DPawnAtGreen(*pawnX_G4, *pawnY_G4);
        }
    }
}

/**
 * @brief Ustawia wskaŸniki na nicki graczy.
 *
 * @param red Nick gracza czerwonego.
 * @param blue Nick gracza niebieskiego.
 * @param green Nick gracza zielonego.
 * @param yellow Nick gracza ¿ó³tego.
 */
void Pawn3D::setNicknames(const std::string* red, const std::string* blue,  
   const std::string* green, const std::string* yellow)  
{  
    player1Name = const_cast<std::string*>(red);
    player2Name = const_cast<std::string*>(blue);
    player3Name = const_cast<std::string*>(green);
    player4Name = const_cast<std::string*>(yellow);
}

/**
 * @brief Przypisuje wskaŸniki na pozycje i statusy wszystkich pionków w grze.
 *
 * Umo¿liwia zewnêtrznej klasie (np. Engine) aktualizacjê pozycji pionków.
 * Przyjmuje a¿ 32 wskaŸniki (4 graczy x 4 pionki x [bool + x + y]).
 */
void Pawn3D::PlayPawnsPointers(bool* RedPlay, float* pawnXred, float* pawnYred, bool* RedPlay2, float* pawnXred2, float* pawnYred2,
    bool* RedPlay3, float* pawnXred3, float* pawnYred3, bool* RedPlay4, float* pawnXred4, float* pawnYred4,
    bool* BluePlay, float* pawnXblue, float* pawnYblue, bool* BluePlay2, float* pawnXblue2, float* pawnYblue2,
    bool* BluePlay3, float* pawnXblue3, float* pawnYblue3, bool* BluePlay4, float* pawnXblue4, float* pawnYblue4, 
    bool* YellowPlay, float* pawnXyellow, float* pawnYyellow, bool* GreenPlay, float* pawnXgreen, float* pawnYgreen,
    bool* YellowPlay2, float* pawnXyellow2, float* pawnYyellow2, bool* YellowPlay3, float* pawnXyellow3, float* pawnYyellow3,
    bool* YellowPlay4, float* pawnXyellow4, float* pawnYyellow4, bool* GreenPlay2, float* pawnXgreen2, float* pawnYgreen2,
    bool* GreenPlay3, float* pawnXgreen3, float* pawnYgreen3, bool* GreenPlay4, float* pawnXgreen4, float* pawnYgreen4)
{
    redPawnInPlay = RedPlay;
    pawnX = pawnXred;
    pawnY = pawnYred;

    redPawnInPlay2 = RedPlay2;
    pawnX_R2 = pawnXred2;
    pawnY_R2 = pawnYred2;

    redPawnInPlay3 = RedPlay3;
    pawnX_R3 = pawnXred3;
    pawnY_R3 = pawnYred3;

    redPawnInPlay4 = RedPlay4;
    pawnX_R4 = pawnXred4;
    pawnY_R4 = pawnYred4;

    bluePawnInPlay = BluePlay;
    pawnX2 = pawnXblue;
    pawnY2 = pawnYblue;

    bluePawnInPlay2 = BluePlay2;
    pawnX_B2 = pawnXblue2;
    pawnY_B2 = pawnYblue2;

    bluePawnInPlay3 = BluePlay3;
    pawnX_B3 = pawnXblue3;
    pawnY_B3 = pawnYblue3;

    bluePawnInPlay4 = BluePlay4;
    pawnX_B4 = pawnXblue4;
    pawnY_B4 = pawnYblue4;

    yellowPawnInPlay = YellowPlay;
    pawnX_YE = pawnXyellow;
    pawnY_YE = pawnYyellow;

    yellowPawnInPlay2 = YellowPlay2;
    pawnX_YE2 = pawnXyellow2;
    pawnY_YE2 = pawnYyellow2;

    yellowPawnInPlay3 = YellowPlay3;
    pawnX_YE3 = pawnXyellow3;
    pawnY_YE3 = pawnYyellow3;

    yellowPawnInPlay4 = YellowPlay4;
    pawnX_YE4 = pawnXyellow4;
    pawnY_YE4 = pawnYyellow4;

    greenPawnInPlay = GreenPlay;
    pawnX_G = pawnXgreen;
    pawnY_G = pawnYgreen;

    greenPawnInPlay2 = GreenPlay2;
    pawnX_G2 = pawnXgreen2;
    pawnY_G2 = pawnYgreen2;

    greenPawnInPlay3 = GreenPlay3;
    pawnX_G3 = pawnXgreen3;
    pawnY_G3 = pawnYgreen3;

    greenPawnInPlay4 = GreenPlay4;
    pawnX_G4 = pawnXgreen4;
    pawnY_G4 = pawnYgreen4;
}

/**
 * @brief Ustawia wskaŸniki na wspó³rzêdne pól domków dla ka¿dego gracza.
 *
 * @param red Pozycje domku gracza czerwonego.
 * @param blue Pozycje domku gracza niebieskiego.
 * @param yellow Pozycje domku gracza ¿ó³tego.
 * @param green Pozycje domku gracza zielonego.
 */
void Pawn3D::setHousePointers(
   std::vector<std::pair<float, float>>* red,
   std::vector<std::pair<float, float>>* blue,
   std::vector<std::pair<float, float>>* yellow,
   std::vector<std::pair<float, float>>* green) {

   redHouse = red;
   blueHouse = blue;
   yellowHouse = yellow;
   greenHouse = green;
}
