#include "PrimitiveDrawer.h"

void PrimitiveDrawer::drawPoint(float x, float y, float z, float size) {
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
}

void PrimitiveDrawer::drawLine(float x1, float y1, float z1, float x2, float y2, float z2, float width) {
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glEnd();
}

void PrimitiveDrawer::drawTriangle(float vertices1[9], float vertices2[9], float vertices3[9], float colors[9], float posX, float posY, float scale, float rotationAngle) {
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

void PrimitiveDrawer::drawCube(float scale, float offsetX, float offsetY, float vertices[24], unsigned int indices[36], float normals[24], float colors[24]) {
    glPushMatrix();
    glScalef(scale, scale, scale);
    glTranslatef(offsetX, offsetY, 0.0f); // Przesuni�cie

    // Ustawienia materia��w
    GLfloat matAmbient[] = { 0.2f, 0.2f, 0.5f, 1.0f };   // Sk�adowa ambientowa
    GLfloat matDiffuse[] = { 0.5f, 0.5f, 1.0f, 1.0f };   // Sk�adowa rozproszona
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Sk�adowa lustrzana
    GLfloat matShininess = 50.0f;                        // Po�ysk

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

    // W��czenie o�wietlenia
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Konfiguracja �r�d�a �wiat�a
    GLfloat lightPos[] = { 1.0f, 1.0f, 1.0f, 1.0f };     // Pozycja �wiat�a
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Sk�adowa ambient
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Sk�adowa rozproszona
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Sk�adowa lustrzana

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Aktywacja tablic wierzcho�k�w i normalnych
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);

    // Rysowanie sze�cianu
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);

    // Wy��czenie tablic
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    // Wy��czenie o�wietlenia
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    glPopMatrix();
}