#include "Engine.h"
#include "Cube.h"
#include "Triangle.h"



Cube cube;
Engine* Engine::instance = nullptr;


Engine::Engine(int width, int height, const char* title)
    : windowWidth(width), windowHeight(height), windowTitle(title),clearColor{ 0.0f, 0.0f, 0.0f, 1.0f },
    lastMouseX(0), lastMouseY(0), lastTime(0),
    isDragging(false), cameraZ(5.0f), player(&triangle, &cube, &drawer), 
    pointX(0.5f), pointY(0.5f), pointZ(0.5f),
    line(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f), rng(std::random_device{}()), dist(0, 5) {

   
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
    glutMouseFunc(mouseCallback);
    glutMotionFunc(motionCallback);
    glutReshapeFunc(reshapeCallback);

    glutIdleFunc(idleCallback);
    glutSpecialFunc(specialKeyboardCallback);
    
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

  
    reset();
}
void Engine::reset() {

    clear();           

    isGameRunning = true;    
    std::cout << "[INFO] Gra została zresetowana do stanu początkowego." << std::endl;
}

void Engine::clear() {
    
    pawnX = 0.1f;
    pawnY = 0.1f;
    pawnX2 = 0.1f;
    pawnY2 = 0.1f;
    pawnStepsRemaining = 0;
    pawnStepsRemaining2 = 0;
    isPawnMoving = false;
    isPawnMoving2 = false;

    isCubeRotating = false;
    cubeRotationAngle = 0.0f;

    
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

void Engine::setTextures(const std::string& backgroundPath, const std::string& cubePath2, const std::string& cubePath3, const std::string& cubePath4, const std::string& cubePath5, const std::string& cubePath6, const std::string& cubePath7, const std::string& pionek, const std::string& pionek2) {
    if (!bitmapHandler.loadTextures(backgroundPath, cubePath2, cubePath3, cubePath4, cubePath5, cubePath6, cubePath7, pionek, pionek2)) {
        std::cerr << "Nie udało się załadować tekstur!" << std::endl;
    }
}




void Engine::render() {

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


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(1.5, 1.5, cameraZ, 0.0, 0.0, 0.0, 0.0, 8.0, 0.0);

    bitmapHandler.drawBackground();
    
    if (isCubeRotating) {
       float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
       float elapsedTime = currentTime - rotationStartTime;

        if (elapsedTime < 2.0f) {
            cubeRotationAngle = elapsedTime * 180.0f; // Обертання кубика
        }
        else {
          
            isCubeRotating = false; // Завершення обертання
            isPawnMoving = true;    // Початок руху пішака
            isPawnMoving2 = true;
            pawnLastMoveTime = currentTime;
            pawnLastMoveTime2 = currentTime;
            isMyTurn = !isMyTurn;
            std::cout << "[DEBUG] Tura gracza: " << (isMyTurn ? "1" : "2") << std::endl;
        }
    }
    
  
    // Обертання кубика
    glPushMatrix();
    cube.draw();
    glRotatef(cubeRotationAngle, rotationAxisX, rotationAxisY, rotationAxisZ);
  
   
        PrimitiveDrawer::drawCubeNew(1.0f, 0.0f, 0.0f, bitmapHandler);
    
    glPopMatrix();

    // Рух пішака
    if (isPawnMoving) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - pawnLastMoveTime;

        if (elapsedTime >= 0.1f && pawnStepsRemaining > 0) {
            updatePawnPosition();
            pawnLastMoveTime = currentTime;
        }

        if (pawnStepsRemaining == 0) {
            isPawnMoving = false;
        }
      
    }
    bitmapHandler.drawPionek(pawnX, pawnY, 0.1f, 0.1f);
    // Рух пішака
    if (isPawnMoving2) {
        float currentTime2 = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime2 = currentTime2 - pawnLastMoveTime2;

        if (elapsedTime2 >= 0.1f && pawnStepsRemaining2 > 0) {
            updatePawnPosition2();
            pawnLastMoveTime2 = currentTime2;
        }

        if (pawnStepsRemaining2 == 0) {
            isPawnMoving2 = false;
        }
    }

    //bitmapHandler.drawPionek(pawnX, pawnY, 0.1f, 0.1f);
    bitmapHandler.drawPionek2(pawnX2, pawnY2, 0.1f, 0.1f);

    glPushMatrix();
    triangle.updateRotation(deltaTime);
    triangle.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(linePosX, linePosY, 0.0f);
    line.draw();
    PrimitiveDrawer::drawPoint(pointX, pointY, pointZ, 8.0f);
    glPopMatrix();

    gluLookAt(3.0, 3.0, cameraZ, 5.0, 0.0, 0.0, 0.0, 3.0, 2.0);

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
    const float LEFT_LIMIT = 0.1f;   // Lewa granica
    const float RIGHT_LIMIT = 0.85f; // Prawa granica
    const float BOTTOM_LIMIT = 0.1f; // Dolna granica
    const float TOP_LIMIT = 0.85f;   // Górna granica
    const float EPSILON = 0.01f;     // Tolerancja błędu dla porównań
    const float START_X = 0.1f;  // Punkt początkowy X
    const float START_Y = 0.85f; // Punkt początkowy Y

    if (pawnStepsRemaining > 0) {
        // Jeśli pionek znajduje się w lewym górnym rogu, zaczyna poruszać się w dół
        if (std::abs(pawnX - LEFT_LIMIT) < EPSILON && std::abs(pawnY - TOP_LIMIT) < EPSILON) {
            pawnY -= pawnStepSize; // Ruch w dół
        }
        // Jeśli pionek znajduje się na dole i porusza się w prawo
        else if (std::abs(pawnY - BOTTOM_LIMIT) < EPSILON && pawnX < RIGHT_LIMIT) {
            pawnX += pawnStepSize; // Ruch w prawo
        }
        // Jeśli pionek znajduje się po prawej i porusza się w górę
        else if (std::abs(pawnX - RIGHT_LIMIT) < EPSILON && pawnY < TOP_LIMIT) {
            pawnY += pawnStepSize; // Ruch w górę
        }
        // Jeśli pionek znajduje się na górze i porusza się w lewo
        else if (std::abs(pawnY - TOP_LIMIT) < EPSILON && pawnX > LEFT_LIMIT) {
            pawnX -= pawnStepSize; // Ruch w lewo
        }
        // Jeśli pionek znajduje się po lewej i porusza się w dół
        else if (std::abs(pawnX - LEFT_LIMIT) < EPSILON && pawnY > BOTTOM_LIMIT) {
            pawnY -= pawnStepSize; // Ruch w dół
            showWinnerMessage("Pionek czerwony");
        }

        // Zmniejszenie liczby pozostałych kroków
        pawnStepsRemaining--;
        std::cout << "[DEBUG] Moving: Pawn X = " << pawnX
            << ", Pawn Y = " << pawnY
            << ", Steps left = " << pawnStepsRemaining << std::endl;
    }
    
    // Zakończenie ruchu
    if (pawnStepsRemaining == 0) {
        isPawnMoving = false;
        std::cout << "[DEBUG] Pawn movement completed!" << std::endl;
    }
}

void Engine::updatePawnPosition2() {
    const float LEFT_LIMIT = 0.1f;   // Lewa granica
    const float RIGHT_LIMIT = 0.85f; // Prawa granica
    const float BOTTOM_LIMIT = 0.1f; // Dolna granica
    const float TOP_LIMIT = 0.85f;   // Górna granica
    const float EPSILON = 0.01f;     // Tolerancja błędu dla porównań
    const float START_X = 0.1f;  // Punkt początkowy X
    const float START_Y = 0.85f; // Punkt początkowy Y

    if (pawnStepsRemaining2 > 0) {
        // Jeśli pionek znajduje się w lewym górnym rogu, zaczyna poruszać się w dół
        if (std::abs(pawnX2 - LEFT_LIMIT) < EPSILON && std::abs(pawnY2 - TOP_LIMIT) < EPSILON) {
            pawnY2 -= pawnStepSize2; // Ruch w dół
        }
        // Jeśli pionek znajduje się na dole i porusza się w prawo
        else if (std::abs(pawnY2 - BOTTOM_LIMIT) < EPSILON && pawnX2 < RIGHT_LIMIT) {
            pawnX2 += pawnStepSize2; // Ruch w prawo
        }
        // Jeśli pionek znajduje się po prawej i porusza się w górę
        else if (std::abs(pawnX2 - RIGHT_LIMIT) < EPSILON && pawnY2 < TOP_LIMIT) {
            pawnY2 += pawnStepSize2; // Ruch w górę
        }
        // Jeśli pionek znajduje się na górze i porusza się w lewo
        else if (std::abs(pawnY2 - TOP_LIMIT) < EPSILON && pawnX2 > LEFT_LIMIT) {
            pawnX2 -= pawnStepSize2; // Ruch w lewo
        }
        // Jeśli pionek znajduje się po lewej i porusza się w dół
        else if (std::abs(pawnX2 - LEFT_LIMIT) < EPSILON && pawnY2 > BOTTOM_LIMIT) {
            pawnY2 -= pawnStepSize2; // Ruch w dół
            showWinnerMessage("Pionek niebieski");
        }

        // Zmniejszenie liczby pozostałych kroków
        pawnStepsRemaining2--;
        std::cout << "[DEBUG] Moving: Pawn X2 = " << pawnX2
            << ", Pawn Y = " << pawnY2
            << ", Steps left = " << pawnStepsRemaining2 << std::endl;
    }
    
    // Zakończenie ruchu
    if (pawnStepsRemaining2 == 0) {
        isPawnMoving2 = false;
        std::cout << "[DEBUG] Pawn movement completed!" << std::endl;
    }
}

void Engine::onMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !isCubeRotating && !isPawnMoving && !isPawnMoving2) {

        isDragging = true;

        // Початок обертання кубика
        isCubeRotating = true;
        rotationStartTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

        // Генерація випадкової кількості кроків для пішака
        srand(static_cast<unsigned int>(time(nullptr)));
        int steps = (rand() % 6) + 1;
        //pawnStepsRemaining = steps;
        //pawnStepsRemaining2 = steps;

        if (isMyTurn) {
            pawnStepsRemaining = steps;
            std::cout << "[DEBUG] Wylosowano dla pionka 1: " << steps << std::endl;
            //isPawnMoving = true;


        }
        else {
            pawnStepsRemaining2 = steps;
            std::cout << "[DEBUG] Wylosowano dla pionka 2: " << steps << std::endl;
            //isPawnMoving2 = true;
        }

        //std::cout << "[DEBUG] Wylosowano: " << steps << std::endl;




        if (steps == 1) {
            drawer.textureSet = 1;

        }
        else if (steps == 2) {
            drawer.textureSet = 2;
        }
        else if (steps == 3) {
            drawer.textureSet = 3;
        }
        else if (steps == 4) {
            drawer.textureSet = 4;
        }
        else if (steps == 5) {
            drawer.textureSet = 5;
        }
        else if (steps == 6) {
            drawer.textureSet = 6;
        }

        // Встановлення осей для обертання кубика
        rotationAxisX = static_cast<float>(rand() % 2);
        rotationAxisY = static_cast<float>(rand() % 2);
        rotationAxisZ = (rotationAxisX == 0 && rotationAxisY == 0) ? 1.0f : 0.0f;

        // Встановлення цільового кута 
        targetRotationAngle = 180.0f;

    }
  

}




void Engine::onMouseMove(int x, int y) {
   
    if (isDragging) {
    
        float dx = (x - lastMouseX) * 0.01f;
        float dy = -(y - lastMouseY) * 0.01f;

        float lineStartX, lineStartY, lineStartZ, lineEndX, lineEndY, lineEndZ;
        line.getStart(lineStartX, lineStartY, lineStartZ);
        line.getEnd(lineEndX, lineEndY, lineEndZ);

        pointX += dx;
        pointY += dy;

        line.setStart(lineStartX + dx, lineStartY + dy, lineStartZ);
        line.setEnd(lineEndX + dx, lineEndY + dy, lineEndZ);

        lastMouseX = x;
        lastMouseY = y;

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
    instance->onMouse(button, state, x, y);
}

void Engine::motionCallback(int x, int y) {
    instance->onMouseMove(x, y);
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

