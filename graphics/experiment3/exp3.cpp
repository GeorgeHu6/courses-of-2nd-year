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

std::vector<point> vertice; //����

typedef struct XET {
    float x;
    float dx;  // �ӵ�ǰɨ���ߵ���һ��ɨ���߼�x����������б�ʵĵ���
    float ymax; //�ñ����������ɨ���ߵ�����ֵymax
    XET *next;
} AET, NET; //AET ���Ա߱� NET�±߱�


void PolyScan() {
    /*�õ���ߵ��y����*/
    int Max_Y = 0;
    for (int i = 0; i < vertice.size(); i++)
        /*Max_Y = max(Max_Y, vertice[i].y);*/
        if (vertice[i].y > Max_Y)
            Max_Y = vertice[i].y;


    //��ʼ��AET��
    AET *pAET = new AET;
    pAET->next = NULL;

    //��ʼ��NET��
    NET *pNET[800]; //��Ͱ
    for (int i = 0; i <= Max_Y; i++) {
        pNET[i] = new NET;
        pNET[i]->next = NULL;
    }

    //ɨ�貢�ҽ���NET��
    int len = vertice.size(); //�������
    for (int i = 0; i <= Max_Y; i++) {
        for (int j = 0; j < len; j++) //ɨ��ÿ����
        {
            if (i == vertice[j].y) {
                //���һ�����ǰһ������һ������������õ�ͺ���һ����Ҳ����
                //�����ʽ�� �������һ������͵�һ�������� �� ��ֹ���ָ���

                //�жϵ�ǰ��ĸߵͣ�ʹymax��DX��DY�ļ����б仯
                if (vertice[(j - 1 + len) % len].y > vertice[j].y) {
                    //ǰһ�����ڵ�ǰ����Ϸ�
                    NET *p = new NET;
                    p->x = vertice[j].x;
                    p->ymax = vertice[(j - 1 + len) % len].y;//�뵱ǰɨ�����ཻ�Ļ��Ա� �� ��ߵ㼴Ϊ���ڶ����y
                    float DX = vertice[(j - 1 + len) % len].x - vertice[j].x;
                    float DY = vertice[(j - 1 + len) % len].y - vertice[j].y;
                    p->dx = DX / DY;//dxΪֱ��б�ʵĵ���
                    p->next = pNET[i]->next;
                    pNET[i]->next = p;
                }
                if (vertice[(j + 1) % len].y > vertice[j].y) {
                    //��һ�����ڵ�ǰ����Ϸ�
                    NET *p = new NET;
                    p->x = vertice[j].x;
                    p->ymax = vertice[(j + 1) % len].y;
                    float DX = vertice[(j + 1) % len].x - vertice[j].x;
                    float DY = vertice[(j + 1) % len].y - vertice[j].y;
                    p->dx = DX / DY;//dxΪֱ��б�ʵĵ���
                    p->next = pNET[i]->next;
                    pNET[i]->next = p;
                }
            }
        }
    }

    //�������Ҹ��»��Ա߱�AET
    //����ɨ����i
    for (int i = 0; i <= Max_Y; i++) {
        /*���±߱�NET[i] �еı߽���ò������򷨲���AET��ʹ֮��x�������˳������*/

        //����ÿ��ɨ�����ϲ�ͬ�߲������µĽ���x������AET
        NET *p = pAET->next;
        while (p) {
            p->x = p->x + p->dx; //����x����
            p = p->next;
        }

        //�ϱ�����,���ٿ��ٿռ�
        AET *tq = pAET;
        p = pAET->next;
        tq->next = NULL;
        while (p)//˳������������
        {
            //�ҵ���һ�������������tq->next->next->x�����p->next��tq->next���Ǳ�p->xС��
            while (tq->next != NULL && tq->next->x <= p->x)
                tq = tq->next;
            //����p��tq��tq->next֮��
            NET *t = p->next;
            p->next = tq->next;
            tq->next = p;
            p = t;

            tq = pAET;//�ص�ͷ
        }

        /*(�Ľ��㷨) ȡ���󽻣����ټ�����*/
        //�ȴ�AET����ɾ��ymax==i�Ľ��****************************************/
        //���ص�ȡ�����⣬��֤����εġ��±��Ͽ���������������󻯣�����ĸ���Ӧ��֤Ϊż������
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

        //��NET�����µ㣬�����ò��뷨����AET����x������˳������
        p = pNET[i]->next;
        q = pAET;
        while (p) {
            while (q->next && p->x >= q->next->x)
                q = q->next;
            //����p
            NET *t = p->next;
            p->next = q->next;
            q->next = p;
            p = t;

            q = pAET;//�ص�ͷ
        }

        //��Ժ������ɫ
        p = pAET->next;
        while (p && p->next != NULL) {
            for (float j = p->x; j <= p->next->x; j++) {
                //ɨ���߻���
                setPixel(j, i);
                //cout << "(" << j << ", " << i << ")" << endl;
            }
            p = p->next->next;//���Ƕ˵����
        }
    }
    glFlush();
}

void mymouse(int button, int state, int x, int y) {
    //���
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        setPixel(x, window_height - y);

        point p(x, window_height - y);
        vertice.push_back(p);
        std::cout << "����" << vertice.size() << ": (" << x << ", " << window_height - y << ")" << std::endl;
    }
    //�Ҽ�
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        glClearColor(1, 1, 1, 1);//���û��ƴ�����ɫΪ��ɫ
        glColor3f(0, 1, 1);

        //���ƶ����
        glBegin(GL_LINES);
        for (int i = 0; i < vertice.size(); i++) {
            if (i == vertice.size() - 1)//�������һ���㣬ʹ��պ�
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

    //����м�
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        //cout << "center: (" << x << ", " << y << ")" << endl;
        //BoundaryFill4(x, window_height - y);
        //BoundaryFill4_Stack(x, window_height - y);

        std::cout << "����ζ������Ϊ" << vertice.size() << "�� " << "��ʼɨ������䡣" << std::endl;
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

// ������ɫ���õĻص�����
void colorTest(void) {
    int x = 0;
    glBegin(GL_LINES);
    // ������ɫ�����Ч�����������ң���ɫ�ɷ�Խ��Խ��
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

// �ķ���ı߽�����㷨
void boundaryFill4(int x, int y, Color fillColor, Color borderColor) {
    Color interiorColor;
    // ��ȡ��ǰ�����ɫֵ���ж��Ƿ����
    getPixel(x, y, interiorColor);
    // û���߽���û�������ͷֱ����ҡ����ϡ������
    if (!cmpColor(interiorColor, borderColor) && !cmpColor(interiorColor, fillColor)) {
        setPixel(x, y);
        // ÿ��һ���㶼����Flush����չʾ�����Ĺ���
//        glFlush();
        // �ֱ�ݹ�߽�����ҡ����ϡ����ĸ���
        boundaryFill4(x + 1, y, fillColor, borderColor);
        boundaryFill4(x - 1, y, fillColor, borderColor);
        boundaryFill4(x, y + 1, fillColor, borderColor);
        boundaryFill4(x, y - 1, fillColor, borderColor);
    }
}

void floodFill4(int x, int y, Color fillColor, Color interiorColor) {
    Color current;
    // ��ȡ��ǰ����ɫֵ
    getPixel(x, y, current);
    // ��ǰ��ɫֵ��interiorColor��ȣ�˵����ǰ������Ҫ���滻ΪfillColorɫ
    if (cmpColor(interiorColor, current)) {
        setPixel(x, y);
        // ÿ��һ���㶼����Flush����չʾ�����Ĺ���
        glFlush();
        // �ֱ�ݹ鷺������ҡ����ϡ����ĸ���
        floodFill4(x + 1, y, fillColor, interiorColor);
        floodFill4(x - 1, y, fillColor, interiorColor);
        floodFill4(x, y - 1, fillColor, interiorColor);
        floodFill4(x, y + 1, fillColor, interiorColor);
    }
}

// ���Բ���4��ͨ�߽�����㷨�Ļص�����
void testBoundaryFill(void) {
    // ����������ɫ��ʮ������Ϊ#66CCFF
    Color fill = {0.4f, 0.8f, 1.0f};
    // ��Ϊ�߽���ɫ��Ϊ��ɫ
    Color border = {0.0f, 0.0f, 0.0f};
    // �Ȼ��ô���������ı߽磨һ������ǣ�
    int points[] = {85, 160, 109, 117, 156, 108, 123, 73, 129, 24, 85, 45, 41, 24, 47, 73, 14, 108, 61, 117};
    glColor3fv(border);
    // �������10������ɣ�ʹ��GL_LINE_LOOP����λ��ӵ���
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 10; i++) {
        glVertex2i(points[2 * i], points[2 * i + 1]);
    }
    glEnd();
    glFlush();
    printf("boundary draw completed.\n");
    // ���û�ͼ��ɫΪfill
    glColor3fv(fill);
    // ѡ�����ʼ��λ�����ε����ĵ�
    boundaryFill4(85, 85, fill, border);
    glFlush();
    printf("boundary fill done.\n");
}

// ���Բ��Է�������㷨�Ļص�����
void testFloodFill(void) {
    Sleep(5000);
    // ����������ɫ��ʮ������Ϊ#66CCFF
    Color fill = {0.4f, 0.8f, 1.0f};
    // �����ԭ������ɫ��Ϊ��ɫ
    Color origin = {0.0f, 0.0f, 0.0f};
    // ����һ������������������
    int points[] = {50, 100, 100, 130, 150, 100, 150, 50, 50, 50};
    glColor3fv(origin);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 5; i++) {
        glVertex2i(points[2 * i], points[2 * i + 1]);
    }
    glEnd();
    glFlush();
    printf("Polygon draw completed.\n");
    // �л��������ɫ
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