#include <GL/glut.h>

#define PROJECTION_X_MIN -5.0
#define PROJECTION_X_MAX 5.0
#define PROJECTION_Y_MIN -5.0
#define PROJECTION_Y_MAX 5.0

void drawDiamond(void) //绘制中心在原点的菱形（宽>高）
{
    glBegin(GL_POLYGON); //顶点指定需要按逆时针方向
    glVertex2f(0.0f, -1.0f);//下点
    glVertex2f(2.0f, 0.0f);//右点
    glVertex2f(0.0f, 1.0f);//上点
    glVertex2f(-2.0f, 0.0f);//左点
    glEnd();
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(PROJECTION_X_MIN, PROJECTION_X_MAX, PROJECTION_Y_MIN, PROJECTION_Y_MAX);
    glMatrixMode(GL_MODELVIEW);
}

void Draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // 先画上方的菱形（红色）
    glLoadIdentity();// 每次都从单位矩阵开始变换
    glColor3f(1.0f, 0.0f, 0.0f);// 设置颜色为红色
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f);// 为了保持代码一致，不旋转写成旋转0°
    glTranslatef(0.0f, 2.0f, 0.0f);// 沿y轴向上平移2个单位
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);// 沿x轴旋转90°，使得菱形高>宽
    drawDiamond();
    glFlush();

    // 画左侧的菱形（绿色）
    glLoadIdentity();
    glColor3f(0.0f, 1.0f, 0.0f);// 设置颜色为绿色
    glRotatef(120.0f, 0.0f, 0.0f, 1.0f);// 沿x轴旋转120°
    glTranslatef(0.0f, 2.0f, 0.0f);// 沿y轴向上平移2个单位
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);// 沿x轴旋转90°，使得菱形高>宽
    drawDiamond();
    glFlush();

    // 最后画右侧的菱形（蓝色）
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 1.0f);// 设置颜色为蓝色
    glRotatef(240.0f, 0.0f, 0.0f, 1.0f);// 沿x轴旋转240°
    glTranslatef(0.0f, 2.0f, 0.0f);// 沿y轴向上平移2个单位
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);// 沿x轴旋转90°，使得菱形高>宽
    drawDiamond();
    glFlush();

}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3-diamond");
    init();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}

