#include <GL/freeglut.h>
#include <cmath>
#include <ctime>
#include <random>
#include <iostream>

struct line {
    int x0, y0, x1, y1;

    line(int i, int i1, int i2, int i3) {
        x0 = i, y0 = i1, x1 = i2, y1 = i3;
    }

    line() {}
};

line lines[50000];

struct scrPt {
    GLint x, y;
};

void setPixel(GLint x, GLint y) {
    glVertex2i(x, y);
}

inline int round(const float a) { return int(a + 0.5); }

// 标准DDA画线算法
void lineDDA(int x0, int y0, int xEnd, int yEnd) {
    int dx = xEnd - x0, dy = yEnd - y0, steps, k;
    float xIncrement, yIncrement, x = x0, y = y0;

    // 斜率绝对值小于1，沿x轴递进，每一列画一个点
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else// 斜率绝对值大于1，沿y轴递进，每一行画一个点
        steps = fabs(dy);
    // 计算增量
    xIncrement = float(dx) / steps;
    yIncrement = float(dy) / steps;

    // 先画好第一个点
    setPixel(round(x), round(y));
    // 逐点绘画，共steps步，加上第一个点刚好steps+1步
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

// bresenham算法画线
void bresenham(int x0, int y0, int x1, int y1) {
    int dy = y1 - y0, dx = x1 - x0;
    int stepx, stepy;
    // 根据Δx和Δy的符号判断决策参数增量式()2Δy()2Δx(y(k+1)-y(k))两项前的正负
    // 并确定x与y的递进方向
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

    // 通过位移乘2，更快
    dy <<= 1;
    dx <<= 1;
    // 先画起点
    setPixel(x0, y0);
    // 不使用round取整，使用fraction记录每次加法的小数部分，有进位时才+1
    if (dx > dy) {// 斜率绝对值小于1
        int fraction = dy - (dx >> 1);
        while (x0 != x1) {
            // 小数部分的进位操作
            if (fraction >= 0) {
                y0 += stepy;
                fraction -= dx;
            }
            // x步进
            x0 += stepx;
            // 决策参数加上递增量
            fraction += dy;
            setPixel(x0, y0);
        }
    } else {// 斜率绝对值大于1，与上面类似
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
    //获取随机数发生器以生成随机种子
    std::random_device rd;
    //生成种子
    std::mt19937 gen(rd());
    //随机数生成器，生成[0,500]中的随机整数
    std::uniform_int_distribution<> dis(0, 500);
    //生成50000对随机点，作为50000条线的起点与终点
    for (int i = 0; i < 50000; i++) {
        lines[i] = line(dis(gen), dis(gen), dis(gen), dis(gen));
    }
    clock_t start, finish;


    //普通DDA算法画线
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    start = clock();
    for (int i = 0; i < 50000; i++) {
        lineDDA(lines[i].x0, lines[i].y0, lines[i].x1, lines[i].y1);
    }

    glFlush();
    glEnd();
    finish = clock();
    std::cout << "DDA normal lineDraw: " << (double) (finish - start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

    //bresenham算法画线
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    start = clock();
    for (int i = 0; i < 50000; i++) {
        bresenham(lines[i].x0, lines[i].y0, lines[i].x1, lines[i].y1);
    }
    glEnd();
    glFlush();
    finish = clock();

    std::cout << "Bresenham lineDraw: " << (double) (finish - start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

    //改进的DDA算法画线
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    start = clock();
    for (int i = 0; i < 50000; i++) {
        lineDDA_improved(lines[i].x0, lines[i].y0, lines[i].x1, lines[i].y1);
    }
    glEnd();
    glFlush();
    finish = clock();
    std::cout << "DDA improved lineDraw: " << (double) (finish - start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

    //OpenGL自带画线函数画线
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    start = clock();
    for (int i = 0; i < 50000; i++) {
        glVertex2i(lines[i].x0, lines[i].y0);
        glVertex2i(lines[i].x1, lines[i].y1);
    }
    glEnd();
    glFlush();
    finish = clock();
    std::cout << "OpenGL inner function: " << (double) (finish - start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
}

// 依据圆的对称性，同时可以画出8个八分之一圆
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

// 中点圆算法，以(xc, yc)为圆心，radius为半径画圆
// 从画第二象限（共分为8个象限）的八分之一圆出发，根据对称性画出其他部分
void circleMidpoint(GLint xc, GLint yc, GLint radius) {
    scrPt circPt, tmp;
    GLint p = 1 - radius;
    // circPt起始于圆的上边界点
    circPt.x = 0, circPt.y = radius;
    tmp.x = xc, tmp.y = yc;
    circlePlotPoints(tmp, circPt);

    // 只画八分之一圆，即画到y=x直线处即可
    while (circPt.x < circPt.y) {
        // 沿x方向递进
        (circPt.x)++;
        // 根据决策参数p确定要画的点
        if (p < 0) {// p<0，画(x(k+1), y(k))，y不用变
            // 决策变量加上增量式
            p += 2 * circPt.x + 1;
        } else {// p>0，画(x(k+1), y(k)-1)
            (circPt.y)--;
            // 决策变量加上增量式
            p += 2 * (circPt.x - circPt.y) + 1;
        }
        //画出k+1号点
        circlePlotPoints(tmp, circPt);
    }
}

void circleDraw_test(void) {
    circleMidpoint(200, 200, 100);
    glFlush();
}

// 根据椭圆的对称性，可以一次画4个点
void ellipsePlotPoints(int xc, int yc, int x, int y) {
    setPixel(xc + x, yc + y);
    setPixel(xc - x, yc + y);
    setPixel(xc + x, yc - y);
    setPixel(xc - x, yc - y);
}

// 使用与中点圆类似的思想，但由于对称性不同，需要画四分之一个
// 右上四分之一个椭圆由于斜率不同，需要递进的方向也不同，因此分为两部分来画
void ellipseMidpoint(int xc, int yc, int rx, int ry) {
    int rx2 = rx * rx;
    int ry2 = ry * ry;
    int twoRx2 = 2 * rx2;
    int twoRy2 = 2 * ry2;
    int p;
    // 与中点圆相同，从上方的点开始画，从右上四分之一个出发，根据对称性画出其余部分
    int x = 0, y = ry;
    // 决策变量中要用到的项
    int px = 0, py = twoRx2 * y;
    ellipsePlotPoints(xc, yc, x, y);

    // 计算决策变量的初始值
    p = round(ry2 - (ry2 * ry) + (0.25 * rx2));

    // 画“区域1”即靠近y轴的半个四分之一椭圆
    while (px < py) {
        // 沿x轴递增
        x++;
        px += twoRy2;
        if (p < 0) {// p<0，画(x(k+1), y(k))，y不用变
            p += ry2 + px;
        } else {// p>0，画(x(k+1), y(k)-1)
            y--;
            py -= twoRx2;
            p += ry2 + px - py;
        }
        ellipsePlotPoints(xc, yc, x, y);
    }

    // 根据“区域1”中的最后一个点来计算“区域2”即靠近x轴部分的半个四分之一椭圆的决策参数初始值
    p = round(ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2);
    // 与上面类似
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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Ellipse drawing");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 500, 0, 500);
    std::cout << "Draw 50000 lines test" << std::endl;
    std::cout << "--------------------" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glutDisplayFunc(lineDraw_test);
    glutMainLoop();

    return 0;
}