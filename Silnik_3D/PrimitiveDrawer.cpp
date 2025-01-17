
#include "PrimitiveDrawer.h"
#include "Cube.h"
#include <memory>

PrimitiveDrawer::ShadingMode PrimitiveDrawer::currentShadingMode = PrimitiveDrawer::GOURAUD;

GLuint PrimitiveDrawer::textures[6];
int PrimitiveDrawer::textureSet;

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

    // Pozycja �wiat�a
    GLfloat lightPos[] = { 0.0f, 0.0f, 5.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // Parametry sto�ka
    GLfloat spotDirection[] = { 0.0f, 0.0f, -1.0f }; // Kierunek sto�ka �wiat�a
    GLfloat spotCutoff = 25.0f; // K�t odci�cia sto�ka (w stopniach)
    GLfloat spotExponent = 15.0f; // Eksponent decyduj�cy o rozmyciu kraw�dzi sto�ka

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);

    // Materia� tr�jk�ta
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
        // W��cz o�wietlenie i �wiat�o
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0); // �wiat�o punktowe
        glEnable(GL_LIGHT1); // �wiat�o kierunkowe

        // Ustawienia �wiat�a punktowego
        GLfloat lightPos[] = { 1.0f, 1.0f, 5.0f, 1.0f };
        GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat lightDiffuse[] = { 0.8f, 0.0f, 0.0f, 1.0f }; // Czerwone �wiat�o
        GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

        // Ustawienia �wiat�a kierunkowego
        GLfloat dirLightDirection[] = { -1.0f, -1.0f, -1.0f }; // Kierunek �wiat�a (w d� i na lewo)
        GLfloat dirLightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        GLfloat dirLightDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
        GLfloat dirLightSpecular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
        glLightfv(GL_LIGHT1, GL_POSITION, dirLightDirection); // Kierunek �wiat�a kierunkowego
        glLightfv(GL_LIGHT1, GL_AMBIENT, dirLightAmbient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, dirLightDiffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, dirLightSpecular);

        // Ustawienia materia�u
        GLfloat matAmbient[] = { 0.2f, 0.0f, 0.0f, 1.0f }; // Czerwony ambient
        GLfloat matDiffuse[] = { 0.8f, 0.0f, 0.0f, 1.0f }; // Czerwony diffuse
        GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat matShininess = 50.0f;
        glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

        // W��cz tablice wierzcho�k�w i normalnych
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glNormalPointer(GL_FLOAT, 0, normals);

        // Rysowanie element�w
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);

        // Wy��cz o�wietlenie po rysowaniu
        glDisable(GL_LIGHT1); // Wy��cz �wiat�o kierunkowe
        glDisable(GL_LIGHT0); // Wy��cz �wiat�o punktowe
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

        // W��cz tablice wierzcho�k�w
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


    switch (textureSet) {
    case 1: // Zestaw tekstur 1
        textures[0] = bitmapHandler.texture2; // Przednia
        textures[1] = bitmapHandler.texture3; // Tylna
        textures[2] = bitmapHandler.texture4; // Lewa
        textures[3] = bitmapHandler.texture5; // Prawa
        textures[4] = bitmapHandler.texture6; // G�rna
        textures[5] = bitmapHandler.texture7; // Dolna
        break;
    case 2: // Zestaw tekstur 2
        textures[0] = bitmapHandler.texture3; // Przednia
        textures[1] = bitmapHandler.texture4; // Tylna
        textures[2] = bitmapHandler.texture5; // Lewa
        textures[3] = bitmapHandler.texture6; // Prawa
        textures[4] = bitmapHandler.texture7; // G�rna
        textures[5] = bitmapHandler.texture2; // Dolna
        break;
    case 3: // Zestaw tekstur 2
        textures[0] = bitmapHandler.texture4; // Przednia
        textures[1] = bitmapHandler.texture3; // Tylna
        textures[2] = bitmapHandler.texture5; // Lewa
        textures[3] = bitmapHandler.texture6; // Prawa
        textures[4] = bitmapHandler.texture7; // G�rna
        textures[5] = bitmapHandler.texture2; // Dolna
        break;
    case 4: // Zestaw tekstur 2
        textures[0] = bitmapHandler.texture5; // Przednia
        textures[1] = bitmapHandler.texture4; // Tylna
        textures[2] = bitmapHandler.texture3; // Lewa
        textures[3] = bitmapHandler.texture6; // Prawa
        textures[4] = bitmapHandler.texture7; // G�rna
        textures[5] = bitmapHandler.texture2; // Dolna
        break;
    case 5: // Zestaw tekstur 2
        textures[0] = bitmapHandler.texture6; // Przednia
        textures[1] = bitmapHandler.texture3; // Tylna
        textures[2] = bitmapHandler.texture5; // Lewa
        textures[3] = bitmapHandler.texture4; // Prawa
        textures[4] = bitmapHandler.texture7; // G�rna
        textures[5] = bitmapHandler.texture2; // Dolna
        break;
    case 6: // Zestaw tekstur 2
        textures[0] = bitmapHandler.texture7; // Przednia
        textures[1] = bitmapHandler.texture3; // Tylna
        textures[2] = bitmapHandler.texture5; // Lewa
        textures[3] = bitmapHandler.texture6; // Prawa
        textures[4] = bitmapHandler.texture4; // G�rna
        textures[5] = bitmapHandler.texture2; // Dolna
        break;
    default: // Domy�lny zestaw tekstur
        textures[0] = bitmapHandler.texture2;
        textures[1] = bitmapHandler.texture3;
        textures[2] = bitmapHandler.texture4;
        textures[3] = bitmapHandler.texture5;
        textures[4] = bitmapHandler.texture6;
        textures[5] = bitmapHandler.texture7;
        break;
    }

    glPushMatrix();
    glTranslatef(offsetX, offsetY, 0.0f);
    glScalef(scale, scale, scale);
    // Przednia �ciana
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glEnd();
   
    // Tylna �ciana
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();

    // Lewa �ciana
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();

    // Prawa �ciana
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();

    // G�rna �ciana
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();

    // Dolna �ciana
    glBindTexture(GL_TEXTURE_2D, textures[5]);
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

