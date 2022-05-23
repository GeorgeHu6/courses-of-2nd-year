#include <GL/glut.h>

typedef unsigned char encode;

struct wcPt2D {
    int x;
    int y;
};

bool flag = false;

// 0000上下右左
encode getEncode(wcPt2D pt, wcPt2D min, wcPt2D max) {
    encode code = 0x00;
    if (pt.y > max.y) {
        code |= 1 << 3;
    }
    if (pt.y < min.y) {
        code |= 1 << 2;
    }
    if (pt.x > max.x) {
        code |= 1 << 1;
    }
    if (pt.x < min.x) {
        code |= 1 << 0;
    }
    return code;
}

void lineClipCohSutherland(wcPt2D minCoord, wcPt2D maxCoord, wcPt2D p1, wcPt2D p2) {
    int xmin = minCoord.x, ymin = minCoord.y;
    int xmax = maxCoord.x, ymax = maxCoord.y;
    int x1 = p1.x, y1 = p1.y;
    int x2 = p2.x, y2 = p2.y;
    double m = (double) (y2 - y1) / (x2 - x1);

    encode code1 = getEncode(p1, minCoord, maxCoord);
    encode code2 = getEncode(p2, minCoord, maxCoord);

    // 如果两点都在视窗内，则直接画线
    if (code1 == 0 && code2 == 0) {
        glBegin(GL_LINES);
        glVertex2i(p1.x, p1.y);
        glVertex2i(p2.x, p2.y);
        glEnd();
    } else if (code1 & code2) {
        // 如果两点都在视窗外，则不画线
        return;
    } else {
        // 如果一点在视窗内，一点在视窗外，则画线
        if (code1) {
            // 如果第一个点在视窗外，则画第一个点
            glVertex2i(x1, y1);
            // 计算第一个点的新坐标
            if (code1 & 1) {
                y1 += m * (xmin - x1);
                x1 = xmin;
            }
            if (code1 & 2) {
                y1 += m * (xmax - x1);
                x1 = xmax;
            }
            if (code1 & 4) {
                x1 += (ymin - y1) / m;
                y1 = ymin;
            }
            if (code1 & 8) {
                x1 += (ymax - y1) / m;
                y1 = ymax;
            }
        }
        if (code2) {
            // 如果第二个点在视窗外，则画第二个点
            glVertex2i(x2, y2);
            // 计算第二个点的新坐标
            if (code2 & 1) {
                y2 += m * (xmin - x2);
                x2 = xmin;
            }
            if (code2 & 2) {
                y2 += m * (xmax - x2);
                x2 = xmax;
            }
            if (code2 & 4) {
                x2 += (ymin - y2) / m;
                y2 = ymin;
            }
            if (code2 & 8) {
                x2 += (ymax - y2) / m;
                y2 = ymax;
            }
        }
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
    }
}

// 计算处理边界的p、q、r
int clipTest(float p, float q, float *u1, float *u2) {
    bool res = true;// 用于记录线段是否要保留
    float r;

    if (p < 0) {// 由外到内的情况
        r = q / p;
        if (r > *u2) {// r>u2，意味着已经超出线段右端点，是无效的
            res = false;
        } else if (r > *u1) {// 更新u1为较大值
            *u1 = r;
        }
    } else if (p > 0) {// 由内到外的情况
        r = q / p;
        if (r < *u1) {// r<u1，意味着已经超出线段左端点，是无效的
            res = false;
        } else if (r < *u2) {// 更新u2为较小值
            *u2 = r;
        }
    } else {// p=0，线段平行于边界
        if (q < 0) {// 线段完全在边界外，直接舍弃
            res = false;
        }
        // p大于等于0时，线段完全在裁剪窗口内，直接保留
    }
    return res;
}

void lineClipBarskey(wcPt2D minCoord, wcPt2D maxCoord, wcPt2D p1, wcPt2D p2) {
    float u1 = 0.0, u2 = 1.0, dx = p2.x - p1.x, dy = p2.y - p1.y;
    int xmin = minCoord.x, ymin = minCoord.y;
    int xmax = maxCoord.x, ymax = maxCoord.y;

    if (clipTest(-dx, p1.x - xmin, &u1, &u2)) {// 左边界
        if (clipTest(dx, xmax - p1.x, &u1, &u2)) {// 右边界
            if (clipTest(-dy, p1.y - ymin, &u1, &u2)) {// 下边界
                if (clipTest(dy, ymax - p1.y, &u1, &u2)) {// 上边界
                    // 得到了裁剪后的参数u1、u2，将线段端点缩到裁剪后位置
                    if (u2 < 1) {// 右端点要调整
                        p2.x = p1.x + u2 * dx;
                        p2.y = p1.y + u2 * dy;
                    }
                    if (u1 > 0) {// 左端点要调整
                        p1.x += u1 * dx;
                        p1.y += u1 * dy;
                    }
                    glBegin(GL_LINES);
                    glVertex2i(p1.x, p1.y);
                    glVertex2i(p2.x, p2.y);
                    glEnd();
                }
            }
        }
    }


}

void myDisplay() {
    wcPt2D winMin, winMax, p1, p2;
    winMin.x = 100;
    winMin.y = 200;//定义裁剪窗口
    winMax.x = 400;
    winMax.y = 400;
    p1.x = 200;
    p1.y = 200; //定义被裁剪的直线端点
    p2.x = 300;
    p2.y = 300;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);

    glRectf(winMin.x, winMin.y, winMax.x, winMax.y); //绘制红色裁剪矩形

    glColor3f(1.0f, 1.0f, 1.0f);
    if (flag) {
        // lineClipCohSutherland(winMin, winMax, p1, p2);// 绘制裁剪线段，由你们实现
        // lineClipBarskey(winMin, winMax, p1, p2);

    } else {
        glBegin(GL_LINES);
        glVertex2i(p1.x, p1.y);
        glVertex2i(p2.x, p2.y);
        glEnd();
    }
    glFlush();
}

void myInit() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void Reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'c' || key == 'C') flag = true;
    if (key == 'r' || key == 'R') flag = false;
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Cohen-Sutherland");
    myInit();
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
