#include <GL/glut.h>
#include <iostream>

int WINDOW_HEIGHT = 600;
int WINDOW_WIDTH = 600;
// 移动时每一步的距离
const int move_step = 5;

struct rectangle {
    int x, y;// 左下角坐标
    int width, height;
};

// 初始化矩形
rectangle rect1 = {10, 10, 200, 300};
// 标记是否需要重绘
bool need_redraw = false;

// 普通键位的回调函数
void normal_keyboard(unsigned char key, int x, int y) {
    if (key == 'c' || key == 'C') {// c键退出
        exit(0);
    }
}

// 特殊键位的回调函数
void spec_keyboard(int key, int x, int y) {
    // std::cout << rect1.x << " " << rect1.y << std::endl;
    if (key == GLUT_KEY_UP && rect1.y + rect1.height + move_step <= WINDOW_HEIGHT) {// 向上移动，但上边界不能超过屏幕高度
        rect1.y += move_step;
    } else if (key == GLUT_KEY_DOWN && rect1.y - move_step >= 0) {// 向下移动，但下边界不能小于0
        rect1.y -= move_step;
    } else if (key == GLUT_KEY_LEFT && rect1.x - move_step >= 0) {// 向左移动，但左边界不能小于0
        rect1.x -= move_step;
    } else if (key == GLUT_KEY_RIGHT && rect1.x + rect1.width + move_step <= WINDOW_WIDTH) {// 向右移动，但右边界不能超过屏幕宽度
        rect1.x += move_step;
    }
    need_redraw = true;
}

// 绘制矩形rect
void drawRect(rectangle rect) {
    glRecti(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height);
}

// 设置画笔颜色，并绘制一开始的矩形
void draw() {
    glColor3f(0.4f, 0.8f, 1.0f);
    drawRect(rect1);
    glFlush();
}

void refresh() {
    // 不需要重绘
    if (!need_redraw) {
        return;
    }
    // 需要重绘，先清屏，再绘制矩形
    glClear(GL_COLOR_BUFFER_BIT);
    drawRect(rect1);
    glFlush();
    need_redraw = false;
}

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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(draw);
    glutIdleFunc(refresh);
    glutSpecialFunc(spec_keyboard);
    glutKeyboardFunc(normal_keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

