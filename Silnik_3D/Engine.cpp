﻿#include "Engine.h"
#include "Cube.h"
#include "Triangle.h"
#include <array>

Cube cube;
Engine* Engine::instance = nullptr;

/**
 * @brief Konstruktor klasy Engine, inicjalizuje wszystkie ważne parametry.
 *
 * @param width Szerokość okna.
 * @param height Wysokość okna.
 * @param title Tytuł okna.
 * @param fps Liczba klatek na sekundę (FPS).
 */
Engine::Engine(int width, int height, const char* title, int fps)
    : windowWidth(width), windowHeight(height), windowTitle(title), clearColor{ 0.0f, 0.0f, 0.0f, 1.0f },
    cameraZ(5.0f), player(&triangle, &cube, &drawer),
    line(1.5f, 0.2f, 1.0f, 1.5f, 2.0f, 1.0f), rng(std::random_device{}()), dist(0, 5), frameRate(fps),
    isMyTurn(false) 
{
    initializePawnPaths();
    //currentLightingMode = LightingMode::DIRECTIONAL_LIGHT;
  

    // Ustawienie środka linii
    point.set(
        (line.getEndX() + line.getStartX()) / 2,
        (line.getEndY() - line.getStartY()) / 2,
        (line.getEndZ() - line.getStartZ()) / 2
    );
    PrimitiveDrawer::setShadingMode(currentShadingMode);// Ustawienie trybu cieniowania
}

/**
 * @brief Inicjalizacja okna i konfiguracja OpenGL.
 *
 * @param argc Liczba argumentów wiersza poleceń.
 * @param argv Tablica argumentów wiersza poleceń.
 */
void Engine::init(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow(windowTitle);

    glEnable(GL_DEPTH_TEST);
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

    glutDisplayFunc(renderCallback);
    glutIdleFunc(idleCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialKeyboardCallback);
    glutReshapeFunc(reshapeCallback);

    glutMouseFunc(mouseCallback);   
    glutMotionFunc(motionCallback); 
    glutMouseWheelFunc([](int wheel, int direction, int x, int y) {
        if (instance) {
            instance->onMouseWheel(wheel, direction, x, y);
        }
        });
}

/**
 * @brief Wyświetlenie komunikatu o zwycięzcy.
 *
 * @param winner Nazwa zwycięzcy.
 */
void Engine::showWinnerMessage(const std::string& winner) {
    // Konwersja napisu na szerokie znaki
    std::wstring wideWinner(winner.begin(), winner.end());
    std::wstring message = wideWinner + L" wygrywa!";

    // Wyświetlenie okna dialogowego
    int result = MessageBoxW(
        nullptr,               // Brak okna nadrzędnego
        message.c_str(),       // Treść komunikatu
        L"Koniec gry",         // Tytuł okna
        MB_OK | MB_ICONINFORMATION // Styl okna
    );

    // Sprawdzenie, czy okno zostało wyświetlone poprawnie
    if (result == 0) {
        std::cerr << "[ERROR] Nie udalo sie wyswietlic okna dialogowego!" << std::endl;
    }
    else {
        std::cout << "[INFO] Wyswietlono komunikat: " << winner << " wygrywa!" << std::endl;
    }
}

/**
 * @brief Ustawia kolor tła dla okna.
 *
 * @param r Składowa czerwonego koloru (0.0 - 1.0).
 * @param g Składowa zielonego koloru (0.0 - 1.0).
 * @param b Składowa niebieskiego koloru (0.0 - 1.0).
 * @param a Składowa przezroczystości (0.0 - 1.0).
 */
void Engine::setClearColor(float r, float g, float b, float a) {
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
}

/**
 * @brief Ustawia liczbę klatek na sekundę (FPS) w grze.
 *
 * @param fps Liczba klatek na sekundę. Musi być większa od 0.
 */
void Engine::setFrameRate(int fps) {
    if (fps <= 0) {
        frameRate = 1; // Minimalny FPS to 1
        std::cerr << "Frame rate must be greater than 0. Setting to minimum (1 FPS)." << std::endl;
    }
    else {
        frameRate = fps;
    }
}

/**
 * @brief Funkcja zegara dla cyklicznego odświeżania gry.
 *
 * @param value Argument (zwykle ustawiony na 0).
 */
void Engine::timer(int value) {
    if (instance) {  
        instance->render();
    }

    int interval = (instance && instance->frameRate > 0) ? 1000 / instance->frameRate : 0;

    if (interval > 0) {
        glutTimerFunc(interval, timer, 0);
    }
    else {
        glutPostRedisplay();
    }
}

/**
 * @brief Rozpoczyna główną pętlę gry.
 */
void Engine::run() {

        instance = this; // Ustawienie wskaźnika na obiekt

        if (frameRate > 0) {
            glutTimerFunc(1000 / frameRate, timer, 0); // Rozpoczęcie pętli czasowej
        }

        lastTime = glutGet(GLUT_ELAPSED_TIME);
        lastFrameTime = std::chrono::high_resolution_clock::now();
       
        glutMainLoop();
    
}

/**
 * @brief Zatrzymuje główną pętlę gry.
 */
void Engine::stop() {

    glutLeaveMainLoop();
}

/**
 * @brief Ustawia tekstury dla obiektów w grze.
 *
 * @param texturePaths Ścieżki do plików tekstur.
 */
void Engine::setTextures(const std::vector<std::string>& texturePaths) {
    if (!bitmapHandler.loadTextures(texturePaths)) {
        std::cerr << "Nie udało się załadować tekstur!" << std::endl;
    }
}

void drawText(float x, float y, const std::string& text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

/**
 * @brief Funkcja renderująca całą scenę gry.
 */
void Engine::render() {
   
    // Obliczanie czasu ramki
    auto currentFrameTime = std::chrono::high_resolution_clock::now();
    if (frameRate > 0) {
        std::chrono::duration<float> elapsedTime = currentFrameTime - lastFrameTime;
        float frameDuration = 1.0f / frameRate;

        // Pomijanie renderowania, jeśli czas ramki jeszcze nie upłynął
        if (elapsedTime.count() < frameDuration) {
            return;
        }
    }
    lastFrameTime = currentFrameTime;

    // Czyszczenie buforów
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
   
    //configureLighting();

    // Ustawienie kamery
    //gluLookAt(1.5, 1.5, cameraZ, 0.0, 0.0, 0.0, 0.0, 8.0, 0.0);
    gluLookAt(0.5, 0.5, cameraZ,  // nad środkiem planszy
        0.5, 0.5, 0.0,      // patrz na środek planszy
        0.0, 1.0, 0.0);     // oś Y jako góra


    // Rysowanie tła
    bitmapHandler.drawBackground();

    // Obracanie kostki
    if (isCubeRotating) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - rotationStartTime;

        // Kontrola czasu obrotu kostki
        if (elapsedTime < 2.0f) {
            cubeRotationAngle = elapsedTime * 180.0f; // Obrót kostki
        }
        else {
            isCubeRotating = false;    // Zakończenie obrotu kostki
          
            if ((isMyTurn && pawnStepsRemaining > 0) || (!isMyTurn && pawnStepsRemaining2 > 0)) {
                allowPawnSelection = true; // Pozwól na kliknięcie pionka
                std::cout << "[INFO] Kliknij pionka, ktorym chcesz sie poruszyc." << std::endl;
            }
            else if (!rolledSix) {
                // Tylko jeśli NIE wypadła 6 – zmień turę
                isMyTurn = !isMyTurn;
            }
            std::cout << "[DEBUG] Tura gracza: " << (isMyTurn ? "1" : "2") << std::endl;
       
        }


    }

    // Rysowanie kostki z obrotem
    glPushMatrix();
   // cube.draw();
    
    glPopMatrix();

    if (isPawnMoving && pawnStepsRemaining > 0) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - pawnLastMoveTime;
        if (elapsedTime >= 0.1f) {
            updatePawnPosition("red1");
            pawnLastMoveTime = currentTime;
        }
    }
    else if (isRedPawn2Moving && pawnStepsRemainingRed2 > 0) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - lastMoveTimeRed2;
        if (elapsedTime >= 0.1f) {
            updatePawnPosition("red2");
            lastMoveTimeRed2 = currentTime;
        }
    }
    else if (isRedPawn3Moving && pawnStepsRemainingRed3 > 0) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - lastMoveTimeRed3;
        if (elapsedTime >= 0.1f) {
            updatePawnPosition("red3");
            lastMoveTimeRed3 = currentTime;
        }
    }
    else if (isRedPawn4Moving && pawnStepsRemainingRed4 > 0) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - lastMoveTimeRed4;
        if (elapsedTime >= 0.1f) {
            updatePawnPosition("red4");
            lastMoveTimeRed4 = currentTime;
        }
    }
    else if (isPawnMoving2 && pawnStepsRemaining2 > 0) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - pawnLastMoveTime2;
        if (elapsedTime >= 0.1f) {
            updatePawnPosition("blue1");
            pawnLastMoveTime2 = currentTime;
        }
    }
    else if (isBluePawn2Moving && pawnStepsRemainingBlue2 > 0) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - lastMoveTimeBlue2;
        if (elapsedTime >= 0.1f) {
            updatePawnPosition("blue2");
            lastMoveTimeBlue2 = currentTime;
        }
    }
    else if (isBluePawn3Moving && pawnStepsRemainingBlue3 > 0) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - lastMoveTimeBlue3;
        if (elapsedTime >= 0.1f) {
            updatePawnPosition("blue3");
            lastMoveTimeBlue3 = currentTime;
        }
    }
    else if (isBluePawn4Moving && pawnStepsRemainingBlue4 > 0) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - lastMoveTimeBlue4;
        if (elapsedTime >= 0.1f) {
            updatePawnPosition("blue4");
            lastMoveTimeBlue4 = currentTime;
        }
    }


    // Rysowanie czerwonych pionków w domku
    for (const auto& pos : redHouse) {
        bitmapHandler.drawPionek(pos.first, pos.second, 0.08f, 0.08f, bitmapHandler.texture_pionek);
 
    }

    // Rysowanie niebieskich pionków w domku
    for (const auto& pos : blueHouse) {
        bitmapHandler.drawPionek(pos.first, pos.second, 0.08f, 0.08f, bitmapHandler.texture_pionek2);
 
    }

   // Rysowanie pionków tylko jeśli wyszły z domku
    if (redPawnInPlay) {

        bitmapHandler.drawPionek(pawnX, pawnY, 0.1f, 0.1f, bitmapHandler.texture_pionek);
    }
    if (redPawnInPlay2) {
        bitmapHandler.drawPionek(pawnX_R2, pawnY_R2, 0.1f, 0.1f, bitmapHandler.texture_pionek);
    }
    if (redPawnInPlay3) {
        bitmapHandler.drawPionek(pawnX_R3, pawnY_R3, 0.1f, 0.1f, bitmapHandler.texture_pionek);
    }
    if (redPawnInPlay4) {
        bitmapHandler.drawPionek(pawnX_R4, pawnY_R4, 0.1f, 0.1f, bitmapHandler.texture_pionek);
    }

    if (bluePawnInPlay) {
        bitmapHandler.drawPionek(pawnX2, pawnY2, 0.1f, 0.1f, bitmapHandler.texture_pionek2);
    }
    if (bluePawnInPlay2) {
        bitmapHandler.drawPionek(pawnX_B2, pawnY_B2, 0.1f, 0.1f, bitmapHandler.texture_pionek2);
    }
    if (bluePawnInPlay3) {
        bitmapHandler.drawPionek(pawnX_B3, pawnY_B3, 0.1f, 0.1f, bitmapHandler.texture_pionek2);
    }
    if (bluePawnInPlay4) {
        bitmapHandler.drawPionek(pawnX_B4, pawnY_B4, 0.1f, 0.1f, bitmapHandler.texture_pionek2);
    }
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0); // Ustawienie ortograficzne (2D)

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    if (diceInCenter) {
        cubeScreenPosX = 0.02f - cubeScreenScale / 2.0f; // środek planszy
    }
    else {
        cubeScreenPosX = isMyTurn ? 0.00f : 0.90f; // lewa lub prawa
    }
    cubeScreenPosY = firstThrowDone ? 0.32f : 0.90f;



    // Translacja do środka kostki, bo rysowana jest od -1 do 1 (czyli 2x większa)
    glTranslatef(cubeScreenPosX + cubeScreenScale, cubeScreenPosY + cubeScreenScale, 0.0f);
    glScalef(cubeScreenScale * 0.5f, cubeScreenScale * 0.5f, cubeScreenScale * 0.5f); // Dzielimy na pół, bo kostka ma 2x2x2 jednostki
    glRotatef(cubeRotationAngle, rotationAxisX, rotationAxisY, rotationAxisZ);

    // Rysowanie
    PrimitiveDrawer::drawCubeWithTexture(1.0f, 0.0f, 0.0f, bitmapHandler);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0); // Ustawienie ortograficzne (2D)

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f); 
    drawText(0.18f, 0.03f, player1Name);
    drawText(0.77f, 0.03f, player2Name);

    glPopMatrix(); 
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    // Rysowanie trójkąta
    glPushMatrix();
    //triangle.updateRotation();
   // triangle.draw();
    glPopMatrix();

    // Rysowanie linii i punktu
    glPushMatrix();
    //line.draw();
   // point.draw();
    glPopMatrix();

    // Ustawienie drugiej kamery
    //gluLookAt(3.0, 3.0, cameraZ, 5.0, 0.0, 0.0, 0.0, 3.0, 2.0);

    // Wymiana buforów
    glutSwapBuffers();
}

/**
 * @brief Obsługuje zdarzenia naciśnięcia klawiszy z klawiatury.
 *
 * Ta funkcja reaguje na naciśnięcie klawiszy, w tym:
 * - 'O'/'o' - przełącza tryb oświetlenia,
 * - 'Z'/'z' - przełącza tryb cieniowania,
 * - 'Esc' - zatrzymuje grę.
 *
 * @param key Naciśnięty klawisz.
 * @param x Pozycja kursora w osi X.
 * @param y Pozycja kursora w osi Y.
 */
void Engine::onKeyboard(unsigned char key, int x, int y) {
    if (key == 'O' || key == 'o') { // przełączenia oświetlenia
        switchLightingMode();
    }
    else if (key == 'Z' || key == 'z') { // przełączenia cieniowania
        switchShadingMode();
    }
    else if (key == 27) { // wyjście
        stop();
    }
    else if (key >= '1' && key <= '6') {
        manualDiceValue = key - '0';
        std::cout << "[DEBUG] Recznie ustawiono wartosc kostki na: " << manualDiceValue << std::endl;
    }

    player.handleInput(key);
    glutPostRedisplay();
}

/**
 * @brief Funkcja wywoływana przy naciśnięciu klawiszy specjalnych.
 *
 * Ta funkcja reaguje na klawisze specjalne, takie jak strzałki.
 *
 * @param key Kod klawisza.
 * @param x Pozycja kursora w osi X.
 * @param y Pozycja kursora w osi Y.
 */
void Engine::specialKeyboardCallback(int key, int x, int y) {
    if (instance) {
        instance->onSpecialKeyboard(key, x, y);
    }
}

/**
 * @brief Obsługuje wejście z klawiszy strzałek.
 *
 * Funkcja ta obsługuje naciśnięcie klawiszy strzałek i przetwarza je na odpowiednie akcje w grze.
 *
 * @param key Kod naciśniętego klawisza.
 * @param x Pozycja kursora w osi X.
 * @param y Pozycja kursora w osi Y.
 */
void Engine::onSpecialKeyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        player.handleInput('U'); 
        break;
    case GLUT_KEY_DOWN:
        player.handleInput('C');
        break;
    case GLUT_KEY_LEFT:
        player.handleInput('L');
        break;
    case GLUT_KEY_RIGHT:
        player.handleInput('R');
        break;
    }
    glutPostRedisplay();
}

void Engine::initializePawnPaths()
{
    redHouse = Paths::getRedHouse();
    blueHouse = Paths::getBlueHouse();
    redPath = Paths::getRedPath();
    bluePath = Paths::getBluePath();

}
void Engine::updatePawnPosition(const std::string& id) {
    
    std::array<PawnData, 8> pawns = { {
        {pawnX, pawnY, pawnStepsRemaining, pawnStepSize, bitmapHandler.texture_pionek, isPawnMoving, "Pionek czerwony", crossedBottomBoundary1, redHouse, currentStepRed, redPath, true, redHouseIndex},
        {pawnX2, pawnY2, pawnStepsRemaining2, pawnStepSize2, bitmapHandler.texture_pionek2, isPawnMoving2, "Pionek niebieski", crossedBottomBoundary2, blueHouse, currentStepBlue, bluePath, false, blueHouseIndex},
        {pawnX_R2, pawnY_R2, pawnStepsRemainingRed2, pawnStepSize, bitmapHandler.texture_pionek, isRedPawn2Moving, "Pionek czerwony 2", crossedBottomBoundary1, redHouse, currentStepRed2, redPath, true, redHouseIndex},
        {pawnX_B2, pawnY_B2, pawnStepsRemainingBlue2, pawnStepSize2, bitmapHandler.texture_pionek2, isBluePawn2Moving, "Pionek niebieski 2", crossedBottomBoundary2, blueHouse, currentStepBlue2, bluePath, false, blueHouseIndex},
        {pawnX_R3, pawnY_R3, pawnStepsRemainingRed3, pawnStepSize, bitmapHandler.texture_pionek, isRedPawn3Moving, "Pionek czerwony 3", crossedBottomBoundary1, redHouse, currentStepRed3, redPath, true, redHouseIndex},
        {pawnX_B3, pawnY_B3, pawnStepsRemainingBlue3, pawnStepSize2, bitmapHandler.texture_pionek2, isBluePawn3Moving, "Pionek niebieski 3", crossedBottomBoundary2, blueHouse, currentStepBlue3, bluePath, false, blueHouseIndex},
        {pawnX_R4, pawnY_R4, pawnStepsRemainingRed4, pawnStepSize, bitmapHandler.texture_pionek, isRedPawn4Moving, "Pionek czerwony 4", crossedBottomBoundary1, redHouse, currentStepRed4, redPath, true, redHouseIndex},
        {pawnX_B4, pawnY_B4, pawnStepsRemainingBlue4, pawnStepSize2, bitmapHandler.texture_pionek2, isBluePawn4Moving, "Pionek niebieski 4", crossedBottomBoundary2, blueHouse, currentStepBlue4, bluePath, false, blueHouseIndex}
    } };

    for (auto& pawn : pawns) {
        if ((id == "red1" && &pawn != &pawns[0]) ||
            (id == "blue1" && &pawn != &pawns[1]) ||
            (id == "red2" && &pawn != &pawns[2]) ||
            (id == "blue2" && &pawn != &pawns[3]) || 
            (id == "red3" && &pawn != &pawns[4]) ||
            (id == "blue3" && &pawn != &pawns[5])||
            (id == "red4" && &pawn != &pawns[6]) ||
            (id == "blue4" && &pawn != &pawns[7]))
        {
            continue;
        }

        // Pionek jeszcze nie wyszedl
        if (pawn.pawnStepsRemaining == -1) {
            pawn.isMoving = false;
            continue;
        }


        if (pawn.pawnStepsRemaining > 0 && pawn.currentStep == 0) {

            pawn.pawnX = pawn.path[0].first;
            pawn.pawnY = pawn.path[0].second;
            pawn.currentStep = 1;
            pawn.pawnStepsRemaining--;
            pawn.isMoving = true;
           
            continue;
        }

        if (pawn.pawnStepsRemaining > 0 && pawn.currentStep < pawn.path.size()) {

            // Sprawdzenie czy pionek może zbić przeciwnika (najpierw ustal, gdzie pionek ma się przemieścić)
            int nextStep = pawn.currentStep;
            float nextX = pawn.path[nextStep].first;
            float nextY = pawn.path[nextStep].second;

            // Sprawdzenie czy na tym polu stoi przeciwnik
            for (auto& other : pawns) {
                if (&other == &pawn) continue;

                std::string otherId;
                if (&other == &pawns[0]) otherId = "red1";
                else if (&other == &pawns[1]) otherId = "blue1";
                else if (&other == &pawns[2]) otherId = "red2";
                else if (&other == &pawns[3]) otherId = "blue2";
                else if (&other == &pawns[4]) otherId = "red3";
                else if (&other == &pawns[5]) otherId = "blue3";
                else if (&other == &pawns[6]) otherId = "red4";
                else if (&other == &pawns[7]) otherId = "blue4";

                // Nie bij pionków z własnej drużyny
                bool isEnemy = (pawn.isRed && !other.isRed) || (!pawn.isRed && other.isRed);
                if (!isEnemy) continue;

                if (other.pawnStepsRemaining >= 0 &&
                    std::abs(other.pawnX - nextX) < 0.01f &&
                    std::abs(other.pawnY - nextY) < 0.01f &&
                    pawn.pawnStepsRemaining == 1) {

                    std::cout << "[INFO] " << other.winnerName << " zostal zbity!" << std::endl;

                    other.pawnStepsRemaining = -1;
                    other.currentStep = 0;
                    other.isMoving = false;

                    if (other.isRed) {
                        if (otherId == "red1") {
                            redPawnInPlay = false;
                            other.house.insert(other.house.begin() + other.houseIndex, { 0.12f, 0.12f });
                        }
                        else if (otherId == "red2") {
                            redPawnInPlay2 = false;
                            other.house.insert(other.house.begin() + other.houseIndex, { 0.12f, 0.22f });
                        }
                        else if (otherId == "red3") {
                            redPawnInPlay3 = false;
                            other.house.insert(other.house.begin() + other.houseIndex, { 0.22f, 0.12f });
                        }
                        else if (otherId == "red4") {
                            redPawnInPlay4 = false;
                            other.house.insert(other.house.begin() + other.houseIndex, { 0.22f, 0.22f });
                        }
                    }
                    else {
                        if (otherId == "blue1") {
                            bluePawnInPlay = false;
                            other.house.insert(other.house.begin() + other.houseIndex, { 0.80f, 0.13f });
                        }
                        else if (otherId == "blue2") {
                            bluePawnInPlay2 = false;
                            other.house.insert(other.house.begin() + other.houseIndex, { 0.80f, 0.23f });
                        }
                        else if (otherId == "blue3") {
                            bluePawnInPlay3 = false;
                            other.house.insert(other.house.begin() + other.houseIndex, { 0.70f, 0.13f });
                        }
                        else if (otherId == "blue4") {
                            bluePawnInPlay4 = false;
                            other.house.insert(other.house.begin() + other.houseIndex, { 0.70f, 0.23f });
                        }
                    }
                }
            }
            // Dopiero teraz przesuwamy pionka na nowe pole
            pawn.pawnX = nextX;
            pawn.pawnY = nextY;

            pawn.currentStep++;
            pawn.pawnStepsRemaining--;

            if (pawn.pawnStepsRemaining == 0 || pawn.currentStep >= pawn.path.size()) {
                pawn.isMoving = false;
            }
            if (pawn.pawnStepsRemaining == 0 && !rolledSix) {
                isMyTurn = !isMyTurn;
                std::cout << "[DEBUG] Tura zmieniona! Teraz gra: " << (isMyTurn ? "Czerwony" : "Niebieski") << std::endl;
            }

            if (pawn.currentStep >= pawn.path.size()) {
                pawn.isMoving = false;
                pawn.pawnStepsRemaining = 0;
            }

            // Po zakończeniu ruchu, sprawdzamy czy któryś z pionków właśnie dobił do końca,
            // i czy **wszystkie 4 pionki** gracza osiągnęły cel.
            int redFinished = 0;
            int blueFinished = 0;

            for (const auto& other : pawns) {
                if (other.isRed && other.currentStep >= other.path.size()) {
                    redFinished++;
                }
                else if (!other.isRed && other.currentStep >= other.path.size()) {
                    blueFinished++;
                }
            }

            // Wygrana Czerwonego
            if (redFinished == 4 && pawn.isRed) {
                showWinnerMessage(player1Name); // albo pawn.winnerName
                resetGame();
                return;
            }

            // Wygrana Niebieskiego
            if (blueFinished == 4 && !pawn.isRed) {
                showWinnerMessage(player2Name); // albo pawn.winnerName
                resetGame();
                return;
            }


        }
    }
    
}

/**
 * @brief Resetuje stan gry, ustawiając pionki na początkowe pozycje.
 *
 * Funkcja ta ustawia pionki na pozycjach początkowych, resetuje liczbę pozostałych kroków oraz inne istotne zmienne.
 */
void Engine::resetGame() {
    //// Resetowanie pozycji pionków do początkowych współrzędnych
    //pawnX = 0.38f;
    //pawnY = 0.06f; 
    //pawnX2 = 0.85f;
    //pawnY2 = 0.4f; 

    //// Resetowanie liczby kroków
    //pawnStepsRemaining = 0;
    //pawnStepsRemaining2 = 0;

    //// Zatrzymanie ruchu pionków
    //isPawnMoving = false;
    //isPawnMoving2 = false;

    //// Resetowanie flag przekroczenia dolnej granicy
    //crossedBottomBoundary1 = false;
    //crossedBottomBoundary2 = false;

    //std::cout << "[DEBUG] Gra zostala zresetowana. Mozna grac ponownie." << std::endl;
}


void Engine::onMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float normalizedX = (float)x / glutGet(GLUT_WINDOW_WIDTH);
        float normalizedY = 1.0f - (float)y / glutGet(GLUT_WINDOW_HEIGHT);
       
        if (waitingForRedPawnClick && isMyTurn) {
            auto pos = redHouse[redHouseIndex];
            float size = 0.08f;

            if (normalizedX >= pos.first && normalizedX <= pos.first + size &&
                normalizedY >= pos.second && normalizedY <= pos.second + size) {

                if (!redPawnInPlay) {
                    redPawnInPlay = true;
                    pawnStepsRemaining = 1;
                    currentStepRed = 1;
                    pawnX = redPath[0].first;
                    pawnY = redPath[0].second;
                }
                else if (!redPawnInPlay2) {
                    redPawnInPlay2 = true;
                    pawnStepsRemainingRed2 = 1;
                    currentStepRed2 = 1;
                    pawnX_R2 = redPath[0].first;
                    pawnY_R2 = redPath[0].second;
                }
                else if (!redPawnInPlay3) {
                    redPawnInPlay3 = true;
                    pawnStepsRemainingRed3 = 1;
                    currentStepRed3 = 1;
                    pawnX_R3 = redPath[0].first;
                    pawnY_R3 = redPath[0].second;
                }
                else if (!redPawnInPlay4) {
                    redPawnInPlay4 = true;
                    pawnStepsRemainingRed4 = 1;
                    currentStepRed4 = 1;
                    pawnX_R4 = redPath[0].first;
                    pawnY_R4 = redPath[0].second;
                }

                redHouse.erase(redHouse.begin() + redHouseIndex);
                waitingForRedPawnClick = false;
                std::cout << "[DEBUG] Czerwony pionek zostal klikniety i wychodzi na plansze!" << std::endl;
                return;
            }
        }
        if (waitingForBluePawnClick && !isMyTurn) {
            auto pos = blueHouse[blueHouseIndex];
            float size = 0.08f;

            if (normalizedX >= pos.first && normalizedX <= pos.first + size &&
                normalizedY >= pos.second && normalizedY <= pos.second + size) {

                if (!bluePawnInPlay) {
                    bluePawnInPlay = true;
                    pawnStepsRemaining2 = 1;
                    currentStepBlue = 1;
                    pawnX2 = bluePath[0].first;
                    pawnY2 = bluePath[0].second;
                }
                else if (!bluePawnInPlay2) {
                    bluePawnInPlay2 = true;
                    pawnStepsRemainingBlue2 = 1;
                    currentStepBlue2 = 1;
                    pawnX_B2 = bluePath[0].first;
                    pawnY_B2 = bluePath[0].second;
                }
                else if (!bluePawnInPlay3) {
                    bluePawnInPlay3 = true;
                    pawnStepsRemainingBlue3 = 1;
                    currentStepBlue3 = 1;
                    pawnX_B3 = bluePath[0].first;
                    pawnY_B3 = bluePath[0].second;
                }
                else if (!bluePawnInPlay4) {
                    bluePawnInPlay4 = true;
                    pawnStepsRemainingBlue4 = 1;
                    currentStepBlue4 = 1;
                    pawnX_B4 = bluePath[0].first;
                    pawnY_B4 = bluePath[0].second;
                }

                blueHouse.erase(blueHouse.begin() + blueHouseIndex);
                waitingForBluePawnClick = false;
                isCubeRotating = false;
                std::cout << "[DEBUG] Niebieski pionek zostal klikniety i wychodzi na plansze!" << std::endl;
                return;
            }
        }
       
        if (allowPawnSelection && drawer.textureSet > 0) {
            float size = 0.2f;

            std::cout << "[DEBUG] Sprawdzam klikniecie w pionki..." << std::endl;

            if (isMyTurn) {
                if (redPawnInPlay &&
                    normalizedX >= pawnX && normalizedX <= pawnX + size &&
                    normalizedY >= pawnY && normalizedY <= pawnY + size) {

                    pawnStepsRemaining = drawer.textureSet;
                    isPawnMoving = true;
                    pawnLastMoveTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
                    std::cout << "[DEBUG] Kliknieto czerwonego pionka 1 - rusza!" << std::endl;
                    drawer.textureSet = 0;
                    allowPawnSelection = false;
                    return;
                }
                else if (redPawnInPlay2 &&
                    normalizedX >= pawnX_R2 && normalizedX <= pawnX_R2 + size &&
                    normalizedY >= pawnY_R2 && normalizedY <= pawnY_R2 + size) {

                    pawnStepsRemainingRed2 = drawer.textureSet;
                    isRedPawn2Moving = true;
                    lastMoveTimeRed2 = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
                    std::cout << "[DEBUG] Kliknieto czerwonego pionka 2 - rusza!" << std::endl;
                    drawer.textureSet = 0;
                    allowPawnSelection = false;
                    return;
                }
                else if (redPawnInPlay3 &&
                    normalizedX >= pawnX_R3 && normalizedX <= pawnX_R3 + size &&
                    normalizedY >= pawnY_R3 && normalizedY <= pawnY_R3 + size) {

                    pawnStepsRemainingRed3 = drawer.textureSet;
                    isRedPawn3Moving = true;
                    lastMoveTimeRed3 = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
                    std::cout << "[DEBUG] Kliknieto czerwonego pionka 3 - rusza!" << std::endl;
                    drawer.textureSet = 0;
                    allowPawnSelection = false;
                    return;
                }
                else if (redPawnInPlay4 &&
                    normalizedX >= pawnX_R4 && normalizedX <= pawnX_R4 + size &&
                    normalizedY >= pawnY_R4 && normalizedY <= pawnY_R4 + size) {

                    pawnStepsRemainingRed4 = drawer.textureSet;
                    isRedPawn4Moving = true;
                    lastMoveTimeRed4 = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
                    std::cout << "[DEBUG] Kliknieto czerwonego pionka 4 - rusza!" << std::endl;
                    drawer.textureSet = 0;
                    allowPawnSelection = false;
                    return;
                }
            }
            else {
                if (bluePawnInPlay &&
                    normalizedX >= pawnX2 && normalizedX <= pawnX2 + size &&
                    normalizedY >= pawnY2 && normalizedY <= pawnY2 + size) {

                    pawnStepsRemaining2 = drawer.textureSet;
                    isPawnMoving2 = true;
                    pawnLastMoveTime2 = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
                    std::cout << "[DEBUG] Kliknieto niebieskiego pionka 1 - rusza!" << std::endl;
                    drawer.textureSet = 0;
                    allowPawnSelection = false;
                    return;
                }
                else if (bluePawnInPlay2 &&
                    normalizedX >= pawnX_B2 && normalizedX <= pawnX_B2 + size &&
                    normalizedY >= pawnY_B2 && normalizedY <= pawnY_B2 + size) {

                    pawnStepsRemainingBlue2 = drawer.textureSet;
                    isBluePawn2Moving = true;
                    lastMoveTimeBlue2 = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
                    std::cout << "[DEBUG] Kliknieto niebieskiego pionka 2 - rusza!" << std::endl;
                    drawer.textureSet = 0;
                    allowPawnSelection = false;
                    return;
                }
                else if (bluePawnInPlay3 &&
                    normalizedX >= pawnX_B3 && normalizedX <= pawnX_B3 + size &&
                    normalizedY >= pawnY_B3 && normalizedY <= pawnY_B3 + size) {

                    pawnStepsRemainingBlue3 = drawer.textureSet;
                    isBluePawn3Moving = true;
                    lastMoveTimeBlue3 = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
                    std::cout << "[DEBUG] Kliknieto niebieskiego pionka 3 - rusza!" << std::endl;
                    drawer.textureSet = 0;
                    allowPawnSelection = false;
                    return;
                }
                else if (bluePawnInPlay4 &&
                    normalizedX >= pawnX_B4 && normalizedX <= pawnX_B4 + size &&
                    normalizedY >= pawnY_B4 && normalizedY <= pawnY_B4 + size) {

                    pawnStepsRemainingBlue4 = drawer.textureSet;
                    isBluePawn4Moving = true;
                    lastMoveTimeBlue4 = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
                    std::cout << "[DEBUG] Kliknieto niebieskiego pionka 4 - rusza!" << std::endl;
                    drawer.textureSet = 0;
                    allowPawnSelection = false;
                    return;
                }
            }

            std::cout << "[DEBUG] Kliknieto poza pionkami - brak ruchu" << std::endl;
        }


        // Sprawdzenie, czy kliknięto na kostkę
        if (isClickOnCube(x, y) && !isCubeRotating && !isPawnMoving && !isPawnMoving2) {
            isDragging = true;

            // Rozpoczęcie obrotu kostki
            isCubeRotating = true;
            diceInCenter = false;
            firstThrowDone = true;
            rotationStartTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; // Czas początkowy obrotu

            // Generowanie losowej liczby kroków dla pionka
            srand(static_cast<unsigned int>(time(nullptr)));
            //int steps = (rand() % 6) + 1;
            int steps = (manualDiceValue != -1) ? manualDiceValue : (rand() % 6 + 1);
            manualDiceValue = -1; // resetuj po użyciu

            rolledSix = (steps == 6);
            diceRolledForRed = isMyTurn;
                        diceRolledForBlue = !isMyTurn;
          
            if (isMyTurn) {
                if (steps == 6) {
                    if (redHouseIndex < redHouse.size()) {
                        waitingForRedPawnClick = true;
                        std::cout << "[INFO] Wyrzucono 6 – kliknij czerwonego pionka w domku." << std::endl;
                    }
                    if (redPawnInPlay || redPawnInPlay2 || redPawnInPlay3 || redPawnInPlay4) {
                        allowPawnSelection = true;
                        std::cout << "[INFO] Mozesz tez kliknac istniejacego czerwonego pionka i poruszyc go o " << steps << " kroków." << std::endl;
                    }
                }
                else if (redPawnInPlay || redPawnInPlay2 || redPawnInPlay3 || redPawnInPlay4) {
                    pawnStepsRemaining = steps;
                    std::cout << "[DEBUG] Ruch czerwonego pionka o " << steps << " krokow." << std::endl;
                }
            }
            else {
                if (steps == 6) {
                    if (blueHouseIndex < blueHouse.size()) {
                        waitingForBluePawnClick = true;
                        std::cout << "[INFO] Wyrzucono 6 – kliknij niebieskiego pionka w domku." << std::endl;
                    }
                    if (bluePawnInPlay || bluePawnInPlay2 || bluePawnInPlay3 || bluePawnInPlay4) {
                        allowPawnSelection = true;
                        std::cout << "[INFO] Mozesz też kliknac istniejacego niebieskiego pionka i poruszyc go o " << steps << " kroków." << std::endl;
                    }
                } else if (bluePawnInPlay || bluePawnInPlay2 || bluePawnInPlay3 || bluePawnInPlay4) {
                    pawnStepsRemaining2 = steps;
                    std::cout << "[DEBUG] Ruch niebieskiego pionka o " << steps << " krokow." << std::endl;
                }
            }
            // Ustawianie tekstury kostki w zależności od liczby kroków
            drawer.textureSet = steps;

            // Ustawianie osi obrotu kostki
            rotationAxisX = static_cast<float>(rand() % 2);
            rotationAxisY = static_cast<float>(rand() % 2);
            rotationAxisZ = (rotationAxisX == 0 && rotationAxisY == 0) ? 1.0f : 0.0f;
        }
    }
}

void Engine::setPlayerNicknames(const std::string& name1, const std::string& name2) {
    player1Name = name1;
    player2Name = name2;
}


/**
 * @brief Obsługuje kliknięcie myszką na kostce.
 *
 * Sprawdza, czy kliknięcie miało miejsce w odpowiednim obszarze kostki.
 * Rozpoczyna przeciąganie, jeśli kliknięcie jest wystarczająco blisko środka kostki.
 *
 * @param button Przycisk myszy.
 * @param state Stan przycisku.
 * @param x Pozycja kursora w osi X.
 * @param y Pozycja kursora w osi Y.
 */
void Engine::handleMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) { 
        float mouseWorldX = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2.0f - 1.0f;
        float mouseWorldY = 1.0f - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0f;

   
        mouseWorldX *= cameraZ;
        mouseWorldY *= cameraZ;

        if (state == GLUT_DOWN) { 

            float centerX = (line.getStartX() + line.getEndX()) / 2.0f;
            float centerY = (line.getStartY() + line.getEndY()) / 2.0f;

            const float CLICK_RADIUS = 0.25f * cameraZ;  
            if (std::abs(mouseWorldX - centerX) < CLICK_RADIUS &&
                std::abs(mouseWorldY - centerY) < CLICK_RADIUS) {
                isDraggingLine = true; 
                mouseStartX = mouseWorldX;
                mouseStartY = mouseWorldY;
                lineStartPosX = centerX;
                lineStartPosY = centerY;
            }
        }
        else if (state == GLUT_UP) { 
            isDraggingLine = false; 
        }
    }
}

/**
 * @brief Obsługuje ruchy myszki, jeśli aktywne jest przeciąganie.
 *
 * Funkcja ta aktualizuje pozycję obiektów w grze w zależności od ruchów myszki, np. przesuwanie linii.
 *
 * @param x Nowa pozycja kursora w osi X.
 * @param y Nowa pozycja kursora w osi Y.
 */
void Engine::handleMouseMotion(int x, int y) {
    if (isDraggingLine) { 
        
        float mouseWorldX = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2.0f - 1.0f;
        float mouseWorldY = 1.0f - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0f;

    
        mouseWorldX *= cameraZ;
        mouseWorldY *= cameraZ;

    
        float deltaX = mouseWorldX - mouseStartX;
        float deltaY = mouseWorldY - mouseStartY;

        mouseStartX = mouseWorldX;
        mouseStartY = mouseWorldY;

        line.setStart(line.getStartX() + deltaX, line.getStartY() + deltaY, line.getStartZ());
        line.setEnd(line.getEndX() + deltaX, line.getEndY() + deltaY, line.getEndZ());


        point.set((line.getStartX() + line.getEndX()) / 2.0f,
            (line.getStartY() + line.getEndY()) / 2.0f,
            point.getZ());


        glutPostRedisplay();
    }
}

/**
 * @brief Funkcja wywoływana w pętli gry, gdy nie ma innych zdarzeń.
 *
 * Ta funkcja jest wywoływana w przypadku braku aktywności w grze i aktualizuje stan gry na podstawie upływu czasu.
 */
void Engine::idleCallback() {
    if (instance) {
        float currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
        float elapsedTime = currentTime - instance->lastTime;
        instance->lastTime = static_cast<int>(currentTime);

        instance->player.update(elapsedTime);
        glutPostRedisplay(); 
    }
}

/**
 * @brief Funkcja wywoływana w celu rysowania sceny.
 *
 * Funkcja ta renderuje całą scenę, w tym obiekty, które są aktualnie widoczne.
 */
void Engine::renderCallback() {
    if (instance) {
        instance->render();
    }
}

/**
 * @brief Obsługuje zdarzenia związane z klawiaturą.
 *
 * Funkcja ta jest wywoływana przy naciśnięciu dowolnego klawisza.
 *
 * @param key Kod naciśniętego klawisza.
 * @param x Pozycja kursora w osi X.
 * @param y Pozycja kursora w osi Y.
 */
void Engine::keyboardCallback(unsigned char key, int x, int y) {
    instance->onKeyboard(key, x, y);
}

/**
 * @brief Obsługuje zdarzenia związane z myszką.
 *
 * Funkcja ta reaguje na kliknięcia myszką, sprawdzając, czy kliknięcie miało miejsce w odpowiednich obszarach.
 *
 * @param button Przycisk myszy.
 * @param state Stan przycisku myszy.
 * @param x Pozycja kursora w osi X.
 * @param y Pozycja kursora w osi Y.
 */
void Engine::mouseCallback(int button, int state, int x, int y) {
    if (instance) {
        instance->onMouse(button, state, x, y);
        instance->handleMouseClick(button, state, x, y);
    }
}

/**
 * Funkcja callback dla ruchu myszki. Wywoływana, gdy użytkownik porusza myszką w oknie gry.
 *
 * @param x Współrzędna X kursora myszy w oknie.
 * @param y Współrzędna Y kursora myszy w oknie.
 *
 * Funkcja ta sprawdza, czy istnieje instancja silnika gry (Engine) i jeśli tak, przekazuje
 * współrzędne ruchu myszy do metody `handleMouseMotion` odpowiedzialnej za dalsze
 * przetwarzanie i ewentualne aktualizowanie stanu gry w odpowiedzi na ruch myszy.
 */
void Engine::motionCallback(int x, int y) {
    if (instance) {
        instance->handleMouseMotion(x, y);
    }
}

/**
 * @brief Obsługuje zdarzenia związane z przesunięciem okna.
 *
 * Funkcja ta dostosowuje widok w zależności od rozmiaru okna gry.
 *
 * @param width Nowa szerokość okna.
 * @param height Nowa wysokość okna.
 */
void Engine::reshapeCallback(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);


    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error during reshape: " << gluErrorString(error) << std::endl;
    }
}

/**
 * @brief Sprawdza, czy kliknięcie miało miejsce na kostce.
 *
 * Funkcja ta przekształca współrzędne kliknięcia w układ współrzędnych OpenGL i sprawdza, czy kliknięcie
 * było w obrębie kostki.
 *
 * @param mouseX Pozycja kliknięcia w osi X.
 * @param mouseY Pozycja kliknięcia w osi Y.
 * @return true Jeśli kliknięcie było na kostce, false w przeciwnym razie.
 */
bool Engine::isClickOnCube(int mouseX, int mouseY) const {

    float windowWidthF = static_cast<float>(glutGet(GLUT_WINDOW_WIDTH));
    float windowHeightF = static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT));

    // Normalizujemy kliknięcie
    float normalizedX = static_cast<float>(mouseX) / windowWidthF;
    float normalizedY = 1.0f - (static_cast<float>(mouseY) / windowHeightF); // y jest odwrócone

    float margin = 0.02f; // albo 0.005f

    float cubeMinX = cubeScreenPosX - margin;
    float cubeMaxX = cubeScreenPosX + cubeScreenScale + margin;
    float cubeMinY = cubeScreenPosY - margin;
    float cubeMaxY = cubeScreenPosY + cubeScreenScale + margin;

    // Sprawdzenie, czy kliknięto w granicach prostokąta kostki
    return (normalizedX >= cubeMinX && normalizedX <= cubeMaxX &&
        normalizedY >= cubeMinY && normalizedY <= cubeMaxY);
}

/**
 * @brief Ustawia instancję silnika gry.
 *
 * Funkcja ta ustawia wskaźnik na instancję gry, umożliwiając dostęp do metod tej instancji w innych częściach kodu.
 *
 * @param engineInstance Wskaźnik na instancję gry.
 */
void Engine::setInstance(Engine* engineInstance) {
    instance = engineInstance;
}

/**
 * @brief Obsługuje przewijanie myszką (zoomowanie).
 *
 * Funkcja ta zmienia poziom przybliżenia kamery w zależności od kierunku przewijania kółka myszy.
 *
 * @param wheel Numer koła myszy.
 * @param direction Kierunek przewijania (1 - w górę, -1 - w dół).
 * @param x Pozycja kursora w osi X.
 * @param y Pozycja kursora w osi Y.
 */
void Engine::onMouseWheel(int wheel, int direction, int x, int y) {
 
    if (direction > 0) {
        cameraZ -= 1.0f; 
    }
    else if (direction < 0) {
        cameraZ += 1.0f; 
    }

    if (cameraZ < minCameraZ) {
        cameraZ = minCameraZ;
    }
    else if (cameraZ > maxCameraZ) {
        cameraZ = maxCameraZ;
    }

    glutPostRedisplay(); 
}

/**
 * @brief Przełącza tryb cieniowania.
 *
 * Funkcja ta zmienia tryb cieniowania pomiędzy płaskim a gładkim.
 */
void Engine::switchShadingMode() {
    if (currentShadingMode == ShadingMode::FLAT) {
        currentShadingMode = ShadingMode::SMOOTH;
    }
    else {
        currentShadingMode = ShadingMode::FLAT;
    }

    PrimitiveDrawer::setShadingMode(currentShadingMode);
}

/**
 * @brief Konfiguruje oświetlenie w grze.
 *
 * Funkcja ta ustawia odpowiedni typ oświetlenia (punktowe, kierunkowe, spot) w zależności od aktualnego trybu.
 */
void Engine::configureLighting() {
    glEnable(GL_LIGHTING); 

    switch (currentLightingMode) {
    case LightingMode::POINT_LIGHT: {
        glEnable(GL_LIGHT0);
        GLfloat pointLightPos[] = { 1.0f, 1.0f, 2.0f, 1.0f };  
        GLfloat pointLightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
        GLfloat pointLightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };  
        GLfloat pointLightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, pointLightPos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, pointLightDiffuse);
        glLightfv(GL_LIGHT0, GL_AMBIENT, pointLightAmbient);
        glLightfv(GL_LIGHT0, GL_SPECULAR, pointLightSpecular);
        break;
    }

    case LightingMode::DIRECTIONAL_LIGHT: {
        glEnable(GL_LIGHT1);

        GLfloat dirLightDir[] = { -0.3f, -1.0f, -0.7f, 0.0f }; // światło z lewego górnego rogu
        GLfloat dirLightDiffuse[] = { 0.9f, 0.85f, 0.7f, 1.0f }; // lekko ciepłe, jak Ludo Club
        GLfloat dirLightAmbient[] = { 0.25f, 0.25f, 0.25f, 1.0f }; // subtelna poświata
        GLfloat dirLightSpecular[] = { 0.6f, 0.6f, 0.6f, 1.0f }; // miękkie krawędzie

        glLightfv(GL_LIGHT1, GL_POSITION, dirLightDir);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, dirLightDiffuse);
        glLightfv(GL_LIGHT1, GL_AMBIENT, dirLightAmbient);
        glLightfv(GL_LIGHT1, GL_SPECULAR, dirLightSpecular);

        break; 
    }

    case LightingMode::SPOTLIGHT: {
        glEnable(GL_LIGHT2);
        GLfloat spotLightPos[] = { 0.0f, 0.0f, 5.0f, 1.0f };      
        GLfloat spotLightDir[] = { 0.0f, 0.0f, -1.0f };          
        GLfloat spotLightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
        GLfloat spotLightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };  
        GLfloat spotLightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
        glLightfv(GL_LIGHT2, GL_POSITION, spotLightPos);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotLightDir);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0f);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, spotLightDiffuse);
        glLightfv(GL_LIGHT2, GL_AMBIENT, spotLightAmbient);
        glLightfv(GL_LIGHT2, GL_SPECULAR, spotLightSpecular);
        break;
    }

    case LightingMode::NONE:
    default:
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        break;
    }
}

/**
 * @brief Przełącza tryb oświetlenia.
 *
 * Funkcja ta przełącza pomiędzy różnymi trybami oświetlenia (brak, punktowe, kierunkowe, spot).
 */
void Engine::switchLightingMode() {

    switch (currentLightingMode) {
    case LightingMode::NONE:
        currentLightingMode = LightingMode::POINT_LIGHT;
        break;
    case LightingMode::POINT_LIGHT:
        currentLightingMode = LightingMode::DIRECTIONAL_LIGHT;
        break;
    case LightingMode::DIRECTIONAL_LIGHT:
        currentLightingMode = LightingMode::SPOTLIGHT;
        break;
    case LightingMode::SPOTLIGHT:
        currentLightingMode = LightingMode::NONE;
        break;
    }

    configureLighting(); 
}