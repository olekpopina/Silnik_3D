#ifndef ENGINE_H
#define ENGINE_H

#include <GL/freeglut.h>
#include <iostream>

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
    void cleanup();

    static void setInstance(Engine* engineInstance);

private:
    int windowWidth, windowHeight;
    const char* windowTitle;
    int frameRate;
    float clearColor[4];
    bool isRunning;
    int lastTime;

    static void renderCallback();
    static void idleCallback();
    static void keyboardCallback(unsigned char key, int x, int y);
    static void mouseCallback(int button, int state, int x, int y);
    static void reshapeCallback(int width, int height);

    static Engine* instance;
};

#endif // ENGINE_H
