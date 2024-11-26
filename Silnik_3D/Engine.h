#ifndef ENGINE_H
#define ENGINE_H

#include <GL/freeglut.h>
#include <iostream>
#include "PrimitiveDrawer.h"

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
    int windowWidth, windowHeight;
    const char* windowTitle;
    int frameRate;
    float clearColor[4];
    bool isRunning;
    int lastTime;

    // Mouse interaction
    float lineStart[3];  // Start of the line
    float lineEnd[3];    // End of the line
    bool isDragging;     // Is the line being dragged
    int lastMouseX, lastMouseY; // Last mouse position

    static void renderCallback();
    static void idleCallback();
    static void keyboardCallback(unsigned char key, int x, int y);
    static void mouseCallback(int button, int state, int x, int y);
    static void motionCallback(int x, int y);
    static void reshapeCallback(int width, int height);

    static Engine* instance;
};

#endif // ENGINE_H
