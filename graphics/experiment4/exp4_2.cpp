#include <GL/glut.h>
#include <iostream>
#include <vector>

int WINDOW_HEIGHT = 600;
int WINDOW_WIDTH = 600;

struct dcPt {
    int x;
    int y;
};

// 记录线的集合
std::vector<std::pair<dcPt, dcPt>> lines = {};

// 记录第一个点
dcPt pre;
// 是否已标记第一个点
bool pre_flag = false;
// 需要重绘
bool need_redraw = false;

// 将清屏操作独立出来
void clear_screen() {
    lines.clear();
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glEnd();
    glFlush();
}

// 鼠标事件回调函数
void mouse(int button, int state, int x, int y) {
    if (!pre_flag) {// 鼠标左键点击第一个点
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            pre_flag = true;
            pre.x = x;
            pre.y = y;
        }
    } else {// 鼠标左键点击第二个点
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            std::cout << "draw: " << pre.x << " " << pre.y << " to " << x << " " << y << std::endl;
            lines.emplace_back(pre, dcPt{x, y});
            pre_flag = false;
            need_redraw = true;
        }
    }
    // 鼠标右键清屏
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        std::cout << "clear" << std::endl;
        clear_screen();
    }
}

// 设置画笔颜色为66CCFF、线宽为2
void draw() {
    glColor3f(0.4f, 0.8f, 1.0f);
    glLineWidth(2.0f);
}

// 根据lines中的更新重绘
void refresh() {
    // 不需要重绘
    if (!need_redraw) {
        return;
    }
    // 需要重绘，先清屏，再绘制lines中的线
    glClear(GL_COLOR_BUFFER_BIT);
    for (std::pair<dcPt, dcPt> & line : lines) {
        glBegin(GL_LINES);
        glVertex2i(line.first.x, WINDOW_HEIGHT-line.first.y);
        glVertex2i(line.second.x, WINDOW_HEIGHT-line.second.y);
        glEnd();
    }
    glFlush();
    need_redraw = false;
}

// 窗口大小改变时的回调函数
void reshape(int width, int height) {
    // 根据当前窗口大小改变全局变量
    WINDOW_HEIGHT = height;
    WINDOW_WIDTH = width;
    // 重新设置裁剪窗口和视口
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();// 重新投影
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    // 窗口大小改变后需要进行重绘
    need_redraw = true;
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("interactive window");
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
    clear_screen();
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutIdleFunc(refresh);
    glutMainLoop();
    return 0;
}
