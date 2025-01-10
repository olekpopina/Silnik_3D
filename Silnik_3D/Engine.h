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
#include <SFML/Graphics.hpp>
#include <random>

class Engine {
public:
    Engine(int width, int height, const char* title);

    void init(int argc, char** argv);
    void setClearColor(float r, float g, float b, float a = 1.0f);
    void setFrameRate(int fps);
    void run();
    void stop();
    void setTextures(const std::string& backgroundPath, const std::string& cubePath2, const std::string& cubePath3, const std::string& cubePath4, const std::string& cubePath5, const std::string& cubePath6, const std::string& cubePath7, const std::string& pionek);
    void render();
    void onKeyboard(unsigned char key, int x, int y);
    void onMouse(int button, int state, int x, int y);

    void onMouseMove(int x, int y);
    void cleanup();
    void onSpecialKeyboard(int key, int x, int y);
    void updatePawnPosition();
    void onMouseWheel(int wheel, int direction, int x, int y);
    static void setInstance(Engine* engineInstance);


   



private:
    Triangle triangle;
    TransformableObject transformable;
    Player player;
    PrimitiveDrawer drawer;
    BitmapHandler bitmapHandler;  // Tekstura obiektu

    int windowWidth, windowHeight;
    const char* windowTitle;
    int frameRate;
    float clearColor[4];
    float deltaTime = 0.0f;
    int lastTime;
    float cameraZ;

    bool isRotating = false;   

    
    int lastMouseX, lastMouseY; 
 
    bool isDragging; 
    bool isPointNearLine(float px, float py, float x1, float y1, float x2, float y2, float threshold);
    float trianglePosX = 0.0f; 
    float trianglePosY = 0.0f; 
    float linePosX = 2.0f; 
    float linePosY = 0.10f; 
    float pointX, pointY, pointZ;
    float minCameraZ = 2.0f; 
    float maxCameraZ = 20.0f;

    bool isCubeRotating_old = false; // Czy kostka siê obraca
    bool isCubeRotating = false;
    float rotationStartTime = 0.0f; // Czas rozpoczêcia obrotu
    float cubeRotationAngle = 0.0f; // Aktualny k¹t obrotu kostki
    float targetRotationAngle = 0.0f; // Docelowy k¹t obrotu po losowaniu
    float rotationAxisX = 1.0f;
    float rotationAxisY = 0.0f;
    float rotationAxisZ = 0.0f;
    bool rotationDirection = true; // true = zgodnie z ruchem wskazówek zegara
    std::mt19937 rng; // Generator liczb losowych
    std::uniform_int_distribution<int> dist; // Rozk³ad liczb losowych
    int previousSide = -1; // Ostatnia wylosowana strona, -1 oznacza brak pocz¹tkowej strony

    bool isPawnMoving = false;
    int pawnStepsRemaining = 0;
    float pawnStepSize = 0.05f;
    float pawnX = 0.1f, pawnY = 0.1f;
    float pawnTargetX = 0.3f, pawnTargetY = 0.3f;
    float pawnMoveDelay = 0.5f;
    float pawnLastMoveTime = 0.0f;
    bool movePawnAfterRotation = false;
    int targetSide = 2;
  
    int textureSet = -1;
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