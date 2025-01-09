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

    updatePawnPosition();

    glPushMatrix();
    cube.draw();
  
   
    if (isCubeRotating) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - rotationStartTime;

        if (elapsedTime < 2.0f) {
            cubeRotationAngle = elapsedTime * 180.0f; // Dynamiczny obrót
        }
        else {
            cubeRotationAngle = targetRotationAngle;
            isCubeRotating = false;

            // Zakończ obrót i rozpocznij ruch pionka
            isPawnMoving = true;
            pawnLastMoveTime = currentTime;
        }
    }

    // Obracaj kostkę wokół losowo wybranej osi
    glRotatef(cubeRotationAngle, rotationAxisX, rotationAxisY, rotationAxisZ);

    PrimitiveDrawer::drawCubeNew(1.0f, 0.0f, 0.0f, bitmapHandler);
    glPopMatrix();
    // Rysowanie pionka i jego ruch
    if (isPawnMoving) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float elapsedTime = currentTime - pawnLastMoveTime;

        if (elapsedTime >= 0.1f && pawnStepsRemaining > 0) { // Jeden krok co 0.1 sekundy
            pawnX += pawnStepSize;
            pawnStepsRemaining--;
            pawnLastMoveTime = currentTime;
        }

        if (pawnStepsRemaining == 0) {
            isPawnMoving = false;
        }
    }
    bitmapHandler.drawPionek(pawnX, pawnY, 0.1f, 0.1f);

  //  glPopMatrix();

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
    // Jeśli pionek osiągnął prawą krawędź
    if (pawnX >= 750.0f) {
        pawnX = 0.0f;   // Resetujemy na lewą krawędź
        pawnY += 0.1f;   // Przemieszczamy pionka do góry
    }

    // Jeśli pionek osiągnął górną krawędź
    if (pawnY >= 550.0f) {
        pawnY = 0.0f;   // Resetujemy na dolną krawędź
        pawnX += 0.1f;   // Przemieszczamy pionka w prawo
    }

    // Jeśli pionek osiągnął dolną krawędź
    if (pawnY <= 0.0f) {
        pawnY = 550.0f;   // Resetujemy na górną krawędź
        pawnX += 0.1f;   // Przemieszczamy pionka w prawo
    }

    // Jeśli pionek osiągnął lewą krawędź
    if (pawnX <= 0.0f) {
        pawnX = 750.0f;   // Resetujemy na prawą krawędź
        pawnY -= 0.1f;   // Przemieszczamy pionka w dół
    }
}


void Engine::onMouse(int button, int state, int x, int y) {
    /*
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else if (state == GLUT_UP) {
            isDragging = false;
        }
    }
    */
  
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !isCubeRotating && !isPawnMoving) {
        // Rozpocznij obrót kostki
        isCubeRotating = true;
        rotationStartTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

        // Losuj liczbę kroków (1–6)
        srand(static_cast<unsigned int>(time(nullptr)));
        int steps = (rand() % 6) + 1;
        pawnStepsRemaining = steps;
        std::cout << "Wylosowano: " << steps << " ";

        BitmapHandler::bindTextureForCube(steps);
 
        // Obrót i ruch pionka
        rotationAxisX = static_cast<float>(rand() % 2);
        rotationAxisY = static_cast<float>(rand() % 2);
        rotationAxisZ = (rotationAxisX == 0 && rotationAxisY == 0) ? 1.0f : 0.0f;

        pawnTargetX = pawnX + steps * pawnStepSize;
        targetRotationAngle = 180.0f;
        isPawnMoving = false; // Ruch pionka rozpocznie się po zakończeniu obrotu
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
        float deltaTime = currentTime - instance->lastTime;
        instance->lastTime = currentTime;

        if (instance->isCubeRotating) {
            glutPostRedisplay(); // Odświeżanie podczas obrotu
        }

        if (instance->isPawnMoving) {
            if (currentTime - instance->pawnLastMoveTime >= instance->pawnMoveDelay) {
                if (instance->pawnStepsRemaining > 0) {
                    instance->pawnX += instance->pawnStepSize;
                    instance->pawnStepsRemaining--;
                    instance->pawnLastMoveTime = currentTime;
                }
                else {
                    instance->isPawnMoving = false;
                }
            }
        }

        if (instance->isCubeRotating) {
            glutPostRedisplay();
        }
        instance->updatePawnPosition();
        instance->player.update(deltaTime);
        glutPostRedisplay();
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

