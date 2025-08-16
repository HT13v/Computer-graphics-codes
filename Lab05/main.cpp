#include <GL/glut.h>
using namespace std;
const int pixelSize = 5;
const int screenWidth = 600, screenHeight = 400;
const int charWidth = 7, charHeight = 7;
void drawPixel(int x, int y) {
glBegin(GL_QUADS);
glVertex2i(x * pixelSize, y * pixelSize);
glVertex2i((x + 1) * pixelSize, y * pixelSize);
glVertex2i((x + 1) * pixelSize, (y + 1) * pixelSize);
glVertex2i(x * pixelSize, (y + 1) * pixelSize);
glEnd();
}
void drawLine(int x1, int y1, int x2, int y2) {
int dx = x2 - x1;
int dy = y2 - y1;
int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
float Xinc = (float)dx / steps;
float Yinc = (float)dy / steps;
float x = x1;
float y = y1;
for (int i = 0; i <= steps; i++) {
drawPixel(x, y);
x += Xinc;
y += Yinc;
}
}
void drawDynamicBitmapA(int startX, int startY) {
for (int y = 0; y < charHeight; y++) {
for (int x = 0; x < charWidth; x++) {
if (x == 0 || x == charWidth - 1 || y == charHeight / 2 ) {
drawPixel(startX + x, startY - y);
}
}
}
}
void display() {
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0, 1.0, 1.0);
drawDynamicBitmapA(5, 10);
glFlush();
}
void init() {
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0, screenWidth, 0, screenHeight);
glClearColor(0.0, 0.0, 0.0, 1.0);
glColor3f(1.0, 1.0, 1.0);
}
int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(screenWidth, screenHeight);
glutCreateWindow("Bitmap Outline Method");
init();
glutDisplayFunc(display);
glutMainLoop();
return 0;
}
