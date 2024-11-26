#include "Engine.h"

Engine* Engine::instance = nullptr;

Engine::Engine(int width, int height, const char* title)
    : windowWidth(width), windowHeight(height), windowTitle(title),
    frameRate(60), clearColor{ 0.0f, 0.0f, 0.0f, 1.0f }, isRunning(false) {}

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

    // Example rendering
    PrimitiveDrawer::drawPoint(0.0f, 0.0f, -5.0f, 5.0f);
    PrimitiveDrawer::drawLine(-0.5f, -0.5f, -5.0f, 0.5f, 0.5f, -5.0f, 2.0f);

    Cube cube;
    cube.draw();

    glutSwapBuffers();
}

void Engine::onKeyboard(unsigned char key, int x, int y) {
    if (key == 27) { // ESC key
        stop();
    }
    std::cout << "Key pressed: " << key << " at (" << x << ", " << y << ")\n";
}

void Engine::onMouse(int button, int state, int x, int y) {
    std::cout << "Mouse button: " << button
        << " state: " << state
        << " at (" << x << ", " << y << ")\n";
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
