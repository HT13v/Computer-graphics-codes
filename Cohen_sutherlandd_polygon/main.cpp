#include <GL/glut.h>
#include <vector>
using namespace std;

struct Point
{
    float x, y;
};

vector<Point> subjectPolygon =
{
    {250, 100}, {400, 250}, {250, 400}, {100, 250}
};

vector<Point> clipPolygon =
 {
    {200, 200}, {400, 200}, {400, 300}, {200, 300}
};

bool inside(Point p, Point a, Point b)
{
    return (b.x - a.x) * (p.y - a.y) > (b.y - a.y) * (p.x - a.x);
}

Point intersection(Point a, Point b, Point p, Point q)
{
    float A1 = b.y - a.y;
    float B1 = a.x - b.x;
    float C1 = A1 * a.x + B1 * a.y;
    float A2 = q.y - p.y;
    float B2 = p.x - q.x;
    float C2 = A2 * p.x + B2 * p.y;
    float det = A1 * B2 - A2 * B1;
    return { (B2 * C1 - B1 * C2) / det, (A1 * C2 - A2 * C1) / det };
}

vector<Point> sutherlandHodgman(vector<Point> poly, vector<Point> clipper)
 {
    for (size_t i = 0; i < clipper.size(); i++)
        {
        vector<Point> input = poly;
        poly.clear();
        Point A = clipper[i];
        Point B = clipper[(i + 1) % clipper.size()];
        for (size_t j = 0; j < input.size(); j++)
        {
            Point P = input[j];
            Point Q = input[(j + 1) % input.size()];
            if (inside(Q, A, B))
                {
                if (!inside(P, A, B))
                    poly.push_back(intersection(P, Q, A, B));
                poly.push_back(Q);
            }
            else if (inside(P, A, B))
                {
                poly.push_back(intersection(P, Q, A, B));
            }
        }
    }
    return poly;
}

void drawPolygonOutline(const vector<Point>& poly, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (auto& p : poly)
        glVertex2f(p.x, p.y);
    glEnd();
}

void drawPolygonFilled(const vector<Point>& poly, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (auto& p : poly)
        glVertex2f(p.x, p.y);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawPolygonOutline(subjectPolygon, 0.0, 0.0, 1.0);
    drawPolygonOutline(clipPolygon, 1.0, 0.0, 0.0);
    vector<Point> clipped = sutherlandHodgman(subjectPolygon, clipPolygon);
    drawPolygonFilled(clipped, 0.0, 0.0, 1.0);
    glFlush();
}

void init()
 {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 512, 0, 512);
 }

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutCreateWindow("Sutherland-Hodgman Polygon Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
