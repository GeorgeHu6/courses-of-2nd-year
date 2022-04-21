#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <windows.h>
#include <vector>


const int window_width = 800, window_height = 600;
const int maxn = 99999;

void setPixel(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

struct point {
    float x, y;

    point() {}

    point(int xx, int yy) :
            x(xx), y(yy) {}
};

std::vector<point> vertice; //顶点

typedef struct XET {
    float x;
    float dx;  // 从当前扫描线到下一条扫描线间x的增量，即斜率的倒数
    float ymax; //该边所交的最高扫描线的坐标值ymax
    XET *next;
} AET, NET; //AET 活性边表； NET新边表


void PolyScan() {
    /*得到最高点的y坐标*/
    int Max_Y = 0;
    for (int i = 0; i < vertice.size(); i++)
        /*Max_Y = max(Max_Y, vertice[i].y);*/
        if (vertice[i].y > Max_Y)
            Max_Y = vertice[i].y;


    //初始化AET表
    AET *pAET = new AET;
    pAET->next = NULL;

    //初始化NET表
    NET *pNET[800]; //吊桶
    for (int i = 0; i <= Max_Y; i++) {
        pNET[i] = new NET;
        pNET[i]->next = NULL;
    }

    //扫描并且建立NET表
    int len = vertice.size(); //顶点个数
    for (int i = 0; i <= Max_Y; i++) {
        for (int j = 0; j < len; j++) //扫描每个点
        {
            if (i == vertice[j].y) {
                //如果一个点和前一个点有一条边相连，则该点和后面一个点也相连
                //！这个式子 便于最后一个顶点和第一个点相连 和 防止出现负数

                //判断当前点的高低，使ymax、DX、DY的计算有变化
                if (vertice[(j - 1 + len) % len].y > vertice[j].y) {
                    //前一个点在当前点的上方
                    NET *p = new NET;
                    p->x = vertice[j].x;
                    p->ymax = vertice[(j - 1 + len) % len].y;//与当前扫描线相交的活性边 的 最高点即为相邻顶点的y
                    float DX = vertice[(j - 1 + len) % len].x - vertice[j].x;
                    float DY = vertice[(j - 1 + len) % len].y - vertice[j].y;
                    p->dx = DX / DY;//dx为直线斜率的倒数
                    p->next = pNET[i]->next;
                    pNET[i]->next = p;
                }
                if (vertice[(j + 1) % len].y > vertice[j].y) {
                    //后一个点在当前点的上方
                    NET *p = new NET;
                    p->x = vertice[j].x;
                    p->ymax = vertice[(j + 1) % len].y;
                    float DX = vertice[(j + 1) % len].x - vertice[j].x;
                    float DY = vertice[(j + 1) % len].y - vertice[j].y;
                    p->dx = DX / DY;//dx为直线斜率的倒数
                    p->next = pNET[i]->next;
                    pNET[i]->next = p;
                }
            }
        }
    }

    //建立并且更新活性边表AET
    //各条扫描线i
    for (int i = 0; i <= Max_Y; i++) {
        /*把新边表NET[i] 中的边结点用插入排序法插入AET表，使之按x坐标递增顺序排列*/

        //计算每条扫描线上不同线产生的新的交点x，更新AET
        NET *p = pAET->next;
        while (p) {
            p->x = p->x + p->dx; //更新x坐标
            p = p->next;
        }

        //断表排序,不再开辟空间
        AET *tq = pAET;
        p = pAET->next;
        tq->next = NULL;
        while (p)//顺着链表往下走
        {
            //找到第一个比它大的数字tq->next->next->x，则从p->next到tq->next都是比p->x小的
            while (tq->next != NULL && tq->next->x <= p->x)
                tq = tq->next;
            //插入p到tq和tq->next之间
            NET *t = p->next;
            p->next = tq->next;
            tq->next = p;
            p = t;

            tq = pAET;//回到头
        }

        /*(改进算法) 取消求交，减少计算量*/
        //先从AET表中删除ymax==i的结点****************************************/
        //像素的取舍问题，保证多边形的“下闭上开”，避免填充扩大化（交点的个数应保证为偶数个）
        AET *q = pAET;
        p = q->next;
        while (p) {
            if (p->ymax == i) {
                q->next = p->next;
                delete p;
                p = q->next;
            } else {
                q = q->next;
                p = q->next;
            }
        }

        //若NET中有新点，将其用插入法插入AET，按x递增的顺序排列
        p = pNET[i]->next;
        q = pAET;
        while (p) {
            while (q->next && p->x >= q->next->x)
                q = q->next;
            //插入p
            NET *t = p->next;
            p->next = q->next;
            q->next = p;
            p = t;

            q = pAET;//回到头
        }

        //配对后填充颜色
        p = pAET->next;
        while (p && p->next != NULL) {
            for (float j = p->x; j <= p->next->x; j++) {
                //扫描线画点
                setPixel(j, i);
                //cout << "(" << j << ", " << i << ")" << endl;
            }
            p = p->next->next;//考虑端点情况
        }
    }
    glFlush();
}

void mymouse(int button, int state, int x, int y) {
    //左键
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        setPixel(x, window_height - y);

        point p(x, window_height - y);
        vertice.push_back(p);
        std::cout << "顶点" << vertice.size() << ": (" << x << ", " << window_height - y << ")" << std::endl;
    }
    //右键
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        glClearColor(1, 1, 1, 1);//设置绘制窗口颜色为白色
        glColor3f(0, 1, 1);

        //绘制多边形
        glBegin(GL_LINES);
        for (int i = 0; i < vertice.size(); i++) {
            if (i == vertice.size() - 1)//画完最后一个点，使其闭合
            {
                glVertex2f(vertice[0].x, vertice[0].y);
                glVertex2f(vertice[i].x, vertice[i].y);
            } else {
                glVertex2f(vertice[i].x, vertice[i].y);
                glVertex2f(vertice[i + 1].x, vertice[i + 1].y);
            }
        }
        glEnd();
        glFlush();
    }

    //鼠标中间
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        //cout << "center: (" << x << ", " << y << ")" << endl;
        //BoundaryFill4(x, window_height - y);
        //BoundaryFill4_Stack(x, window_height - y);

        std::cout << "多边形顶点个数为" << vertice.size() << "。 " << "开始扫描线填充。" << std::endl;
        PolyScan();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.4, 0.2);
    glPointSize(1);
    glBegin(GL_POINTS);
    PolyScan();
    glEnd();
    glFlush();
}

typedef float Color[3];

bool cmpColor(Color a, Color b) {
    return abs(a[0] - b[0]) < 0.001 && abs(a[1] - b[1]) < 0.001 && abs(a[2] - b[2]) < 0.001;
}

void getPixel(GLint x, GLint y, Color c) {
    Color tmp = {0, 0, 0};
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, tmp);
    c[0] = tmp[0], c[1] = tmp[1], c[2] = tmp[2];
}

// 测试颜色设置的回调函数
void colorTest(void) {
    int x = 0;
    glBegin(GL_LINES);
    // 测试蓝色渐变的效果，从左往右，蓝色成分越来越多
    for (int i = 0; i < 250; i++) {
        glColor3f(0.0f, 0.0f, (float) i / 255);
        glVertex2i(x, 0);
        glVertex2i(x++, 500);
        glVertex2i(x, 0);
        glVertex2i(x++, 500);
    }
    glEnd();
    glFlush();
}

// 四方向的边界填充算法
void boundaryFill4(int x, int y, Color fillColor, Color borderColor) {
    Color interiorColor;
    // 获取当前点的颜色值以判断是否填充
    getPixel(x, y, interiorColor);
    // 没到边界且没填充过，就分别往右、左、上、下填充
    if (!cmpColor(interiorColor, borderColor) && !cmpColor(interiorColor, fillColor)) {
        setPixel(x, y);
        // 每填一个点都进行Flush，以展示出填充的过程
//        glFlush();
        // 分别递归边界填充右、左、上、下四个点
        boundaryFill4(x + 1, y, fillColor, borderColor);
        boundaryFill4(x - 1, y, fillColor, borderColor);
        boundaryFill4(x, y + 1, fillColor, borderColor);
        boundaryFill4(x, y - 1, fillColor, borderColor);
    }
}

void floodFill4(int x, int y, Color fillColor, Color interiorColor) {
    Color current;
    // 获取当前点颜色值
    getPixel(x, y, current);
    // 当前颜色值与interiorColor相等，说明当前像素需要被替换为fillColor色
    if (cmpColor(interiorColor, current)) {
        setPixel(x, y);
        // 每填一个点都进行Flush，以展示出填充的过程
        glFlush();
        // 分别递归泛滥填充右、左、上、下四个点
        floodFill4(x + 1, y, fillColor, interiorColor);
        floodFill4(x - 1, y, fillColor, interiorColor);
        floodFill4(x, y - 1, fillColor, interiorColor);
        floodFill4(x, y + 1, fillColor, interiorColor);
    }
}

// 用以测试4连通边界填充算法的回调函数
void testBoundaryFill(void) {
    // 用来填充的颜色，十六进制为#66CCFF
    Color fill = {0.4f, 0.8f, 1.0f};
    // 作为边界颜色，为黑色
    Color border = {0.0f, 0.0f, 0.0f};
    // 先画好待填充的区域的边界（一个五角星）
    int points[] = {85, 160, 109, 117, 156, 108, 123, 73, 129, 24, 85, 45, 41, 24, 47, 73, 14, 108, 61, 117};
    glColor3fv(border);
    // 五角星由10个点组成，使用GL_LINE_LOOP画首位相接的线
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 10; i++) {
        glVertex2i(points[2 * i], points[2 * i + 1]);
    }
    glEnd();
    glFlush();
    printf("boundary draw completed.\n");
    // 设置绘图颜色为fill
    glColor3fv(fill);
    // 选择的起始点位三角形的中心点
    boundaryFill4(85, 85, fill, border);
    glFlush();
    printf("boundary fill done.\n");
}

// 用以测试泛滥填充算法的回调函数
void testFloodFill(void) {
    Sleep(5000);
    // 用来填充的颜色，十六进制为#66CCFF
    Color fill = {0.4f, 0.8f, 1.0f};
    // 多边形原来的颜色，为黑色
    Color origin = {0.0f, 0.0f, 0.0f};
    // 绘制一个多边形用来泛滥填充
    int points[] = {50, 100, 100, 130, 150, 100, 150, 50, 50, 50};
    glColor3fv(origin);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 5; i++) {
        glVertex2i(points[2 * i], points[2 * i + 1]);
    }
    glEnd();
    glFlush();
    printf("Polygon draw completed.\n");
    // 切换至填充颜色
    glColor3fv(fill);
    floodFill4(100, 100, fill, origin);
    glFlush();
    printf("floodFill done.\n");
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(200, 200);
    glutCreateWindow("test");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(0, 200.0, 0, 200.0);
    glMatrixMode(GL_PROJECTION);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
//    glutMouseFunc(mymouse);
    glutDisplayFunc(testBoundaryFill);
    glutMainLoop();

    return 0;
}