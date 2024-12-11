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
    // W³¹czenie oœwietlenia i ustawienie materia³u
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // Aktywacja œwiat³a 0 (podstawowe)

    GLfloat lightPos[] = { 0.0f, 0.0f, 5.0f, 1.0f }; // Pozycja œwiat³a
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Sk³adnik ambient
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Sk³adnik rozproszony
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Sk³adnik zwierciadlany

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

    glPushMatrix(); // Zapamiêtanie bie¿¹cej macierzy
    glTranslatef(posX, posY, 0.0f); // Przesuniêcie trójk¹ta na pozycjê
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f); // Obrót wokó³ osi Y
    glScalef(scale, scale, scale);

    // Normalki dla ka¿dego wierzcho³ka
    GLfloat normals[] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    // Rysowanie trzech czêœci trójk¹ta z u¿yciem ró¿nych wierzcho³ków
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

    glPopMatrix(); // Przywrócenie poprzedniej macierzy

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glScalef(scale, scale, scale);
}

void PrimitiveDrawer::drawCube(float scale, float offsetX, float offsetY, float vertices[24], unsigned int indices[36], float normals[24], float colors[24]) {
    glPushMatrix();
    glScalef(scale, scale, scale);
    glTranslatef(offsetX, offsetY, 0.0f); // Przesuniêcie

    // Ustawienia materia³ów
    GLfloat matAmbient[] = { 0.2f, 0.2f, 0.5f, 1.0f };   // Sk³adowa ambientowa
    GLfloat matDiffuse[] = { 0.5f, 0.5f, 1.0f, 1.0f };   // Sk³adowa rozproszona
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Sk³adowa lustrzana
    GLfloat matShininess = 50.0f;                        // Po³ysk

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

    // W³¹czenie oœwietlenia
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Konfiguracja Ÿród³a œwiat³a
    GLfloat lightPos[] = { 1.0f, 1.0f, 1.0f, 1.0f };     // Pozycja œwiat³a
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Sk³adowa ambient
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Sk³adowa rozproszona
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Sk³adowa lustrzana

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Aktywacja tablic wierzcho³ków i normalnych
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);

    // Rysowanie szeœcianu
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);

    // Wy³¹czenie tablic
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    // Wy³¹czenie oœwietlenia
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    glPopMatrix();
}