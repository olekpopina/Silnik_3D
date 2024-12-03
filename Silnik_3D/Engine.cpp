#include "Engine.h"
#include "Cube.h"
#include "Triangle.h"

Cube cube;
Engine* Engine::instance = nullptr;


Engine::Engine(int width, int height, const char* title)
    : windowWidth(width), windowHeight(height), windowTitle(title),
    frameRate(60), clearColor{ 0.0f, 0.0f, 0.0f, 1.0f },
    lastMouseX(0), lastMouseY(0), lastTime(0),
    isDragging(false), cameraZ(5.0f), player(&triangle, &cube), 
    pointX(0.5f), pointY(0.5f), pointZ(0.5f),
    line(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f) {
    
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
        0.0, 0.0, 0.0,      // Punkt, na który patrzy kamera
        0.0, 1.0, 0.0);     // Wektor "w górê"

   cube.draw();
    triangle.updateRotation(deltaTime); // Aktualizacja obrotu
    triangle.updatePosition(); // Aktualizacja pozycji (jeœli potrzeba)
    triangle.draw(); // Rysowanie trójk¹ta

    // Rysowanie linii
    glPushMatrix();
    glTranslatef(linePosX, linePosY, 0.0f);
    line.draw();  // Rysowanie linii
    PrimitiveDrawer::drawPoint(pointX, pointY, pointZ, 5.0f);
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
    player.handleInput(key);
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
        // Zmiana pozycji punktu na linii w zale¿noœci od ruchu myszy
        float dx = (x - lastMouseX) * 0.01f;
        float dy = -(y - lastMouseY) * 0.01f;

        // Ustalamy now¹ pozycjê punktu wzd³u¿ linii
        float lineStartX, lineStartY, lineStartZ, lineEndX, lineEndY, lineEndZ;
        line.getStart(lineStartX, lineStartY, lineStartZ);
        line.getEnd(lineEndX, lineEndY, lineEndZ);

        // Przemieszczanie punktu wzd³u¿ linii
        pointX += dx;
        pointY += dy;

        // Zaktualizowanie pozycji linii, aby punkt pozosta³ na niej
        line.setStart(lineStartX + dx, lineStartY + dy, lineStartZ);
        line.setEnd(lineEndX + dx, lineEndY + dy, lineEndZ);

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}

void Engine::idleCallback() {
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; // Czas w sekundach
    float deltaTime = currentTime - instance->lastTime;       // Delta czasu
    instance->lastTime = currentTime;

    instance->player.update(deltaTime); // Zaktualizowanie stanu gracza (ruch i obrót trójk¹ta)
    glutPostRedisplay();                // Wymuœ ponowne renderowanie
}

void Engine::renderCallback() {
    if (instance) {
        instance->render(); // Wywo³anie metody instancji
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
}

void Engine::setInstance(Engine* engineInstance) {
    instance = engineInstance;
}

