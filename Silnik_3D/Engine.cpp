#include "Engine.h"
#include "Cube.h"
#include "Triangle.h"



Cube cube;
Engine* Engine::instance = nullptr;

Engine::Engine(int width, int height, const char* title)
    : windowWidth(width), windowHeight(height), windowTitle(title),
    frameRate(60), clearColor{ 0.0f, 0.0f, 0.0f, 1.0f },
    lastMouseX(0), lastMouseY(0), lastTime(0),
    isDragging(false), cameraZ(5.0f) {
    lineStart[0] = -0.5f; lineStart[1] = 0.0f; lineStart[2] = -5.0f;
    lineEnd[0] = 0.5f; lineEnd[1] = 0.0f; lineEnd[2] = -5.0f;
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


void Engine::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Ustawienie kamery
    gluLookAt(1.5, 1.5, cameraZ,  // Pozycja kamery
        0.0, 0.0, 0.0,      // Punkt, na kt�ry patrzy kamera
        0.0, 1.0, 0.0);     // Wektor "w g�r�"


   cube.draw();
    triangle.updateRotation(deltaTime); // Aktualizacja obrotu
    triangle.updatePosition(); // Aktualizacja pozycji (je�li potrzeba)
    triangle.draw(); // Rysowanie tr�jk�ta


    // Rysowanie linii
    glPushMatrix();
    glTranslatef(linePosX, linePosY, 0.0f); // Transformacja tylko dla linii
    PrimitiveDrawer::drawLine(
        lineStart[0], lineStart[1], lineStart[2],
        lineEnd[0], lineEnd[1], lineEnd[2],
        2.0f
    );
    glPopMatrix();
   
    glutSwapBuffers();

 
   
}




bool Engine::isPointNearLine(float px, float py, float x1, float y1, float x2, float y2, float threshold) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float lengthSq = dx * dx + dy * dy;
    float projection = ((px - x1) * dx + (py - y1) * dy) / lengthSq;

    if (projection < 0.0f || projection > 1.0f) {
        return false; // Punkt poza odcinkiem
    }

    float closestX = x1 + projection * dx;
    float closestY = y1 + projection * dy;

    float distSq = (px - closestX) * (px - closestX) + (py - closestY) * (py - closestY);
    return distSq <= threshold * threshold;
}


void Engine::onKeyboard(unsigned char key, int x, int y) {
    if (key == 27) { // ESC key
        stop();
    }
    else if (key == 'i' || key == 'I') { // W��cz/wy��cz obr�t
        isRotating = !isRotating;
        triangle.setRotation(isRotating);
    }
    else if (key == 'w' || key == 'W') {
        trianglePosY += 0.1f;
        triangle.setPosition(trianglePosX, trianglePosY);
    }
    else if (key == 's' || key == 'S') {
        trianglePosY -= 0.1f;
        triangle.setPosition(trianglePosX, trianglePosY);
    }
    else if (key == 'a' || key == 'A') {
        trianglePosX -= 0.1f;
        triangle.setPosition(trianglePosX, trianglePosY);
    }
    else if (key == 'd' || key == 'D') {
        trianglePosX += 0.1f;
        triangle.setPosition(trianglePosX, trianglePosY);
    }
    glutPostRedisplay(); // Aktualizacja ekranu
}




void Engine::onMouse(int button, int state, int x, int y) {
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
}



void Engine::onMouseMove(int x, int y) {
    if (isDragging) {
        float dx = (x - lastMouseX) * 0.01f;
        float dy = -(y - lastMouseY) * 0.01f;

        lineStart[0] += dx;
        lineStart[1] += dy;
        lineEnd[0] += dx;
        lineEnd[1] += dy;

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}
void Engine::idleCallback() {
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; // Czas w sekundach
    float deltaTime = currentTime - instance->lastTime;       // Delta czasu
    instance->lastTime = currentTime;

    instance->triangle.updateRotation(deltaTime); // Aktualizacja obrotu tr�jk�ta
    glutPostRedisplay();                          // Wymu� ponowne renderowanie
}


void Engine::renderCallback() {
    if (instance) {
        instance->render(); // Wywo�anie metody instancji
    }
}

void Engine::cleanup() {
    std::cout << "Engine shutting down.\n";
}
/*
void Engine::renderCallback() {
    instance->render();
}
*/
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
}

void Engine::setInstance(Engine* engineInstance) {
    instance = engineInstance;
}
