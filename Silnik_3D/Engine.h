#ifndef ENGINE_H
#define ENGINE_H

#include <GL/freeglut.h>
#include <iostream>
#include "PrimitiveDrawer.h"
#include "Triangle.h"
#include "Player.h"
#include "Line.h"
#include "TransformableObject.h"
#include "BitmapHandler.h"


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
    void onSpecialKeyboard(int key, int x, int y);
    void onMouseWheel(int wheel, int direction, int x, int y);
    static void setInstance(Engine* engineInstance);
    BitmapHandler bitmapHandler;

private:
    Triangle triangle;
    TransformableObject transformable;
    Player player;
    PrimitiveDrawer drawer;
   

    int windowWidth, windowHeight;
    const char* windowTitle;
    int frameRate;
    float clearColor[4];
    float deltaTime = 0.0f;
    int lastTime;
    float cameraZ;

    bool isRotating = false;    // Flaga okreœlaj¹ca, czy trójk¹t ma siê obracaæ

    
    int lastMouseX, lastMouseY; // Ostatnia pozycja myszy
 
    bool isDragging; // Stan, czy linia jest przeci¹gana
    bool isPointNearLine(float px, float py, float x1, float y1, float x2, float y2, float threshold);
    float trianglePosX = 0.0f; // Pozycja trójk¹ta na osi X
    float trianglePosY = 0.0f; // Pozycja trójk¹ta na osi Y
    float linePosX = 0.10f; // Pozycja trójk¹ta na osi X
    float linePosY = 0.10f; // Pozycja trójk¹ta na osi Y
    float pointX, pointY, pointZ;
    float minCameraZ = 2.0f; // Minimalna odleg³oœæ kamery
    float maxCameraZ = 20.0f; // Maksymalna odleg³oœæ kamery

    Line line;

    static void renderCallback();
    static void idleCallback();
    static void keyboardCallback(unsigned char key, int x, int y);
    static void mouseCallback(int button, int state, int x, int y);
    static void motionCallback(int x, int y);
    static void reshapeCallback(int width, int height);
    static void specialKeyboardCallback(int key, int x, int y);
   


    static Engine* instance;

};

#endif // ENGINE_H