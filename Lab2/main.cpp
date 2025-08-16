#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

int x_start, y_start, x_end, y_end;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int dx = abs(x_end - x_start);
    int dy = abs(y_end - y_start);
    int sx = (x_end > x_start) ? 1 : -1;
    int sy = (y_end > y_start) ? 1 : -1;

    int err = dx - dy;
    int x = x_start, y = y_start;

    printf("Next pixel plotting:\n");
    glBegin(GL_POINTS);
    while (x != x_end || y != y_end) {
        printf("(%d, %d)\n", x, y);
        glVertex2i(x, y);

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
    printf("(%d, %d)\n", x, y);
    glVertex2i(x, y);
    glEnd();

    glFlush();
}

void myInit() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int main(int argc, char **argv) {
    printf("Enter x1 y1 x2 y2: ");
    scanf("%d %d %d %d", &x_start, &y_start, &x_end, &y_end);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 500);
    glutCreateWindow("Bresenham's Line Algorithm");

    glutDisplayFunc(display);
    myInit();
    glutMainLoop();

    return 0;
}
