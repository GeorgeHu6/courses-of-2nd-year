#include <GL/freeglut.h>
#include <cmath>
#include <vector>

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500

void setPixel(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

typedef struct tEdge {
    int yUpper;
    float xIntersect, dxPerScan;
    struct tEdge *next;
} Edge;

typedef struct dcPt {
    int x, y;
} dcPt;

// 在边表list中插入边edge，ET与AET通用
void insertEdge(Edge *list, Edge *edge) {
    Edge *p, *q = list;
    p = q->next;
    while (p != NULL) {
        // ET、AET中某一项链表记录的点的x要从左往右，将边edge插入到链表中的合适位置
        // 寻找一个比p的x小，比q的x大的位置
        if (edge->xIntersect < p->xIntersect) {
            p = NULL;
        } else {
            q = p;
            p = p->next;
        }
    }
    // 在q、p之间插入edge
    edge->next = q->next;
    q->next = edge;
}

int yNext(int k, int cnt, dcPt *pts) {
    int j;
    // 由于此处 k+1∈[1,cnt]，这段if-else相当于j=(k+1)%cnt
    if ((k + 1) > (cnt - 1)) {
        j = 0;
    } else {
        j = k + 1;
    }

    // 在点的数组中循环找下一个和k点不在一条水平上的点
    while (pts[k].y == pts[j].y) {
        if ((j + 1) > (cnt - 1)) {
            j = 0;
        } else {
            j++;
        }
    }
    return pts[j].y;
}

// 处理边edge（包括顶点算一次还是算两次），并将其加入边表edges
void makeEdgeRec(dcPt lower, dcPt upper, int yComp, Edge *edge, Edge *edges[]) {
    // 计算这条边的斜率
    edge->dxPerScan = (float) (upper.x - lower.x) / (upper.y - lower.y);
    // 与扫描线的第一次相交交点的x，一定是下方点的x
    edge->xIntersect = lower.x;
    // 在边的奇偶处理中，对于顶点需要进行特殊处理
    if (upper.y < yComp) {// 单调的，只算一次，将较低一段的较高点，即终点（此处即为点upper）
        edge->yUpper = upper.y - 1;
    } else {// 不单调的不动，即算两次
        edge->yUpper = upper.y;
    }
    // 将处理好的边edge，即(lower->upper)，放入ET表中
    insertEdge(edges[lower.y], edge);
}

// 构建ET表
void buildEdgeList(int cnt, dcPt *pts, Edge *edges[]) {
    Edge *edge;
    dcPt v1, v2;
    // yPrev记录前一个点的前一个点的y坐标，初始值显然为倒数第二个点
    int i, yPrev = pts[cnt - 2].y;

    // v1记录当前遍历的点的前一个点，初始值显然为倒数第一个点
    v1.x = pts[cnt - 1].x, v1.y = pts[cnt - 1].y;
    // 遍历各个点，同样是遍历边v1-v2
    for (int i = 0; i < cnt; i++) {
        // v2用以记录当前遍历点
        v2 = pts[i];
        // 要添加到ET中的边不能是水平的
        if (v1.y != v2.y) {
            edge = (Edge *) malloc(sizeof(Edge));
            // 要把y较小的点作为起点
            if (v1.y < v2.y) {// 当前点的前一个点v1的y较小
                makeEdgeRec(v1, v2, yNext(i, cnt, pts), edge, edges);
            } else {// 当前点v2的y较小
                makeEdgeRec(v2, v1, yPrev, edge, edges);
            }
        }
        // 传递变量
        yPrev = v1.y;
        v1 = v2;
    }
}

// 将扫描线y=scan涉及的新边加入到AET中
void buildActiveList(int scan, Edge *active, Edge *edges[]) {
    Edge *p, *q;
    p = edges[scan]->next;
    while (p) {
        q = p->next;
        // 在ET中取得的新边，插入AET
        insertEdge(active, p);
        p = q;
    }
}

// 扫描线y=scan按AET进行填充
void fillScan(int scan, Edge *active) {
    Edge *p1, *p2;

    p1 = active->next;
    // 在第奇数个与第偶数个点之间填充即可
    // 即AET中1、2之间，3、4之间...进行填充
    while (p1) {
        p2 = p1->next;
        for (int i = p1->xIntersect; i < p2->xIntersect; i++) {
            setPixel((int) i, scan);
        }
        p1 = p2->next;
    }
}

// 在链表中删除q->next
void deleteAfter(Edge *q) {
    Edge *p = q->next;
    q->next = p->next;
    free(p);
}

// 在完成一条扫描线后，更新AET的操作
void updateActiveList(int scan, Edge *active) {
    Edge *q = active, *p = active->next;

    while (p) {
        if (scan >= p->yUpper) {// 下一条扫描线已经不会与该边相交，从AET中删除
            p = p->next;
            deleteAfter(q);
        } else {// 根据边的dx信息更新下一条扫描线和该边的交点x坐标
            p->xIntersect = p->xIntersect + p->dxPerScan;
            q = p;
            p = p->next;
        }
    }
}

// 在
void resortActiveList(Edge *active) {
    Edge *q, *p = active->next;

    active->next = NULL;
    while (p) {
        q = p->next;
        insertEdge(active, p);
        p = q;
    }
}

// 扫描线填充的主函数，cnt为多边形的顶点个数，pts为顶点数组
void scanFill(int cnt, dcPt *pts) {
    Edge *edges[WINDOW_HEIGHT], *active;
    int i, scan;

    // 初始化一个空的ET
    for (int i = 0; i < WINDOW_HEIGHT; i++) {
        edges[i] = (Edge *) malloc(sizeof(Edge));
        edges[i]->next = NULL;
    }
    // 构建ET
    buildEdgeList(cnt, pts, edges);

    // 初始化AET，各条扫描线之间互不干扰，只需要一条链表记录当前扫描线的AET即可
    active = (Edge *) malloc(sizeof(Edge));
    active->next = NULL;
    // 从下到上遍历扫描线进行填充
    for (scan = 0; scan < WINDOW_HEIGHT; scan++) {
        buildActiveList(scan, active, edges);
        if (active->next) {
            fillScan(scan, active);
            updateActiveList(scan, active);
            resortActiveList(active);
        }
    }
}

void testScanLineFill() {
    // 三种多边形用于测试，分别是复杂多边形、凹多边形、凸多边形
    dcPt complex[] = {
            WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4,
            3 * WINDOW_WIDTH / 4, 3 * WINDOW_HEIGHT / 4,
            3 * WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4,
            WINDOW_WIDTH / 4, 3 * WINDOW_HEIGHT / 4
    };
    dcPt concave[] = {
            WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4,
            3 * WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4,
            3 * WINDOW_WIDTH / 4, 3 * WINDOW_HEIGHT / 4,
            WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,
            WINDOW_WIDTH / 4, 3 * WINDOW_HEIGHT / 4,
    };
    dcPt convex[] = {
            WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4,
            3 * WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4,
            3 * WINDOW_WIDTH / 4, 3 * WINDOW_HEIGHT / 4,
            WINDOW_WIDTH / 2, 4 * WINDOW_HEIGHT / 5,
            WINDOW_WIDTH / 4, 3 * WINDOW_HEIGHT / 4,
    };

    glColor3f(0.4f, 0.8f, 1.0f);
//    scanFill(4, complex);
    scanFill(5, concave);
//    scanFill(5, convex);
    glFlush();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 5; i++) {
        glVertex2i(concave[i].x, concave[i].y);
        glVertex2i(concave[(i + 1) % 5].x, concave[(i + 1) % 5].y);
    }
    glEnd();
    glFlush();
}


int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("scan-line Fill algorithm");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    glutDisplayFunc(testScanLineFill);
    glutMainLoop();
}