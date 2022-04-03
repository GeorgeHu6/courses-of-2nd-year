#include <GL/freeglut.h>
#include <cmath>
#include <ctime>
#include <iostream>

struct line {
    int x0, y0, x1, y1;
};

line lines[50000];

struct scrPt {
    GLint x, y;
};

void setPixel(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

inline int round(const float a) { return int(a + 0.5); }

void lineDDA(int x0, int y0, int xEnd, int yEnd) {
    int dx = xEnd - x0, dy = yEnd - y0, steps, k;
    float xIncrement, yIncrement, x = x0, y = y0;

    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    xIncrement = float(dx) / steps;
    yIncrement = float(dy) / steps;

    setPixel(round(x), round(y));
    for (k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;
        setPixel(round(x), round(y));
    }
}

void lineDDA_improved(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0, dy = y1 - y0;
    int xIncrement, yIncrement;
    int x = x0, y = y0;
    float k;
    float res = 0.5f;

    if (fabs(dx) > fabs(dy)) {
        k = (float) dy / dx;
        xIncrement = dx > 0 ? 1 : -1;
        yIncrement = dy > 0 ? 1 : -1;
        res = xIncrement < 0 ? -0.5f : 0.5f;
        setPixel(x, y);
        while (x != x1) {
            x += xIncrement;
            res += k;
            if (res >= 1) {
                res--;
                y += yIncrement;
            } else if (res <= -1) {
                res++;
                y += yIncrement;
            }

            setPixel(x, y);
        }
    } else {
        k = (float) dx / dy;
        yIncrement = dy > 0 ? 1 : -1;
        xIncrement = dx > 0 ? 1 : -1;
        res = yIncrement < 0 ? -0.5f : 0.5f;
        setPixel(x, y);
        while (y != y1) {
            y += yIncrement;
            res += k;
            if (res >= 1) {
                res--;
                x += xIncrement;
            } else if (res <= -1) {
                res++;
                x += xIncrement;
            }
            setPixel(x, y);
        }
    }
}

void brensenham(int x0, int y0, int x1, int y1) {
    int dy = y1 - y0, dx = x1 - x0;
    int stepx, stepy;
    if (dy < 0) {
        dy = -dy, stepy = -1;
    } else {
        stepy = 1;
    }

    if (dx < 0) {
        dx = -dx, stepx = -1;
    } else {
        stepx = 1;
    }

    dy <<= 1;
    dx <<= 1;
    setPixel(x0, y0);
    if (dx > dy) {
        int fraction = dy - (dx >> 1);
        while (x0 != x1) {
            if (fraction >= 0) {
                y0 += stepy;
                fraction -= dx;
            }
            x0 += stepx;
            fraction += dy;
            setPixel(x0, y0);
        }
    } else {
        int fraction = dx - (dy >> 1);
        while (y0 != y1) {
            if (fraction >= 0) {
                x0 += stepx;
                fraction -= dy;
            }
            y0 += stepy;
            fraction += dx;
            setPixel(x0, y0);
        }
    }
}

//Bresenham line draw
void lineBres(int x0, int y0, int x1, int y1) {
    int dx = fabs(x1 - x0), dy = fabs(y1 - y0);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
    int x, y;

    glBegin(GL_POINTS);
    if (x0 > x1) x = x1, y = y1, x1 = x0;
    else x = x0, y = y0;
    glVertex2i(x, y);

    while (x < x1) {
        x++;
        if (p < 0) {
            p += twoDy;
        } else {
            y++;
            p += twoDyMinusDx;
        }
        glVertex2i(x, y);
    }
    glEnd();
}

void lineDraw_test(void) {
//    clock_t start = clock(), finish;
//    //DDA line draw
//    glClear(GL_COLOR_BUFFER_BIT);
//    for (int i = 0; i < 50000; i++) {
//        lineDDA(lines[i].x0, lines[i].y0, lines[i].x1, lines[i].y1);
//    }
//    glFlush();
//    finish = clock();
//    std::cout << "DDA lineDraw: " << (double) (finish - start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
//
//    start = clock();
//    glClear(GL_COLOR_BUFFER_BIT);
//    for (int i = 0; i < 50000; i++) {
//        brensenham(lines[i].x0, lines[i].y0, lines[i].x1, lines[i].y1);
//    }
//    glFlush();
//    finish = clock();
//    std::cout << "Bresenham lineDraw: " << (double) (finish - start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
//
//
//    //OpenGL line draw
//    start = clock();
//    glClear(GL_COLOR_BUFFER_BIT);
//    glBegin(GL_LINES);
//    for (int i = 0; i < 50000; i++) {
//        glVertex2i(lines[i].x0, lines[i].y0);
//        glVertex2i(lines[i].x1, lines[i].y1);
//    }
//    glEnd();
//    glFlush();
//    finish = clock();
//    std::cout << "OpenGL lineDraw: " << (double) (finish - start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
    lineDDA_improved(400, 30, 30, 40);
    lineDDA_improved(30, 40, 400, 30);
    glFlush();
    glClear(GL_COLOR_BUFFER_BIT);
}

void circlePlotPoints(scrPt circCtr, scrPt circPt) {
    setPixel(circCtr.x + circPt.x, circCtr.y + circPt.y);
    setPixel(circCtr.x - circPt.x, circCtr.y + circPt.y);
    setPixel(circCtr.x + circPt.x, circCtr.y - circPt.y);
    setPixel(circCtr.x - circPt.x, circCtr.y - circPt.y);
    setPixel(circCtr.x + circPt.y, circCtr.y + circPt.x);
    setPixel(circCtr.x - circPt.y, circCtr.y + circPt.x);
    setPixel(circCtr.x + circPt.y, circCtr.y - circPt.x);
    setPixel(circCtr.x - circPt.y, circCtr.y - circPt.x);
}

void circleMidpoint(GLint xc, GLint yc, GLint radius) {
    scrPt circPt, tmp;
    GLint p = 1 - radius;
    circPt.x = 0, circPt.y = radius;
    tmp.x = xc, tmp.y = yc;
    circlePlotPoints(tmp, circPt);

    while (circPt.x < circPt.y) {
        (circPt.x)++;
        if (p < 0) {
            p += 2 * circPt.x + 1;
        } else {
            (circPt.y)--;
            p += 2 * (circPt.x - circPt.y) + 1;
        }
        circlePlotPoints(tmp, circPt);
    }
}

void circleDraw_test(void) {
    circleMidpoint(200, 200, 100);
    glFlush();
}

void ellipsePlotPoints(int xc, int yc, int x, int y) {
    setPixel(xc + x, yc + y);
    setPixel(xc - x, yc + y);
    setPixel(xc + x, yc - y);
    setPixel(xc - x, yc - y);
}

void ellipseMidpoint(int xc, int yc, int rx, int ry) {
    int rx2 = rx * rx;
    int ry2 = ry * ry;
    int twoRx2 = 2 * rx2;
    int twoRy2 = 2 * ry2;
    int p;
    int x = 0, y = ry;
    int px = 0, py = twoRx2 * y;
    ellipsePlotPoints(xc, yc, x, y);

    p = round(ry2 - (ry2 * ry) + (0.25 * rx2));
    while (px < py) {
        x++;
        px += twoRy2;
        if (p < 0) {
            p += ry2 + px;
        } else {
            y--;
            py -= twoRx2;
            p += ry2 + px - py;
        }
        ellipsePlotPoints(xc, yc, x, y);
    }

    p = round(ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2);
    while (y > 0) {
        y--;
        py -= twoRx2;
        if (p > 0) {
            p += rx2 - py;
        } else {
            x++;
            px += twoRy2;
            p += rx2 - py + px;
        }
        ellipsePlotPoints(xc, yc, x, y);
    }
}

void ellipseDraw_test(void) {
    ellipseMidpoint(250, 250, 100, 50);
    glFlush();
}


int main(int argc, char *argv[]) {
    line tmp;
    freopen("E:\\Code\\C_code\\GraphicExp\\random_points.txt", "r", stdin);
    for (int i = 0; i < 50000; i++)
        scanf("%d %d %d %d", &(lines[i].x0), &(lines[i].y0), &(lines[i].x1), &(lines[i].y1));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA draw line");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 500, 0, 500);
    std::cout << "Draw 50000 lines test" << std::endl;
    std::cout << "--------------------" << std::endl;
    glutDisplayFunc(lineDraw_test);
    glutMainLoop();

    return 0;
}