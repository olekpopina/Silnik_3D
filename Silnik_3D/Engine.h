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
#include "ShadingMode.h"
#include <thread>
#include "Paths.h"
#include "PawnData.h"
#include "Winner.h"
#include "Light.h"
#include "Pawn3D.h"

/**
 * @brief Klasa zarządzająca silnikiem graficznym.
 *
 * Klasa Engine jest odpowiedzialna za inicjalizację okna, rysowanie obiektów, obsługę wejścia
 * z klawiatury i myszy, a także za renderowanie sceny i kontrolowanie gry.
 */
class Engine {
public:

    /**
     * @brief Konstruktor klasy Engine.
     *
     * Ustawia szerokość i wysokość okna, tytuł oraz domyślną liczbę klatek na sekundę.
     *
     * @param width Szerokość okna.
     * @param height Wysokość okna.
     * @param title Tytuł okna.
     * @param fps Liczba klatek na sekundę.
     */
    Engine(int width, int height, const char* title, int fps = 60);


    /**
     * @brief Inicjalizuje środowisko OpenGL.
     *
     * Przygotowuje OpenGL do rysowania, ustawiając wszystkie niezbędne parametry.
     *
     * @param argc Liczba argumentów.
     * @param argv Argumenty wiersza poleceń.
     */
    void init(int argc, char** argv);
    
    /**
     * @brief Wyświetla wiadomość o wygranej.
     *
     * @param winner Nazwa zwycięzcy, która ma być wyświetlona.
     */
    void showWinnerMessage(const std::string& winner);
   
    /**
     * @brief Ustawia kolor tła.
     *
     * @param r Czerwony składnik koloru.
     * @param g Zielony składnik koloru.
     * @param b Niebieski składnik koloru.
     * @param a Przezroczystość (domyślnie 1.0f).
     */
    void setClearColor(float r, float g, float b, float a = 1.0f);
   
    /**
     * @brief Ustawia liczbę klatek na sekundę.
     *
     * @param fps Liczba klatek na sekundę.
     */
    void setFrameRate(int fps);
    
    /**
    * @brief Uruchamia pętlę gry.
    *
    * Pętla gry, która renderuje scenę, przetwarza zdarzenia, aktualizuje stan gry.
    */
    void run();
    
    /**
     * @brief Zatrzymuje działanie gry.
     *
     * Zatrzymuje wszystkie procesy związane z grą i renderowaniem.
     */
    void stop();
   
    /**
     * @brief Ustawia tekstury dla obiektów w grze.
     *
     * @param texturePaths Lista ścieżek do plików tekstur.
     */
    void setTextures(const std::vector<std::string>& texturePaths);
    
    /**
     * @brief Funkcja renderująca.
     *
     * Wykonuje renderowanie sceny w oknie aplikacji.
     */
    void render();
   
    /**
    * @brief Obsługuje naciśnięcie klawisza na klawiaturze.
    *
    * @param key Naciśnięty klawisz.
    * @param x Pozycja myszy w osi X.
    * @param y Pozycja myszy w osi Y.
    */
    void onKeyboard(unsigned char key, int x, int y);
   
    /**
     * @brief Obsługuje kliknięcie myszą.
     *
     * @param button Przycisk myszy.
     * @param state Stan przycisku (wciśnięty lub puszczony).
     * @param x Pozycja myszy w osi X.
     * @param y Pozycja myszy w osi Y.
     */
    void onMouse(int button, int state, int x, int y);
    
    /**
     * @brief Obsługuje specjalne klawisze na klawiaturze.
     *
     * @param key Specjalny klawisz.
     * @param x Pozycja myszy w osi X.
     * @param y Pozycja myszy w osi Y.
     */
    void onSpecialKeyboard(int key, int x, int y);
    
    /**
     * @brief Aktualizuje pozycję pionka w grze.
     */
    void updatePawnPosition(const std::string& id);
    
    /**
     * @brief Resetuje stan gry.
     */
    void resetGame();


    // Flagi i zmienne dla obsługi przesuwania linii
    bool crossedBottomBoundary1 = false; ///< Flaga dla pierwszej granicy
    bool crossedBottomBoundary2 = false; ///< Flaga dla drugiej granicy
    bool isDraggingLine = false;         ///< Flaga wskazująca, czy linia jest przesuwana
    float mouseStartX = 0.0f;            ///< Początkowa współrzędna X myszki
    float mouseStartY = 0.0f;            ///< Początkowa współrzędna Y myszki
    float lineStartPosX = 0.0f;          ///< Początkowa pozycja X linii
    float lineStartPosY = 0.0f;          ///< Początkowa pozycja Y linii

    /**
    * @brief Obsługuje kliknięcie myszką.
    *
    * @param button Przycisk myszy.
    * @param state Stan przycisku (wciśnięty lub puszczony).
    * @param x Pozycja myszy w osi X.
    * @param y Pozycja myszy w osi Y.
    */
    void handleMouseClick(int button, int state, int x, int y); // Kliknięcie myszką
    
    /**
     * @brief Obsługuje ruch myszki.
     *
     * @param x Pozycja myszy w osi X.
     * @param y Pozycja myszy w osi Y.
     */
    void handleMouseMotion(int x, int y); // Ruch myszką
    
    
    ShadingMode currentShadingMode = ShadingMode::SMOOTH; // Bieżący tryb oświetlenia
    
    /**
    * @brief Zmienia tryb cieniowania.
    */
    void switchShadingMode();

    /**
    * @brief Obsługuje przewijanie kółka myszy.
    *
    * @param wheel Numer koła myszy.
    * @param direction Kierunek przewijania.
    * @param x Pozycja myszy w osi X.
    * @param y Pozycja myszy w osi Y.
    */
    void onMouseWheel(int wheel, int direction, int x, int y);
    
    /**
    * @brief Ustawia instancję silnika.
    *
    * @param engineInstance Instancja silnika.
    */
    static void setInstance(Engine* engineInstance);

    /**
     * @brief Funkcja wywoływana co klatkę.
     *
     * @param value Parametr dla timera.
     */
   static void timer(int value);

   int frameRate; ///< Liczba klatek na sekundę


       void setPlayerNicknames(const std::string& name1, const std::string& name2);

       void draw3DPawnAt(float x, float y);

private:
    // Obiekty i zmienne związane z grą
    Triangle triangle;
    Player player;
    PrimitiveDrawer drawer;
    BitmapHandler bitmapHandler;  ///< Obiekt do zarządzania teksturami
    Line line;
    Point point;
    Light light;
    Pawn3D pawn3D;

    float pawnX2t = 0.90f;
    float pawnY2t = 0.20f;


    int windowWidth, windowHeight; ///< Wymiary okna
    const char* windowTitle; ///< Tytuł okna

    float clearColor[4]; ///< Kolor tła okna
    int lastTime = 0; ///< Czas ostatniej klatki
    float cameraZ; ///< Pozycja kamery w osi Z

    bool isGameRunning = false; ///< Flaga, czy gra jest aktywna

    bool isDragging = false; ///< Flaga, czy obiekt jest przesuwany

    float minCameraZ = 2.0f; ///< Minimalna wartość dla kamery
    float maxCameraZ = 20.0f; ///< Maksymalna wartość dla kamery

    bool isCubeRotating = false; ///< Flaga, czy sześcian się obraca
    float rotationStartTime = 0.0f; ///< Czas rozpoczęcia obrotu
    float cubeRotationAngle = 0.0f; ///< Kąt obrotu sześcianu
    float rotationAxisX = 1.0f, rotationAxisY = 0.0f, rotationAxisZ = 0.0f; ///< Osie obrotu
    bool diceInCenter = true; // domyślnie na środku
    float cubeScreenPosX = 0.5f;  // Domyślnie środek
    float cubeScreenPosY = 0.32f;
    float cubeScreenScale = 0.05f;  // Takie jak używasz w render()
    bool firstThrowDone = false;


    std::mt19937 rng; ///< Generator liczb losowych
    std::uniform_int_distribution<int> dist; ///< Rozkład liczb losowych

    bool isPawnMoving = false; ///< Flaga dla ruchu pionka
    bool isPawnMoving2 = false; ///< Flaga dla ruchu drugiego pionka
    int pawnStepsRemaining = 0; ///< Liczba pozostałych kroków pionka
    int pawnStepsRemaining2 = 0; ///< Liczba pozostałych kroków drugiego pionka
    float pawnStepSize = 0.05f; ///< Wielkość kroku pionka
    float pawnStepSize2 = 0.1f; ///< Wielkość kroku drugiego pionka
    float pawnX; 
    float pawnY;
    float pawnX2;
    float pawnY2; 
    float pawnLastMoveTime = 0.0f; ///< Czas ostatniego ruchu pionka
    float pawnLastMoveTime2 = 0.0f; ///< Czas ostatniego ruchu drugiego pionka
    bool isMyTurn; ///< Flaga określająca, czy gracz ma swoją turę
    int currentStepRed = 0;
    int currentStepBlue = 0;
    bool canRollAgain = false;

    bool diceRolledForRed = false;
    bool diceRolledForBlue = false;

    bool redPawnInPlay2 = false;
    float pawnX_R2;
    float pawnY_R2;

    bool bluePawnInPlay2 = false;
    float pawnX_B2;
    float pawnY_B2;

    int currentStepRed2 = 0;
    int currentStepBlue2 = 0;

    int pawnStepsRemainingRed2 = 0;
    int pawnStepsRemainingBlue2 = 0;

    bool isRedPawn2Moving = false;
    bool isBluePawn2Moving = false;

    float lastMoveTimeRed2 = 0.0f;
    float lastMoveTimeBlue2 = 0.0f;


    bool redPawnInPlay3 = false;
    float pawnX_R3;
    float pawnY_R3;

    bool bluePawnInPlay3 = false;
    float pawnX_B3;
    float pawnY_B3;

    int currentStepRed3 = 0;
    int currentStepBlue3 = 0;

    int pawnStepsRemainingRed3 = 0;
    int pawnStepsRemainingBlue3 = 0;

    bool isRedPawn3Moving = false;
    bool isBluePawn3Moving = false;

    float lastMoveTimeRed3 = 0.0f;
    float lastMoveTimeBlue3 = 0.0f;

    bool redPawnInPlay4 = false;
    float pawnX_R4;
    float pawnY_R4;

    bool bluePawnInPlay4 = false;
    float pawnX_B4;
    float pawnY_B4;

    int currentStepRed4 = 0;
    int currentStepBlue4 = 0;

    int pawnStepsRemainingRed4 = 0;
    int pawnStepsRemainingBlue4 = 0;

    bool isRedPawn4Moving = false;
    bool isBluePawn4Moving = false;

    float lastMoveTimeRed4 = 0.0f;
    float lastMoveTimeBlue4 = 0.0f;

    std::vector<std::pair<float, float>> redHouse = Paths::getRedHouse();
    std::vector<std::pair<float, float>> blueHouse = Paths::getBlueHouse();
    std::vector<std::pair<float, float>> redPath = Paths::getRedPath();
    std::vector<std::pair<float, float>> bluePath = Paths::getBluePath();

    int redHouseIndex = 0;
    int blueHouseIndex = 0;
    bool redPawnInPlay = false;
    bool bluePawnInPlay = false;
    bool waitingForRedPawnClick = false;
    bool waitingForBluePawnClick = false;
    bool rolledSix = false; // czy w ostatnim rzucie wypadło 6
    bool allowPawnSelection = false; // pozwala na wybór pionka do ruchu po wyrzuceniu 6
    int manualDiceValue = -1; // czasowa zmienna dla steps

    std::string player1Name = "Gracz 1";
    std::string player2Name = "Gracz 2";

    bool extraRollAfterCapture = false; // Nowa zmienna - pozwala na dodatkowy rzut po zbiciu pionka
    bool forceEndTurnAfterRotation = false;

    int consecutiveSixes = 0;

  
    // Statyczne funkcje wywoływane przez OpenGL
    static void renderCallback();
    static void idleCallback();
    static void keyboardCallback(unsigned char key, int x, int y);
    static void mouseCallback(int button, int state, int x, int y);
    static void motionCallback(int x, int y);
    static void reshapeCallback(int width, int height);
    void initializePawnPaths();
    /**
     * @brief Sprawdza, czy kliknięcie myszki jest na sześcianie.
     *
     * @param mouseX Współrzędna X myszy.
     * @param mouseY Współrzędna Y myszy.
     * @return Zwraca true, jeśli kliknięcie jest na sześcianie, w przeciwnym razie false.
     */
    bool isClickOnCube(int mouseX, int mouseY) const;
    static void specialKeyboardCallback(int key, int x, int y);
   
    static Engine* instance; ///< Instancja silnika
    std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime; ///< Czas ostatniej klatki
  
};

#endif // ENGINE_H