﻿#include "Engine.h"
#include "Cube.h"
#include "Triangle.h"


Cube cube;
Engine* Engine::instance = nullptr;


Engine::Engine(int width, int height, const char* title)
    : windowWidth(width), windowHeight(height), windowTitle(title),
    frameRate(60), clearColor{ 0.0f, 0.0f, 0.0f, 1.0f },
    lastMouseX(0), lastMouseY(0), lastTime(0),
    isDragging(false), cameraZ(5.0f), player(&triangle, &cube, &drawer), 
    pointX(0.5f), pointY(0.5f), pointZ(0.5f),
    line(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f) {
    
}

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

    glutIdleFunc(idleCallback);
    glutSpecialFunc(specialKeyboardCallback);
    
    glutMouseWheelFunc([](int wheel, int direction, int x, int y) {
        if (instance) {
            instance->onMouseWheel(wheel, direction, x, y);
        }
        });
   

    
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

    glutLeaveMainLoop();
}

void Engine::render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

   // bitmapHandler.drawBackground();

    gluLookAt(1.5, 1.5, cameraZ, 0.0, 0.0, 0.0, 0.0, 8.0, 0.0);

    glPushMatrix();
    cube.draw();
    glPopMatrix();

    glPushMatrix();
    triangle.updateRotation(deltaTime);
    triangle.updatePosition();
    triangle.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(linePosX, linePosY, 0.0f);
    line.draw();  
    PrimitiveDrawer::drawPoint(pointX, pointY, pointZ, 5.0f);
    glPopMatrix();

    gluLookAt(3.0, 3.0, cameraZ, 5.0, 0.0, 0.0, 0.0, 3.0, 2.0);

    glutSwapBuffers();
}

bool Engine::isPointNearLine(float px, float py, float x1, float y1, float x2, float y2, float threshold) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float lengthSq = dx * dx + dy * dy;
    float projection = ((px - x1) * dx + (py - y1) * dy) / lengthSq;

    if (projection < 0.0f || projection > 1.0f) {
        return false; 
    }

    float closestX = x1 + projection * dx;
    float closestY = y1 + projection * dy;

    float distSq = (px - closestX) * (px - closestX) + (py - closestY) * (py - closestY);
    return distSq <= threshold * threshold;
}

void Engine::onKeyboard(unsigned char key, int x, int y) {
    if (key == 27) { 
        stop();
    }
    player.handleInput(key);
    glutPostRedisplay(); 
}

void Engine::specialKeyboardCallback(int key, int x, int y) {
    if (instance) {
        instance->onSpecialKeyboard(key, x, y);
    }
}

void Engine::onSpecialKeyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        player.handleInput('U'); 
        break;
    case GLUT_KEY_DOWN:
        player.handleInput('C');
        break;
    case GLUT_KEY_LEFT:
        player.handleInput('L');
        break;
    case GLUT_KEY_RIGHT:
        player.handleInput('R');
        break;
    }
    glutPostRedisplay();
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

        float lineStartX, lineStartY, lineStartZ, lineEndX, lineEndY, lineEndZ;
        line.getStart(lineStartX, lineStartY, lineStartZ);
        line.getEnd(lineEndX, lineEndY, lineEndZ);

        pointX += dx;
        pointY += dy;

        line.setStart(lineStartX + dx, lineStartY + dy, lineStartZ);
        line.setEnd(lineEndX + dx, lineEndY + dy, lineEndZ);

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}

void Engine::idleCallback() {
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; 
    float deltaTime = currentTime - instance->lastTime;     
    instance->lastTime = currentTime;

    instance->player.update(deltaTime); 
    glutPostRedisplay();               
}

void Engine::renderCallback() {
    if (instance) {
        instance->render();
    }
}

void Engine::cleanup() {
    std::cout << "Engine shutting down.\n";
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
void Engine::onMouseWheel(int wheel, int direction, int x, int y) {
 
    if (direction > 0) {
        cameraZ -= 1.0f; 
    }
    else if (direction < 0) {
        cameraZ += 1.0f; 
    }

    if (cameraZ < minCameraZ) {
        cameraZ = minCameraZ;
    }
    else if (cameraZ > maxCameraZ) {
        cameraZ = maxCameraZ;
    }

    glutPostRedisplay(); 
}

