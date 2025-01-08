
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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Pozycja œwiat³a
    GLfloat lightPos[] = { 0.0f, 0.0f, 5.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // Parametry sto¿ka
    GLfloat spotDirection[] = { 0.0f, 0.0f, -1.0f }; // Kierunek sto¿ka œwiat³a
    GLfloat spotCutoff = 25.0f; // K¹t odciêcia sto¿ka (w stopniach)
    GLfloat spotExponent = 15.0f; // Eksponent decyduj¹cy o rozmyciu krawêdzi sto¿ka

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);

    // Materia³ trójk¹ta
    GLfloat matAmbient[] = { 0.2f, 0.5f, 0.2f, 1.0f };
    GLfloat matDiffuse[] = { 0.5f, 1.0f, 0.5f, 1.0f };
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matShininess = 30.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

    // Transformacje
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    glScalef(scale, scale, scale);

    // Normalne
    GLfloat normals[] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

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

    glPopMatrix();

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}


void PrimitiveDrawer::drawCube(float scale, float offsetX, float offsetY, float vertices[24], unsigned int indices[36], float normals[24], float colors[24]) {
    glPushMatrix();
    glScalef(scale, scale, scale);
    glTranslatef(offsetX, offsetY, 0.0f);

    if (currentShadingMode == PHONG) {
        // W³¹cz oœwietlenie i œwiat³o
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0); // Œwiat³o punktowe
        glEnable(GL_LIGHT1); // Œwiat³o kierunkowe

        // Ustawienia œwiat³a punktowego
        GLfloat lightPos[] = { 1.0f, 1.0f, 5.0f, 1.0f };
        GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat lightDiffuse[] = { 0.8f, 0.0f, 0.0f, 1.0f }; // Czerwone œwiat³o
        GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

        // Ustawienia œwiat³a kierunkowego
        GLfloat dirLightDirection[] = { -1.0f, -1.0f, -1.0f }; // Kierunek œwiat³a (w dó³ i na lewo)
        GLfloat dirLightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        GLfloat dirLightDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
        GLfloat dirLightSpecular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
        glLightfv(GL_LIGHT1, GL_POSITION, dirLightDirection); // Kierunek œwiat³a kierunkowego
        glLightfv(GL_LIGHT1, GL_AMBIENT, dirLightAmbient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, dirLightDiffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, dirLightSpecular);

        // Ustawienia materia³u
        GLfloat matAmbient[] = { 0.2f, 0.0f, 0.0f, 1.0f }; // Czerwony ambient
        GLfloat matDiffuse[] = { 0.8f, 0.0f, 0.0f, 1.0f }; // Czerwony diffuse
        GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat matShininess = 50.0f;
        glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

        // W³¹cz tablice wierzcho³ków i normalnych
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glNormalPointer(GL_FLOAT, 0, normals);

        // Rysowanie elementów
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);

        // Wy³¹cz oœwietlenie po rysowaniu
        glDisable(GL_LIGHT1); // Wy³¹cz œwiat³o kierunkowe
        glDisable(GL_LIGHT0); // Wy³¹cz œwiat³o punktowe
        glDisable(GL_LIGHTING);
    }
    else {
        // Tryb Flat lub Gouraud (pozostawiony bez zmian)
        if (currentShadingMode == FLAT) {
            glShadeModel(GL_FLAT);
        }
        else if (currentShadingMode == GOURAUD) {
            glShadeModel(GL_SMOOTH);
        }

        // W³¹cz tablice wierzcho³ków
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glNormalPointer(GL_FLOAT, 0, normals);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
    }

    glPopMatrix();
}



void PrimitiveDrawer::drawCubeNew(float scale, float offsetX, float offsetY, BitmapHandler& bitmapHandler) {
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(offsetX, offsetY, 0.0f);
    glScalef(scale, scale, scale);

    // Przednia œciana
    glBindTexture(GL_TEXTURE_2D, bitmapHandler.texture2);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glEnd();

    // Tylna œciana
    glBindTexture(GL_TEXTURE_2D, bitmapHandler.texture3);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();

    // Lewa œciana
    glBindTexture(GL_TEXTURE_2D, bitmapHandler.texture4);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();

    // Prawa œciana
    glBindTexture(GL_TEXTURE_2D, bitmapHandler.texture5);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();

    // Górna œciana
    glBindTexture(GL_TEXTURE_2D, bitmapHandler.texture6);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();

    // Dolna œciana
    glBindTexture(GL_TEXTURE_2D, bitmapHandler.texture7);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

