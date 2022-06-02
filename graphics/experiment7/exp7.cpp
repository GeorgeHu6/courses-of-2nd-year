#include <GL/glut.h>
#include <cmath>
#include <iostream>

#define ROTATE_STEP 0.1

typedef struct {
    float pos_x, pos_y, pos_z;
    float forward_x, forward_y, forward_z;
    float up_x, up_y, up_z;
    bool z_flag;// 记录绕y轴旋转时z的符号，true为正、false为负
    float distance;

    void updateDistance() {
        distance = sqrt(pos_x * pos_x + pos_y * pos_y + pos_z * pos_z);
    };

    float getRadius() const {
        return sqrt(distance * distance - pos_y * pos_y);
    };
} Camera;

float angle_x = 0.0; // 记录x轴旋转角度
float angle_y = 0.0;// 记录y轴旋转角度
float angle_z = 0.0;// 记录z轴旋转角度
int window_width = 500;
int window_height = 500;
// 鼠标按下时的坐标
float mouse_x;
float mouse_y;

Camera camera;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    camera.pos_x = 0.0, camera.pos_y = 0.0, camera.pos_z = 5.0;
    camera.forward_x = 0.0, camera.forward_y = 0.0, camera.forward_z = 0.0;
    camera.up_x = 0.0, camera.up_y = 1.0, camera.up_z = 0.0;
    camera.z_flag = true;
    camera.updateDistance();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glLoadIdentity();  // 加载单位矩阵
    gluLookAt(camera.pos_x, camera.pos_y, camera.pos_z,
              camera.forward_x, camera.forward_y, camera.forward_z,
              camera.up_x, camera.up_y, camera.up_z);
    // 分别在x、y、z轴旋转
    glRotatef(angle_x, 1.0, 0.0, 0.0);
    glRotatef(angle_y, 0.0, 1.0, 0.0);
    glRotatef(angle_z, 0.0, 0.0, 1.0);
    glutWireTeapot(1.8);
    glFlush();
}

void reshape(int w, int h) {
    // 视口与窗口大小保持一致
    glViewport(0, 0, w, h);
    window_height = h;
    window_width = w;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 操作模型视景
    gluPerspective(60.0, (float) w / (float) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera.pos_x, camera.pos_y, camera.pos_z,
              camera.forward_x, camera.forward_y, camera.forward_z,
              camera.up_x, camera.up_y, camera.up_z);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        // 当左键按下时记录鼠标坐标
        if (state == GLUT_DOWN) {
            mouse_x = x;
            mouse_y = y;
        }
    }
}

void motion(int x, int y) {
    float dx = mouse_x - x;
    float dy = mouse_y - y;
    // 将鼠标在窗口中移动的距离转换为旋转角度，
    // 其中y与z上同步旋转
    angle_x += 360 * dx / (float) window_width;
    angle_y += 360 * dy / (float) window_height;
    angle_z += 360 * dy / (float) window_height;
    // 更新最新的鼠标位置，
    // 使得下次拖动旋转是根据当前位置计算的
    mouse_x = x;
    mouse_y = y;
    // 申请重绘
    glutPostRedisplay();
}

void spec_keyboard(int key, int x, int y) {
    // int flag;
    if (key == GLUT_KEY_RIGHT) {// 绕y轴向右（顺向）旋转相机
        // 保留x的符号
        // flag = camera.pos_x >= 0 ? 1 : -1;
        if (camera.pos_z >= 0 && !(camera.pos_z == 0 && camera.pos_x > 0)) {// x需要增加
            camera.pos_x += ROTATE_STEP;
        } else {// x需要减少
            camera.pos_x -= ROTATE_STEP;
        }
        if (camera.pos_x <= -camera.getRadius()) {// 从下半空间转到上半空间，z从负转为正
            camera.pos_x = -camera.getRadius();
            camera.pos_z = 0;
            camera.z_flag = true;
        } else if (camera.pos_x >= camera.getRadius()) {// 从上半空间转到下半空间，z从正转为负
            camera.pos_x = camera.getRadius();
            camera.pos_z = 0;
            camera.z_flag = false;
        }// z未反转正负，z_flag维持不变即可

        // 计算相机z坐标的绝对值
        camera.pos_z = sqrt(camera.distance * camera.distance - camera.pos_x * camera.pos_x);
        // 给相机z坐标加上符号
        if (!camera.z_flag) camera.pos_z = -camera.pos_z;
        std::cout << camera.pos_x << " " << camera.pos_z << std::endl;
    } else if (key == GLUT_KEY_LEFT) {// 绕y轴向左（逆向）旋转相机
        if (camera.pos_z >= 0 && !(camera.pos_z == 0 && camera.pos_x < 0)) {// x需要减少
            camera.pos_x -= ROTATE_STEP;
        } else {// x需要增加
            camera.pos_x += ROTATE_STEP;
        }
        if (camera.pos_x >= camera.getRadius()) {// 从下半空间转到上半空间，z从负转为正
            camera.pos_x = camera.getRadius();
            camera.pos_z = 0;
            camera.z_flag = true;
        } else if (camera.pos_x <= -camera.getRadius()) {// 从上半空间转到下半空间，z从正转为负
            camera.pos_x = -camera.getRadius();
            camera.pos_z = 0;
            camera.z_flag = false;
        }// z未反转正负，z_flag维持不变即可

        // 计算相机z坐标的绝对值
        camera.pos_z = sqrt(camera.distance * camera.distance - camera.pos_x * camera.pos_x);
        // 给相机z坐标加上符号
        if (!camera.z_flag) camera.pos_z = -camera.pos_z;
        std::cout << camera.pos_x << " " << camera.pos_z << std::endl;
    } else if (key == GLUT_KEY_UP) {// 相机向当前面对方向前进
        float len = sqrt(camera.pos_x * camera.pos_x + camera.pos_y * camera.pos_y + camera.pos_z * camera.pos_z);
        len = 1 / len;
        camera.pos_x -= camera.pos_x * len;
        camera.pos_y -= camera.pos_y * len;
        camera.pos_z -= camera.pos_z * len;
        camera.updateDistance();
    } else if (key == GLUT_KEY_DOWN) {// 相机向当前面对方向后退
        float len = sqrt(camera.pos_x * camera.pos_x + camera.pos_y * camera.pos_y + camera.pos_z * camera.pos_z);
        len = 1 / len;
        camera.pos_x += camera.pos_x * len;
        camera.pos_y += camera.pos_y * len;
        camera.pos_z += camera.pos_z * len;
        camera.updateDistance();
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotate Teapot");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutSpecialFunc(spec_keyboard);
    // 空闲回调直接和显示回调相同，直接重绘便于保持矩阵的状态
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}