/*
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
*/
#include "PrimitiveDrawer.h"
#include "Cube.h"
#include <memory>

PrimitiveDrawer::ShadingMode PrimitiveDrawer::currentShadingMode = PrimitiveDrawer::GOURAUD;

void PrimitiveDrawer::setShadingMode(ShadingMode mode) {
    
    currentShadingMode = mode;
}

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
    glTranslatef(offsetX, offsetY, 0.0f);

    // W zale�no�ci od trybu cieniowania ustaw odpowiedni model
    if (currentShadingMode == FLAT) {
        glShadeModel(GL_FLAT); // Cieniowanie p�askie
    }
    else if (currentShadingMode == GOURAUD) {
        glShadeModel(GL_SMOOTH); // Cieniowanie Gouroda
    }
    else if (currentShadingMode == PHONG) {
        // Cieniowanie Phonga
        // W��czenie o�wietlenia
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        // Ustawienie �wiat�a
        GLfloat lightPos[] = { 1.0f, 1.0f, 8.0f, 1.0f }; // Pozycja �wiat�a
        GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Ambient light
        GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Diffuse light
        GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Specular light
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

        // Parametry materia�u
        GLfloat matAmbient[] = { 0.10f, 0.2f, 0.5f, 1.0f };
        GLfloat matDiffuse[] = { 0.5f, 0.5f, 1.0f, 1.0f };
        GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat matShininess = 50.0f;
        glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

        // Ustawienie normalnych i wierzcho�k�w
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glNormalPointer(GL_FLOAT, 0, normals);

        // Rysowanie sze�cianu z obliczeniami Phonga
        for (int i = 0; i < 36; i += 3) {
            GLfloat vertex1[] = { vertices[indices[i] * 3], vertices[indices[i] * 3 + 1], vertices[indices[i] * 3 + 2] };
            GLfloat vertex2[] = { vertices[indices[i + 1] * 3], vertices[indices[i + 1] * 3 + 1], vertices[indices[i + 1] * 3 + 2] };
            GLfloat vertex3[] = { vertices[indices[i + 2] * 3], vertices[indices[i + 2] * 3 + 1], vertices[indices[i + 2] * 3 + 2] };
            GLfloat normal1[] = { normals[indices[i] * 3], normals[indices[i] * 3 + 1], normals[indices[i] * 3 + 2] };
            GLfloat normal2[] = { normals[indices[i + 1] * 3], normals[indices[i + 1] * 3 + 1], normals[indices[i + 1] * 3 + 2] };
            GLfloat normal3[] = { normals[indices[i + 2] * 3], normals[indices[i + 2] * 3 + 1], normals[indices[i + 2] * 3 + 2] };

            // Obliczenia o�wietlenia Phonga dla ka�dego tr�jk�ta
            for (int j = 0; j < 3; ++j) {
                GLfloat vertex[] = { vertex1[0], vertex1[1], vertex1[2] };
                GLfloat normal[] = { normal1[0], normal1[1], normal1[2] };

                // Obliczenia o�wietlenia (ambient, diffuse, specular)
                GLfloat ambient[] = { lightAmbient[0] * matAmbient[0], lightAmbient[1] * matAmbient[1], lightAmbient[2] * matAmbient[2] };
                GLfloat diffuse[] = { lightDiffuse[0] * matDiffuse[0], lightDiffuse[1] * matDiffuse[1], lightDiffuse[2] * matDiffuse[2] };
                GLfloat specular[] = { lightSpecular[0] * matSpecular[0], lightSpecular[1] * matSpecular[1], lightSpecular[2] * matSpecular[2] };

                // Normalizacja wektora kierunku �wiat�a
                GLfloat lightDir[] = { lightPos[0] - vertex[0], lightPos[1] - vertex[1], lightPos[2] - vertex[2] };
                GLfloat lightLength = sqrtf(lightDir[0] * lightDir[0] + lightDir[1] * lightDir[1] + lightDir[2] * lightDir[2]);
                lightDir[0] /= lightLength;
                lightDir[1] /= lightLength;
                lightDir[2] /= lightLength;

                // Normalizacja normalnych
                GLfloat normalLength = sqrtf(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
                normal[0] /= normalLength;
                normal[1] /= normalLength;
                normal[2] /= normalLength;

                // Obliczanie komponent�w Phonga
                GLfloat dotLN = normal[0] * lightDir[0] + normal[1] * lightDir[1] + normal[2] * lightDir[2];
                GLfloat diffuseFactor = fmaxf(dotLN, 0.0f);

                GLfloat reflection[] = { 2.0f * normal[0] * dotLN - lightDir[0], 2.0f * normal[1] * dotLN - lightDir[1], 2.0f * normal[2] * dotLN - lightDir[2] };
                GLfloat viewDir[] = { 0.0f, 0.0f, 1.0f }; // Kamer� ustawiamy w (0, 0, 1) wzgl�dem obiektu
                GLfloat dotRV = reflection[0] * viewDir[0] + reflection[1] * viewDir[1] + reflection[2] * viewDir[2];
                GLfloat specularFactor = powf(fmaxf(dotRV, 0.0f), matShininess);

                // Podsumowanie o�wietlenia Phonga
                GLfloat finalColor[] = {
                    ambient[0] + diffuseFactor * diffuse[0] + specularFactor * specular[0],
                    ambient[1] + diffuseFactor * diffuse[1] + specularFactor * specular[1],
                    ambient[2] + diffuseFactor * diffuse[2] + specularFactor * specular[2]
                };

                // Ustawienie koloru wierzcho�ka
                glColor3f(finalColor[0], finalColor[1], finalColor[2]);

                // Rysowanie tr�jk�ta
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
            }
        }

        // Wy��czanie o�wietlenia
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
    }

    glPopMatrix();
}
