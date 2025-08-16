#include <iostream>
#include <cmath>
#include <GL/glut.h>


float rectX1 = 100.0f, rectY1 = 100.0f;
float rectX2 = 200.0f, rectY2 = 100.0f;
float rectX3 = 200.0f, rectY3 = 200.0f;
float rectX4 = 100.0f, rectY4 = 200.0f;


float x_rc = 150.0f;
float y_rc = 150.0f;


float angleDegrees = 60.0f;

float rectX1Rotated, rectY1Rotated;
float rectX2Rotated, rectY2Rotated;
float rectX3Rotated, rectY3Rotated;
float rectX4Rotated, rectY4Rotated;

void rotatePoint(float x, float y, float x_rc, float y_rc, float angleDegrees,
                 float& x_prime, float& y_prime) {
    float angleRadians = angleDegrees * M_PI / 180.0f;

    x_prime = (x - x_rc) * cos(angleRadians) - (y - y_rc) * sin(angleRadians) + x_rc;
    y_prime = (x - x_rc) * sin(angleRadians) + (y - y_rc) * cos(angleRadians) + y_rc;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(rectX1, rectY1);
    glVertex2f(rectX2, rectY2);
    glVertex2f(rectX3, rectY3);
    glVertex2f(rectX4, rectY4);
    glEnd();

    rotatePoint(rectX1, rectY1, x_rc, y_rc, angleDegrees, rectX1Rotated, rectY1Rotated);
    rotatePoint(rectX2, rectY2, x_rc, y_rc, angleDegrees, rectX2Rotated, rectY2Rotated);
    rotatePoint(rectX3, rectY3, x_rc, y_rc, angleDegrees, rectX3Rotated, rectY3Rotated);
    rotatePoint(rectX4, rectY4, x_rc, y_rc, angleDegrees, rectX4Rotated, rectY4Rotated);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(rectX1Rotated, rectY1Rotated);
    glVertex2f(rectX2Rotated, rectY2Rotated);
    glVertex2f(rectX3Rotated, rectY3Rotated);
    glVertex2f(rectX4Rotated, rectY4Rotated);
    glEnd();

    glutSwapBuffers();
}

void init(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_PROJECTION);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Rectangle Rotation");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
