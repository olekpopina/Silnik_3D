#ifndef ENGINE_H
#define ENGINE_H

#include <GL/freeglut.h>
#include <iostream>
#include "PrimitiveDrawer.h"
#include "Triangle.h"
#include "Player.h"
#include "Line.h"
#include "Point.h"
#include "BitmapHandler.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <string>
#include <windows.h>


enum class LightingMode {
    NONE,
    POINT_LIGHT,
    DIRECTIONAL_LIGHT,
    SPOTLIGHT
};

enum class ShadingMode {
    FLAT,
    SMOOTH
};

class Engine {
public:
    Engine(int width, int height, const char* title, int fps = 60);

    void init(int argc, char** argv);
    void showWinnerMessage(const std::string& winner);
    void setClearColor(float r, float g, float b, float a = 1.0f);
    void setFrameRate(int fps);
    void run();
    void stop();
    void setTextures(const std::vector<std::string>& texturePaths);
    void render();
    void onKeyboard(unsigned char key, int x, int y);
    void onMouse(int button, int state, int x, int y);
    void onSpecialKeyboard(int key, int x, int y);
    void updatePawnPosition();
    void resetGame();
    bool crossedBottomBoundary1 = false; 
    bool crossedBottomBoundary2 = false; 
    // Flagi i zmienne dla obsługi przesuwania linii
    bool isDraggingLine = false;        // Czy linia jest przesuwana
    float mouseStartX = 0.0f;           // Początkowa współrzędna X myszki
    float mouseStartY = 0.0f;           // Początkowa współrzędna Y myszki
    float lineStartPosX = 0.0f;         // Początkowa pozycja X linii
    float lineStartPosY = 0.0f;         // Początkowa pozycja Y linii

    // Funkcje do obsługi kliknięć i ruchu myszki
    void handleMouseClick(int button, int state, int x, int y); // Kliknięcie myszką
    void handleMouseMotion(int x, int y); // Ruch myszką
    ShadingMode currentShadingMode = ShadingMode::SMOOTH; // Поточний режим затінення
    LightingMode currentLightingMode = LightingMode::NONE; // Поточний режим освітлення
    
    
    void switchShadingMode(); // Зміна режиму затінення
    void configureLighting(); // Налаштування освітлення
    void switchLightingMode(); // Зміна режиму освітлення


    void onMouseWheel(int wheel, int direction, int x, int y);
    static void setInstance(Engine* engineInstance);
   static void timer(int value);
   int frameRate;
private:
    Triangle triangle;
    Player player;
    PrimitiveDrawer drawer;
    BitmapHandler bitmapHandler;  // Tekstura obiektu
    Line line;
    Point point;
  
    int windowWidth, windowHeight;
    const char* windowTitle;
    
    float clearColor[4];
    int lastTime = 0;
    float cameraZ;

    bool isGameRunning = false;
 
    bool isDragging = false;


    bool isPointNearLine(float px, float py, float x1, float y1, float x2, float y2, float threshold);
    float minCameraZ = 2.0f; 
    float maxCameraZ = 20.0f;

    bool isCubeRotating = false;
    float rotationStartTime = 0.0f; // Czas rozpoczęcia obrotu
    float cubeRotationAngle = 0.0f; // Aktualny kąt obrotu kostki
    float rotationAxisX = 1.0f;
    float rotationAxisY = 0.0f;
    float rotationAxisZ = 0.0f;
    std::mt19937 rng; // Generator liczb losowych
    std::uniform_int_distribution<int> dist; // Rozkład liczb losowych

    bool isPawnMoving = false;
    bool isPawnMoving2 = false;
    int pawnStepsRemaining = 0;
    int pawnStepsRemaining2 = 0;
    float pawnStepSize = 0.05f;
    float pawnStepSize2 = 0.05f;
    float pawnX = 0.1f, pawnY = 0.1f;
    float pawnX2 = 0.1f, pawnY2 = 0.1f;
    float pawnLastMoveTime = 0.0f;
    float pawnLastMoveTime2 = 0.0f;
    bool isMyTurn;
    

    static void renderCallback();
    static void idleCallback();
    static void keyboardCallback(unsigned char key, int x, int y);
    static void mouseCallback(int button, int state, int x, int y);
    static void motionCallback(int x, int y);
    static void reshapeCallback(int width, int height);
    bool isClickOnCube(int mouseX, int mouseY);
    static void specialKeyboardCallback(int key, int x, int y);
   
    static Engine* instance;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;
  
};

#endif // ENGINE_H