#include <GL/glut.h>
#include <math.h>
float a = 0.5f;
float b = 0.3f;
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    for (float t = 0.0f; t <= 2.0f * M_PI; t += 0.01f) {
        float x = a * cos(t);
        float y = b * sin(t);
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();
}
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Ellipse using Polynomial Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
