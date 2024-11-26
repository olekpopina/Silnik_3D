#include <GL/freeglut.h>
#include <iostream>

class Engine {
public:
    // Konstruktor
    Engine(int width, int height, const char* title)
        : windowWidth(width), windowHeight(height), windowTitle(title),
        frameRate(60), clearColor{ 0.0f, 0.0f, 0.0f, 1.0f }, isRunning(false) {}

    // Inicjalizacja silnika
    void init(int argc, char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(windowWidth, windowHeight);
        glutCreateWindow(windowTitle);

        // Inicjalizacja ustawień domyślnych
        glEnable(GL_DEPTH_TEST);  // Włącz bufor głębokości
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

        // Rejestracja funkcji GLUT
        glutDisplayFunc(renderCallback);
        glutIdleFunc(idleCallback);
        glutKeyboardFunc(keyboardCallback);
        glutMouseFunc(mouseCallback);
        glutReshapeFunc(reshapeCallback);

        isRunning = true;
    }

    // Ustawienia renderowania
    void setClearColor(float r, float g, float b, float a = 1.0f) {
        clearColor[0] = r;
        clearColor[1] = g;
        clearColor[2] = b;
        clearColor[3] = a;
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    }

    void setFrameRate(int fps) {
        frameRate = fps;
    }

    // Funkcja głównej pętli
    void run() {
        lastTime = glutGet(GLUT_ELAPSED_TIME);
        glutMainLoop();
    }

    // Zakończenie działania
    void stop() {
        isRunning = false;
        glutLeaveMainLoop();
    }

    // Funkcja renderowania
    void render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // Przykładowa scena
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, -5.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, -5.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.5f, -5.0f);
        glEnd();

        glutSwapBuffers();
    }

    // Obsługa wejścia z klawiatury
    void onKeyboard(unsigned char key, int x, int y) {
        if (key == 27) { // ESC
            stop();
        }
        std::cout << "Key pressed: " << key << " at (" << x << ", " << y << ")\n";
    }

    // Obsługa wejścia z myszy
    void onMouse(int button, int state, int x, int y) {
        std::cout << "Mouse button: " << button
            << " state: " << state
            << " at (" << x << ", " << y << ")\n";
    }

    // Czyszczenie i zamknięcie
    void cleanup() {
        std::cout << "Engine shutting down.\n";
    }

private:
    int windowWidth, windowHeight;
    const char* windowTitle;
    int frameRate;
    float clearColor[4];
    bool isRunning;
    int lastTime;

    // Callbacki statyczne dla GLUT
    static void renderCallback() {
        instance->render();
    }

    static void idleCallback() {
        int currentTime = glutGet(GLUT_ELAPSED_TIME);
        if (currentTime - instance->lastTime >= 1000 / instance->frameRate) {
            instance->lastTime = currentTime;
            glutPostRedisplay();
        }
    }

    static void keyboardCallback(unsigned char key, int x, int y) {
        instance->onKeyboard(key, x, y);
    }

    static void mouseCallback(int button, int state, int x, int y) {
        instance->onMouse(button, state, x, y);
    }

    static void reshapeCallback(int width, int height) {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
        glMatrixMode(GL_MODELVIEW);
    }

    // Singletonowa instancja
    static Engine* instance;

public:
    static void setInstance(Engine* engineInstance) {
        instance = engineInstance;
    }
};

// Inicjalizacja statycznego wskaźnika
Engine* Engine::instance = nullptr;

int main(int argc, char** argv) {
    Engine gameEngine(800, 600, "Game Engine");
    Engine::setInstance(&gameEngine);

    gameEngine.init(argc, argv);
    gameEngine.setClearColor(0.2f, 0.3f, 0.4f);
    gameEngine.setFrameRate(60);
    gameEngine.run();

    gameEngine.cleanup();
    return 0;
}
