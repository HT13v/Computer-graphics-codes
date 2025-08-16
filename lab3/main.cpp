#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

int r; // Circle radius

void display(void) {
    int x = 0, y = r;
    int p = 3 - (2 * r); // Initial decision parameter

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);

    while (x <= y) {
        // Plot the eight symmetric points
        glVertex2f(x / 100.0, y / 100.0);
        glVertex2f(y / 100.0, x / 100.0);
        glVertex2f(-x / 100.0, y / 100.0);
        glVertex2f(-y / 100.0, x / 100.0);
        glVertex2f(x / 100.0, -y / 100.0);
        glVertex2f(y / 100.0, -x / 100.0);
        glVertex2f(-x / 100.0, -y / 100.0);
        glVertex2f(-y / 100.0, -x / 100.0);

        // Bresenham’s decision parameter update
        if (p < 0) {
            p += (4 * x) + 6;
        } else {
            p += (4 * (x - y)) + 10;
            y--;
        }
        x++;
    }

    glEnd();
    glFlush();
}

void init(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    printf("Enter radius: ");
    scanf("%d", &r);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Circle Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
