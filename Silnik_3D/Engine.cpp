#include "Engine.h"
#include "Cube.h"
#include "Triangle.h"
#include <array>

Cube cube;
Engine* Engine::instance = nullptr;

Engine::Engine(int width, int height, const char* title)
    : windowWidth(width), windowHeight(height), windowTitle(title),clearColor{ 0.0f, 0.0f, 0.0f, 1.0f },
    cameraZ(5.0f), player(&triangle, &cube, &drawer), 
    line(1.5f, 0.2f, 1.0f, 1.5f, 2.0f, 1.0f), rng(std::random_device{}()), dist(0, 5) {
    point.set(
        (line.getEndX() + line.getStartX()) / 2,
        (line.getEndY() - line.getStartY()) / 2 ,
        (line.getEndZ() - line.getStartZ()) / 2
    );
}

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
        std::cerr << "[ERROR] Nie udało się wyświetlić okna dialogowego!" << std::endl;
    }
    else {
        std::cout << "[INFO] Wyświetlono komunikat: " << winner << " wygrywa!" << std::endl;
    }
}


void Engine::setClearColor(float r, float g, float b, float a) {
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
}

void Engine::setFrameRate(int fps) {
    if (fps <= 0) {
        frameRate = 1; // Minimalny FPS to 1
        std::cerr << "Frame rate must be greater than 0. Setting to minimum (1 FPS)." << std::endl;
    }
    else {
        frameRate = fps;
    }
}

void Engine::handleTimer()
{
    glutPostRedisplay(); // Wymuszenie renderowania
    glutTimerFunc(1000 / frameRate, timer, 0); // Rejestracja nowego zdarzenia
}

void Engine::timer(int value) {
    if (instance) {
        instance->render();
    }

    // Jeśli frameRate = 0, renderujemy bez ograniczeń
    int interval = (instance->frameRate > 0) ? 1000 / instance->frameRate : 0;

    if (interval > 0) {
        glutTimerFunc(interval, timer, 0);
    }
    else {
        // Bez ograniczeń wywołujemy render bezpośrednio
        glutPostRedisplay();
    }
}

void Engine::run() {

        instance = this; // Ustawienie wskaźnika na obiekt

        if (frameRate > 0) {
            glutTimerFunc(1000 / frameRate, timer, 0); // Rozpoczęcie pętli czasowej
        }

        lastTime = glutGet(GLUT_ELAPSED_TIME);
        lastFrameTime = std::chrono::high_resolution_clock::now();
       
        glutMainLoop();
    
}

void Engine::stop() {

    glutLeaveMainLoop();
}

void Engine::setTextures(const std::vector<std::string>& texturePaths) {
    if (!bitmapHandler.loadTextures(texturePaths)) {
        std::cerr << "Nie udało się załadować tekstur!" << std::endl;
    }
}

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

    // Ustawienie kamery
    gluLookAt(1.5, 1.5, cameraZ, 0.0, 0.0, 0.0, 0.0, 8.0, 0.0);

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
            isPawnMoving = true;       // Rozpoczęcie ruchu pierwszego pionka
            isPawnMoving2 = true;      // Rozpoczęcie ruchu drugiego pionka
            pawnLastMoveTime = currentTime;
            pawnLastMoveTime2 = currentTime;
            isMyTurn = !isMyTurn;      // Zmiana tury gracza
            std::cout << "[DEBUG] Tura gracza: " << (isMyTurn ? "1" : "2") << std::endl;
        }
    }

    // Rysowanie kostki z obrotem
    glPushMatrix();
    cube.draw();
    glRotatef(cubeRotationAngle, rotationAxisX, rotationAxisY, rotationAxisZ);  
    PrimitiveDrawer::drawCubeNew(1.0f, 0.0f, 0.0f, bitmapHandler);
    glPopMatrix();

    // Aktualizacja i rysowanie pionków
    if (isPawnMoving || isPawnMoving2) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

        // Ruch pierwszego pionka
        if (isPawnMoving) {
            float elapsedTime = currentTime - pawnLastMoveTime;
            if (elapsedTime >= 0.1f && pawnStepsRemaining > 0) {
                updatePawnPosition(); // Aktualizacja pozycji pionków
                pawnLastMoveTime = currentTime;
            }
            if (pawnStepsRemaining == 0) {
                isPawnMoving = false;
            }
        }

        // Ruch drugiego pionka
        if (isPawnMoving2) {
            float elapsedTime2 = currentTime - pawnLastMoveTime2;
            if (elapsedTime2 >= 0.1f && pawnStepsRemaining2 > 0) {
                updatePawnPosition(); // Wykorzystanie jednej funkcji
                pawnLastMoveTime2 = currentTime;
            }
            if (pawnStepsRemaining2 == 0) {
                isPawnMoving2 = false;
            }
        }
    }

    // Rysowanie pierwszego pionka
    bitmapHandler.drawPionek(pawnX, pawnY, 0.1f, 0.1f, bitmapHandler.texture_pionek);

    // Rysowanie drugiego pionka
    bitmapHandler.drawPionek(pawnX2, pawnY2, 0.1f, 0.1f, bitmapHandler.texture_pionek2);

    // Rysowanie trójkąta
    glPushMatrix();
    triangle.updateRotation();
    triangle.draw();
    glPopMatrix();

    // Rysowanie linii i punktu
    glPushMatrix();
    line.draw();
    point.draw();
    glPopMatrix();

    // Ustawienie drugiej kamery
    gluLookAt(3.0, 3.0, cameraZ, 5.0, 0.0, 0.0, 0.0, 3.0, 2.0);

    // Wymiana buforów
    glutSwapBuffers();
}


bool Engine::isPointNearLine(float px, float py, float x1, float y1, float x2, float y2, float threshold) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float lengthSq = dx * dx + dy * dy;
    float projection = ((px - x1) * dx + (py - y1) * dy) / lengthSq;

    if (projection < 0.0f || projection > 1.0f) {
        return false; 
    }
    float closestX = x1 + projection * dx;
    float closestY = y1 + projection * dy;

    float distSq = (px - closestX) * (px - closestX) + (py - closestY) * (py - closestY);
    return distSq <= threshold * threshold;
}

void Engine::onKeyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        stop();
    }
    player.handleInput(key);
    glutPostRedisplay();
}

void Engine::specialKeyboardCallback(int key, int x, int y) {
    if (instance) {
        instance->onSpecialKeyboard(key, x, y);
    }
}

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

void Engine::updatePawnPosition() {
    // Struktura zawierająca dane każdego pionka
    struct PawnData {
        float& pawnX;                 // Współrzędna X pionka
        float& pawnY;                 // Współrzędna Y pionka
        int& pawnStepsRemaining;      // Liczba pozostałych kroków
        float pawnStepSize;           // Rozmiar jednego kroku
        GLuint texture;               // Tekstura pionka
        bool& isMoving;               // Flaga wskazująca, czy pionek się porusza
        const std::string winnerName; // Nazwa gracza
        bool& crossedBottomBoundary;  // Czy pionek przekroczył dolną granicę
    };

    // Konfiguracja dwóch pionków
    std::array<PawnData, 2> pawns = { {
        {pawnX, pawnY, pawnStepsRemaining, pawnStepSize, bitmapHandler.texture_pionek, isPawnMoving, "Pionek czerwony", crossedBottomBoundary1},
        {pawnX2, pawnY2, pawnStepsRemaining2, pawnStepSize2, bitmapHandler.texture_pionek2, isPawnMoving2, "Pionek niebieski", crossedBottomBoundary2}
    } };

    // Stałe granice planszy
    const float LEFT_LIMIT = 0.1f;     // Lewa granica planszy
    const float RIGHT_LIMIT = 0.85f;   // Prawa granica planszy
    const float BOTTOM_LIMIT = 0.1f;   // Dolna granica planszy
    const float TOP_LIMIT = 0.85f;     // Górna granica planszy
    const float START_X = 0.1f;        // Początkowa współrzędna X
    const float START_Y = 0.1f;        // Początkowa współrzędna Y
    const float EPSILON = 0.01f;       // Tolerancja dla błędów obliczeń zmiennoprzecinkowych

    // Iteracja przez wszystkie pionki
    for (auto& pawn : pawns) {
        if (pawn.pawnStepsRemaining > 0) {
            // Logika poruszania się pionka po granicach planszy
            if (std::abs(pawn.pawnX - LEFT_LIMIT) < EPSILON && pawn.pawnY > BOTTOM_LIMIT) {
                pawn.pawnY -= pawn.pawnStepSize; // Ruch w dół
                if (pawn.pawnY < BOTTOM_LIMIT) pawn.pawnY = BOTTOM_LIMIT; // Zapobieganie wyjściu poza granicę
            }
            else if (std::abs(pawn.pawnY - BOTTOM_LIMIT) < EPSILON && pawn.pawnX < RIGHT_LIMIT) {
                pawn.pawnX += pawn.pawnStepSize; // Ruch w prawo
                if (pawn.pawnX > RIGHT_LIMIT) pawn.pawnX = RIGHT_LIMIT; // Zapobieganie wyjściu poza granicę
            }
            else if (std::abs(pawn.pawnX - RIGHT_LIMIT) < EPSILON && pawn.pawnY < TOP_LIMIT) {
                pawn.pawnY += pawn.pawnStepSize; // Ruch w górę
                if (pawn.pawnY > TOP_LIMIT) pawn.pawnY = TOP_LIMIT; // Zapobieganie wyjściu poza granicę
            }
            else if (std::abs(pawn.pawnY - TOP_LIMIT) < EPSILON && pawn.pawnX > LEFT_LIMIT) {
                pawn.pawnX -= pawn.pawnStepSize; // Ruch w lewo
                if (pawn.pawnX < LEFT_LIMIT) pawn.pawnX = LEFT_LIMIT; // Zapobieganie wyjściu poza granicę
            }

            // Sprawdzenie, czy pionek przekroczył dolną granicę
            if (std::abs(pawn.pawnY - BOTTOM_LIMIT) < EPSILON) {
                pawn.crossedBottomBoundary = true;
            }

            // Sprawdzenie, czy pionek wrócił na pozycję początkową (X = 0.1, Y = 0.1)
            if (pawn.crossedBottomBoundary &&
                std::abs(pawn.pawnX - START_X) < EPSILON &&
                std::abs(pawn.pawnY - START_Y) < EPSILON) {
                showWinnerMessage(pawn.winnerName); // Wyświetlenie komunikatu o zwycięstwie
                resetGame(); // Reset gry
                return;
            }

            pawn.pawnStepsRemaining--; // Zmniejszenie liczby pozostałych kroków
        }

        // Zatrzymanie ruchu, jeśli pionek zakończył wszystkie kroki
        if (pawn.pawnStepsRemaining == 0) {
            pawn.isMoving = false;
        }
    }
}

void Engine::resetGame() {
    // Resetowanie pozycji pionków do początkowych współrzędnych
    pawnX = 0.1f;
    pawnY = 0.1f;  // Reset do pozycji startowej (0.1, 0.1)
    pawnX2 = 0.1f;
    pawnY2 = 0.1f; // Reset do pozycji startowej (0.1, 0.1)

    // Resetowanie liczby kroków
    pawnStepsRemaining = 0;
    pawnStepsRemaining2 = 0;

    // Zatrzymanie ruchu pionków
    isPawnMoving = false;
    isPawnMoving2 = false;

    // Resetowanie flag przekroczenia dolnej granicy
    crossedBottomBoundary1 = false;
    crossedBottomBoundary2 = false;

    std::cout << "[DEBUG] Gra została zresetowana. Można grać ponownie." << std::endl;
}




// Funkcja obsługująca kliknięcie myszką
void Engine::onMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Sprawdzenie, czy kliknięto na kostkę
        if (isClickOnCube(x, y) && !isCubeRotating && !isPawnMoving && !isPawnMoving2) {
            isDragging = true;

            // Rozpoczęcie obrotu kostki
            isCubeRotating = true;
            rotationStartTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; // Czas początkowy obrotu

            // Generowanie losowej liczby kroków dla pionka
            srand(static_cast<unsigned int>(time(nullptr)));
            int steps = (rand() % 6) + 1;

            if (isMyTurn) {
                pawnStepsRemaining = steps;
                std::cout << "[DEBUG] Wylosowano dla pionka 1: " << steps << std::endl;
            }
            else {
                pawnStepsRemaining2 = steps;
                std::cout << "[DEBUG] Wylosowano dla pionka 2: " << steps << std::endl;
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


void Engine::handleMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) { // Left mouse button
        // Convert mouse coordinates to world space
        float mouseWorldX = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2.0f - 1.0f;
        float mouseWorldY = 1.0f - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0f;

        // Scale for zoom level
        mouseWorldX *= cameraZ;
        mouseWorldY *= cameraZ;

        if (state == GLUT_DOWN) { // Button pressed
            // Calculate the center of the line
            float centerX = (line.getStartX() + line.getEndX()) / 2.0f;
            float centerY = (line.getStartY() + line.getEndY()) / 2.0f;

            // Check if the click is near the line's center
            const float CLICK_RADIUS = 0.25f * cameraZ; // Tolerance based on zoom
            if (std::abs(mouseWorldX - centerX) < CLICK_RADIUS &&
                std::abs(mouseWorldY - centerY) < CLICK_RADIUS) {
                isDraggingLine = true; // Enable dragging
                mouseStartX = mouseWorldX;
                mouseStartY = mouseWorldY;
                lineStartPosX = centerX;
                lineStartPosY = centerY;
            }
        }
        else if (state == GLUT_UP) { // Button released
            isDraggingLine = false; // Disable dragging
        }
    }
}

// Obsługa ruchu myszką
void Engine::handleMouseMotion(int x, int y) {
    if (isDraggingLine) { // If dragging is active
        // Convert mouse coordinates to world space
        float mouseWorldX = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2.0f - 1.0f;
        float mouseWorldY = 1.0f - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2.0f;

        // Scale for zoom level
        mouseWorldX *= cameraZ;
        mouseWorldY *= cameraZ;

        // Calculate the offset to keep the line center under the mouse
        float deltaX = mouseWorldX - mouseStartX;
        float deltaY = mouseWorldY - mouseStartY;

        // Update mouse start position for continuous dragging
        mouseStartX = mouseWorldX;
        mouseStartY = mouseWorldY;

        // Adjust the line's start and end points
        line.setStart(line.getStartX() + deltaX, line.getStartY() + deltaY, line.getStartZ());
        line.setEnd(line.getEndX() + deltaX, line.getEndY() + deltaY, line.getEndZ());

        // Update the center point
        point.set((line.getStartX() + line.getEndX()) / 2.0f,
            (line.getStartY() + line.getEndY()) / 2.0f,
            //(line.getStartZ() + line.getEndZ()) / 2.0f);
            point.getZ());

        // Redraw the scene
        glutPostRedisplay();
    }
}

void Engine::idleCallback() {
    if (instance) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME);
        float elapsedTime = currentTime - instance->lastTime;

        instance->lastTime = currentTime;

        instance->player.update(elapsedTime);
        glutPostRedisplay(); // Оновлення екрану, якщо є активний рух
    }
}

void Engine::renderCallback() {
    if (instance) {
        instance->render();
    }
}

void Engine::keyboardCallback(unsigned char key, int x, int y) {
    instance->onKeyboard(key, x, y);
}

void Engine::mouseCallback(int button, int state, int x, int y) {
    if (instance) {
        instance->onMouse(button, state, x, y);
        instance->handleMouseClick(button, state, x, y);
    }
}

void Engine::motionCallback(int x, int y) {
    if (instance) {
        instance->handleMouseMotion(x, y);
    }
}

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


// Funkcja sprawdzająca, czy kliknięcie było na kostce
bool Engine::isClickOnCube(int mouseX, int mouseY) {
    // Convert mouse coordinates to normalized OpenGL coordinates [-1, 1]
    float normalizedX = (float)mouseX / glutGet(GLUT_WINDOW_WIDTH) * 2.0f - 1.0f;
    float normalizedY = 1.0f - (float)mouseY / glutGet(GLUT_WINDOW_HEIGHT) * 2.0f;

    // Adjust normalized coordinates for the zoom level (cameraZ)
    float worldX = normalizedX * cameraZ;
    float worldY = normalizedY * cameraZ;

    // Cube's size and position relative to the world space
    float cubeSize = 1.0f * cameraZ; // Adjust cube size based on zoom
    float cubeCenterX = 0.0f;        // Cube's center in world space X
    float cubeCenterY = 0.0f;        // Cube's center in world space Y

    // Calculate cube boundaries in world space
    float cubeMinX = cubeCenterX - 0.5f * cubeSize;
    float cubeMaxX = cubeCenterX + 0.5f * cubeSize;
    float cubeMinY = cubeCenterY - 0.5f * cubeSize;
    float cubeMaxY = cubeCenterY + 0.5f * cubeSize;

    // Check if the click is inside the cube's boundaries
    return (worldX >= cubeMinX && worldX <= cubeMaxX &&
        worldY >= cubeMinY && worldY <= cubeMaxY);
}

void Engine::setInstance(Engine* engineInstance) {
    instance = engineInstance;
}
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