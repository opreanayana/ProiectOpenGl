#include <windows.h>
#include "gl.h"
#include "glu.h"
#include "glaux.h"
#include <math.h>

float angleY = 0.0f;
const float radius = 15.0f;
float cameraHeight = 6.0f;
float bookAngle = 0.0f;
float lampshadeAngle = 0.0f;

GLUquadric* quad;

void drawBase() {
    glPushMatrix();
    glColor3f(0.6f, 0.6f, 0.6f);
    glTranslatef(0.0f, 0.1f, 0.0f);
    glScalef(3.5f, 0.5f, 1.5f);
    auxSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6f, 0.6f, 0.6f);
    glTranslatef(0.0f, 0.3f, 0.0f);
    glScalef(2.6f, 0.5f, 1.5f);
    auxSolidCube(1.0);
    glPopMatrix();
}

void drawBezierPole() {
    GLfloat ctrlPoints[4][3] = {
        { 0.0f, 0.3f, 0.0f },
        { 0.0f, 2.0f, 0.0f },
        { 0.0f, 3.5f, 0.0f },
        { 0.0f, 5.1f, 0.0f }
    };

    glPushMatrix();
    glColor3f(0.6f, 0.6f, 0.6f);
    glLineWidth(8.0f);
    glMap1f(GL_MAP1_VERTEX_3, 0.0f, 1.0f, 3, 4, &ctrlPoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 30; i++) {
        glEvalCoord1f((GLfloat)i / 30.0f);
    }
    glEnd();
    glDisable(GL_MAP1_VERTEX_3);
    glPopMatrix();
}

void drawLampshade() {
    glPushMatrix();
    glTranslatef(0.0f, 5.1f, 0.0f);
    glRotatef(lampshadeAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    gluCylinder(quad, 2.0, 0.9, 2.5, 30, 1);
    glPopMatrix();
}

void drawBook() {
    glPushMatrix();
    glRotatef(bookAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(3.5f, 0.45f, 0.0f);

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glScalef(1.6f, 0.15f, 1.2f);
    auxSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.0f);
    glColor3f(0.95f, 0.95f, 0.95f);
    glScalef(1.7f, 0.05f, 1.3f);
    auxSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
}

void drawText() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(350, 100);
    auxDrawStr("Oprean Ayana");
    glEnable(GL_LIGHTING);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void CALLBACK display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float cameraX = radius * sin(angleY);
    float cameraZ = radius * cos(angleY);

    gluLookAt(cameraX, cameraHeight, cameraZ,
        0.0, 2.5, 0.0,
        0.0, 1.0, 0.0);

    drawBase();
    drawBezierPole();
    drawLampshade();
    drawBook();
    drawText();

    auxSwapBuffers();
}

void CALLBACK reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myinit() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat position[] = { 3.0f, 5.0f, 5.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    auxCreateFont();
}

void CALLBACK RotesteStanga() { angleY -= 0.05f; }
void CALLBACK RotesteDreapta() { angleY += 0.05f; }
void CALLBACK MutaSus() { cameraHeight += 0.5f; }
void CALLBACK MutaJos() { cameraHeight -= 0.5f; }

void CALLBACK RotesteCartea() {
    bookAngle += 5.0f;
    if (bookAngle >= 360.0f)
        bookAngle -= 360.0f;
    display();
}


void CALLBACK idle() {
    lampshadeAngle += 0.2f;
    if (lampshadeAngle >= 360.0f)
        lampshadeAngle -= 360.0f;
    display();
}

int main() {
    auxInitDisplayMode(AUX_RGB | AUX_DEPTH | AUX_DOUBLE);
    auxInitPosition(100, 100, 800, 600);
    auxInitWindow("Lampa");

    myinit();
    auxReshapeFunc(reshape);

    auxKeyFunc(AUX_LEFT, RotesteStanga);
    auxKeyFunc(AUX_RIGHT, RotesteDreapta);
    auxKeyFunc(AUX_UP, MutaSus);
    auxKeyFunc(AUX_DOWN, MutaJos);
    auxKeyFunc('r', RotesteCartea);
    
    auxIdleFunc(idle);
    auxMainLoop(display);
    return 0;
}
