#ifndef ENGINE_H
#define ENGINE_H

#include <GL/freeglut.h>
#include <iostream>
#include "PrimitiveDrawer.h"
#include "Triangle.h"

class Engine {
public:
    Engine(int width, int height, const char* title);

    void init(int argc, char** argv);
    void setClearColor(float r, float g, float b, float a = 1.0f);
    void setFrameRate(int fps);
    void run();
    void stop();
    void render();
    void onKeyboard(unsigned char key, int x, int y);
    void onMouse(int button, int state, int x, int y);
    void onMouseMove(int x, int y);
    void cleanup();

    static void setInstance(Engine* engineInstance);

private:
    Triangle triangle;
    int windowWidth, windowHeight;
    const char* windowTitle;
    int frameRate;
    float clearColor[4];
    float deltaTime = 0.0f;
    int lastTime;
    float cameraZ;

    bool isRotating = false;    // Flaga okre�laj�ca, czy tr�jk�t ma si� obraca�

    // Pozycje wierzcho�k�w tr�jk�ta
 // float triangleVertices[9];
   // bool isDraggingTriangle; // Czy tr�jk�t jest przeci�gany
    int lastMouseX, lastMouseY; // Ostatnia pozycja myszy
    float lineStart[3], lineEnd[3]; // Pocz�tek i koniec linii
    bool isDragging; // Stan, czy linia jest przeci�gana
    bool isPointNearLine(float px, float py, float x1, float y1, float x2, float y2, float threshold);
    float trianglePosX = 0.0f; // Pozycja tr�jk�ta na osi X
    float trianglePosY = 0.0f; // Pozycja tr�jk�ta na osi Y
    float linePosX = 0.1f; // Pozycja tr�jk�ta na osi X
    float linePosY = 0.1f; // Pozycja tr�jk�ta na osi Y

    static void renderCallback();
    static void idleCallback();
    static void keyboardCallback(unsigned char key, int x, int y);
    static void mouseCallback(int button, int state, int x, int y);
    static void motionCallback(int x, int y);
    static void reshapeCallback(int width, int height);

    static Engine* instance;

};

#endif // ENGINE_H