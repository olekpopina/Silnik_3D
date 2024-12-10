#include "Triangle.h"
#include <fstream>

Triangle::Triangle() : posX(0.0f), posY(0.0f), rotationAngle(0.0f), scale(1.0f), isRotating(false) {
    // Ustawienia kolor�w dla wierzcho�k�w
    float initialColors[] = {
        1.0f, 0.0f, 0.0f,  // Czerwony
        0.0f, 1.0f, 0.0f,  // Zielony
        0.0f, 0.0f, 1.0f   // Niebieski
    };
    std::copy(std::begin(initialColors), std::end(initialColors), colors);

    // Wierzho�ki tr�jk�t�w
    float initialVertices1[] = {
        0.0f,  0.5f, 0.0f,  // G�rny wierzcho�ek
       -0.5f, -0.5f, -0.5f, // Lewy dolny
        0.5f, -0.5f, -0.5f  // Prawy dolny
    };
    std::copy(std::begin(initialVertices1), std::end(initialVertices1), vertices1);

    float initialVertices2[] = {
        0.0f,  0.5f, 0.0f,  // G�rny wierzcho�ek
        0.5f, -0.5f, -0.5f, // Lewy dolny
        0.0f, -0.5f,  0.5f  // Prawy dolny
    };
    std::copy(std::begin(initialVertices2), std::end(initialVertices2), vertices2);

    float initialVertices3[] = {
        0.0f,  0.5f, 0.0f,  // G�rny wierzcho�ek
        0.0f, -0.5f,  0.5f, // Lewy dolny
       -0.5f, -0.5f, -0.5f  // Prawy dolny
    };
    std::copy(std::begin(initialVertices3), std::end(initialVertices3), vertices3);

}

void Triangle::draw() {
    // W��czenie o�wietlenia i ustawienie materia�u
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // Aktywacja �wiat�a 0 (podstawowe)

    GLfloat lightPos[] = { 0.0f, 0.0f, 5.0f, 1.0f }; // Pozycja �wiat�a
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Sk�adnik ambient
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Sk�adnik rozproszony
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Sk�adnik zwierciadlany

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    GLfloat matAmbient[] = { 0.2f, 0.5f, 0.2f, 1.0f };
    GLfloat matDiffuse[] = { 0.5f, 1.0f, 0.5f, 1.0f };
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matShininess = 30.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

    glPushMatrix(); // Zapami�tanie bie��cej macierzy
    glTranslatef(posX, posY, 0.0f); // Przesuni�cie tr�jk�ta na pozycj�
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f); // Obr�t wok� osi Y
    glScalef(scale, scale, scale);

    // Normalki dla ka�dego wierzcho�ka
    GLfloat normals[] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    // Rysowanie trzech cz�ci tr�jk�ta z u�yciem r�nych wierzcho�k�w
    glVertexPointer(3, GL_FLOAT, 0, vertices1);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glVertexPointer(3, GL_FLOAT, 0, vertices2);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glVertexPointer(3, GL_FLOAT, 0, vertices3);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glPopMatrix(); // Przywr�cenie poprzedniej macierzy

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glScalef(scale, scale, scale);
}

void Triangle::scale_Up() {
    scale *= 1.1f; // Zwi�kszamy skal� o 10%
}

void Triangle::scale_Down() {
    scale *= 0.9f; // Zmniejszamy skal� o 10%
}


void Triangle::setRotation(bool rotating) {
    isRotating = rotating;
}

void Triangle::setPosition(float x, float y) {
    posX = x; // Ustawia pozycj� X
    posY = y; // Ustawia pozycj� Y
}

void Triangle::updateRotation(float deltaTime) {
    if (isRotating) {
        rotationAngle += rotationSpeed * deltaTime;
        if (rotationAngle > 360.0f) {
            rotationAngle -= 360.0f; // Resetowanie k�ta
        }
    }
}

void Triangle::updatePosition() {
    // Mo�esz doda� logik� aktualizacji pozycji, je�li b�dzie to potrzebne
}




