#include "Engine.h"
#include "Cube.h"
#include "Triangle.h"


Cube cube;
Engine* Engine::instance = nullptr;


Engine::Engine(int width, int height, const char* title)
    : windowWidth(width), windowHeight(height), windowTitle(title),
    frameRate(60), clearColor{ 0.0f, 0.0f, 0.0f, 1.0f },
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


void Engine::setClearColor(float r, float g, float b, float a) {
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
}

void Engine::setFrameRate(int fps) {
    frameRate = fps;
}

void Engine::run() {
    lastTime = glutGet(GLUT_ELAPSED_TIME);
    glutMainLoop();
}

void Engine::stop() {

    glutLeaveMainLoop();
}

void Engine::setTextures(const std::string& backgroundPath, const std::string& cubePath2, const std::string& cubePath3, const std::string& cubePath4, const std::string& cubePath5, const std::string& cubePath6, const std::string& cubePath7, const std::string& pionek) {
    if (!bitmapHandler.loadTextures(backgroundPath, cubePath2, cubePath3, cubePath4, cubePath5, cubePath6, cubePath7, pionek)) {
        std::cerr << "Nie udało się załadować tekstur!" << std::endl;
    }
}




void Engine::render() {
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
            cubeRotationAngle = targetRotationAngle;
            isCubeRotating = false; // Завершення обертання
            isPawnMoving = true;    // Початок руху пішака
            pawnLastMoveTime = currentTime;
        }
    }

    // Обертання кубика
    glPushMatrix();
    cube.draw();
    glRotatef(cubeRotationAngle, rotationAxisX, rotationAxisY, rotationAxisZ);
    // Wywołaj funkcję drawCubeNew z wylosowaną teksturą, która jest przechowywana w zmiennej
    if (textureSet != -1) {
        PrimitiveDrawer::drawCubeNew(1.0f, 0.0f, 0.0f, bitmapHandler, textureSet);
    }
    glPopMatrix();

    // Рух пішака
    if (isPawnMoving) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - pawnLastMoveTime;

        if (elapsedTime >= 0.1f && pawnStepsRemaining > 0) {
            updatePawnPosition(); // Оновлення позиції пішака
            pawnLastMoveTime = currentTime;
        }

        if (pawnStepsRemaining == 0) {
            isPawnMoving = false;
        }
    }

    bitmapHandler.drawPionek(pawnX, pawnY, 0.1f, 0.1f);

    glPushMatrix();
    triangle.updateRotation(deltaTime);
    triangle.updatePosition();
    triangle.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(linePosX, linePosY, 0.0f);
    line.draw();
    PrimitiveDrawer::drawPoint(pointX, pointY, pointZ, 5.0f);
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
    const float LEFT_LIMIT = 0.1f;  // Ліва межа
    const float RIGHT_LIMIT = 0.85f; // Права межа
    const float BOTTOM_LIMIT = 0.1f; // Нижня межа
    const float TOP_LIMIT = 0.85f;   // Верхня межа

    if (pawnStepsRemaining > 0) {
        // Якщо пішак знаходиться внизу і рухається праворуч
        if (std::abs(pawnY - BOTTOM_LIMIT) < 0.01f && pawnX < RIGHT_LIMIT) {
            pawnX += pawnStepSize; // Рух праворуч
        }
        // Якщо пішак знаходиться праворуч і рухається вгору
        else if (std::abs(pawnX - RIGHT_LIMIT) < 0.01f && pawnY < TOP_LIMIT) {
            pawnY += pawnStepSize; // Рух вгору
        }
        // Якщо пішак знаходиться вгорі і рухається ліворуч
        else if (std::abs(pawnY - TOP_LIMIT) < 0.01f && pawnX > LEFT_LIMIT) {
            pawnX -= pawnStepSize; // Рух ліворуч
        }
        // Якщо пішак знаходиться ліворуч і рухається вниз
        else if (std::abs(pawnX - LEFT_LIMIT) < 0.01f && pawnY > BOTTOM_LIMIT) {
            pawnY -= pawnStepSize; // Рух вниз
        }

        // Зменшити кількість залишкових кроків
        pawnStepsRemaining--;
        std::cout << "[DEBUG] Moving: Pawn X = " << pawnX
            << ", Pawn Y = " << pawnY
            << ", Steps left = " << pawnStepsRemaining << std::endl;
    }

    // Завершення руху
    if (pawnStepsRemaining == 0) {
        isPawnMoving = false;
        std::cout << "[DEBUG] Pawn movement completed!" << std::endl;
    }
}


void Engine::onMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !isCubeRotating && !isPawnMoving) {
        // Початок обертання кубика
        isCubeRotating = true;
        rotationStartTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

        // Генерація випадкової кількості кроків для пішака
        srand(static_cast<unsigned int>(time(nullptr)));
        int steps = (rand() % 6) + 1;
        pawnStepsRemaining = steps;

        std::cout << "[DEBUG] Wylosowano: " << steps << std::endl;

        //BitmapHandler::bindTextureForCube(steps);
        
        // Losuj wartość textureSet z zakresu [1, 6] tylko raz przy pierwszym kliknięciu
        if (textureSet == -1) {
            textureSet = (rand() % 6) + 1;  // Losujemy teksturę
            std::cout << "Wylosowano textureSet: " << textureSet << std::endl;
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
    /*
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
    */
}
/*
void Engine::idleCallback() {
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; 
    float deltaTime = currentTime - instance->lastTime;     
    instance->lastTime = currentTime;

   


    if (instance->isCubeRotating) {
        glutPostRedisplay(); // Odświeżanie podczas obrotu
    }

    instance->player.update(deltaTime); 
    glutPostRedisplay();               
}
*/
void Engine::idleCallback() {
    if (instance) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - instance->lastTime;

        instance->lastTime = currentTime;

        if (instance->isCubeRotating || instance->isPawnMoving) {
        
            
        }
        instance->player.update(elapsedTime);
        glutPostRedisplay(); // Оновлення екрану, якщо є активний рух
    }

}




    


void Engine::renderCallback() {
    if (instance) {
        instance->render();
    }
}

void Engine::cleanup() {
    std::cout << "Engine shutting down.\n";
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

