#include "Engine.h"

Engine* Engine::instance = nullptr;

Engine::Engine(int width, int height, const char* title)
    : windowWidth(width), windowHeight(height), windowTitle(title),
    frameRate(60), clearColor{ 0.0f, 0.0f, 0.0f, 1.0f },
    isRunning(false), isDragging(false),
    lineStart{ -0.5f, 0.0f, -5.0f }, lineEnd{ 0.5f, 0.0f, -5.0f } {}

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

    isRunning = true;
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
    isRunning = false;
    glutLeaveMainLoop();
}

void Engine::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Rysowanie przesuwanej linii
    PrimitiveDrawer::drawLine(
        lineStart[0], lineStart[1], lineStart[2],
        lineEnd[0], lineEnd[1], lineEnd[2],
        2.0f
    );

    // Wierzcho³ki trójk¹ta
    float triangleVertices[] = {
        -0.5f, -0.5f, -5.0f,
         0.5f, -0.5f, -5.0f,
         0.0f,  0.5f, -5.0f
    };

    // Kolory wierzcho³ków trójk¹ta
    float triangleColors[] = {
        1.0f, 0.0f, 0.0f,  // Czerwony
        0.0f, 1.0f, 0.0f,  // Zielony
        0.0f, 0.0f, 1.0f   // Niebieski
    };

    // Rysowanie trójk¹ta
    PrimitiveDrawer::drawTriangle(triangleVertices, triangleColors);

    glutSwapBuffers();
}

void Engine::onKeyboard(unsigned char key, int x, int y) {
    if (key == 27) { // ESC key
        stop();
    }
    std::cout << "Key pressed: " << key << " at (" << x << ", " << y << ")\n";
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

void Engine::cleanup() {
    std::cout << "Engine shutting down.\n";
}

void Engine::renderCallback() {
    instance->render();
}

void Engine::idleCallback() {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime - instance->lastTime >= 1000 / instance->frameRate) {
        instance->lastTime = currentTime;
        glutPostRedisplay();
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
}

void Engine::setInstance(Engine* engineInstance) {
    instance = engineInstance;
}
