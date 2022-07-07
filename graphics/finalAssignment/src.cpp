#include <GL/glut.h>
#include <cmath>
#include <iostream>

#define ROTATE_STEP 0.02 // 相机视角旋转步长，作为鼠标灵敏度
#define MOVE_STEP 3 // 相机位置移动步长

int window_height = 600;
int window_width = 800;
bool mouse_capture = false;

// 以width*height的尺寸与depth的位深度读入图片文件filename，首地址存于指针data中
void load_image(char *filename, int width, int height, int depth, GLubyte **data);

// 定义贴图结构体
typedef struct Texture {
    int width, height; // 图片的宽高
    int depth; // 图片的位深度，包括所有通道
    GLenum color_type; // 颜色的类型，bmp文件应使用GL_BGR_EXT
    GLuint id; // 此纹理贴图的id
    GLenum filter_type; // 放大与缩小过滤的过滤类型
    Texture(int width, int height, int depth, GLenum colorType, GLenum filterType, GLuint id) {
        this->width = width;
        this->height = height;
        this->depth = depth;
        this->color_type = colorType;
        this->filter_type = filterType;
        this->id = id;
    }

    // 加载图片文件到贴图中，同时生成mipmap
    void loadImage(char *filename, GLenum env_mode) const {
        GLubyte *data;
        load_image(filename, width, height, depth, &data);
        // data = stbi_load(filename, &width, &height, &depth, 0);
        //  设置过滤类型
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_type);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_type);

        // 切换到当前id的纹理
        glBindTexture(GL_TEXTURE_2D, id);
        // 设置纹理环境，可选值GL_MODULATE、GL_DECAL、GL_BLEND、GL_REPLACE
        // 分别为纹理颜色调制、纹理颜色贴花、纹理颜色混合、纹理颜色替代
        GLfloat texture_color[] = {0.0f, 0.0f, 0.0f, 1.0f};
        // glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, texture_color);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, env_mode);
        // 生成mipmap
        // glTexImage2D(GL_TEXTURE_2D, 0, depth, width, height, 0, color_type, GL_UNSIGNED_BYTE, data);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, color_type, GL_UNSIGNED_BYTE, data);

        free(data);
    }
} Texture;

typedef struct Camera {
    float pos_x, pos_y, pos_z;
    float pitch, yaw; // 偏航角、俯仰角，向上为正，向左为正
    float forward_x, forward_y, forward_z; // 前向量
    float up_x, up_y, up_z; // 上向量

    Camera() {
        pos_x = 0;
        pos_y = 0;
        pos_z = 0;
        pitch = 0;
        yaw = 0;
        forward_x = 0;
        forward_y = 0;
        forward_z = -1;
        up_x = 0;
        up_y = 1;
        up_z = 0;
    }

    void reset() {
        pos_x = 0;
        pos_y = 0;
        pos_z = 0;
        pitch = 0;
        yaw = 0;
        forward_x = 0;
        forward_y = 0;
        forward_z = -1;
        up_x = 0;
        up_y = 1;
        up_z = 0;
    }

    void refreshCamera() const {

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, (float) window_width / (float) window_height, 1.0f, 1000.0f); // 指定透视投影的观察空间
        glTranslatef(-pos_x, -pos_y, -pos_z);
        glRotatef(pitch, 1.0f, 0.0f, 0.0f);
        glRotatef(yaw, 0.0f, 1.0f, 0.0f);
        // std::cout << "pitch: " << pitch << " yaw: " << yaw << std::endl;
        // std::cout << "pos_x: " << pos_x << " pos_y: " << pos_y << " pos_z: " << pos_z << std::endl;

        glutPostRedisplay();
    }

    void move_forward(float distance) {
        // 向前向量方向移动distance
        float forward = sqrt(forward_x * forward_x + forward_y * forward_y + forward_z * forward_z);
        pos_x += distance * forward_x / forward;
        pos_y += distance * forward_y / forward;
        pos_z += distance * forward_z / forward;
    }

    void move_backward(float distance) {
        move_forward(-distance);
    }

    void move_left(float distance) {
        float left_x = up_y * forward_z - up_z * forward_y;
        float left_y = up_z * forward_x - up_x * forward_z;
        float left_z = up_x * forward_y - up_y * forward_x;
        // left为左向量，即前向量与上向量的叉乘
        float left = sqrt(left_x * left_x + left_y * left_y + left_z * left_z);
        pos_x += distance * left_x / left;
        pos_y += distance * left_y / left;
        pos_z += distance * left_z / left;
    }

    void move_right(float distance) {
        move_left(-distance);
    }

    void rotate(float pitch, float yaw) {
        this->pitch += pitch;
        this->yaw += yaw;
        if (this->pitch > 90.0f) {
            this->pitch = 90.0f;
        } else if (this->pitch < -90.0f) {
            this->pitch = -90.0f;
        }
        if (this->yaw > 360.0f) {
            this->yaw -= 360.0f;
        } else if (this->yaw < 0.0f) {
            this->yaw += 360.0f;
        }
    }

} Camera;

// 纹理贴图id，1、2、3分别对应太阳、地球、月球
GLuint tex_id[] = {1, 2, 3};

Camera camera;
float earthDegree = 0.0f;
float earthSelfDegree = 0.0f;
float moonDegree = 0.0f;
GLUquadricObj *q = gluNewQuadric();


// 加载太阳、地球、月球的纹理贴图
void LoadTextures() {
    char sun[] = "./tex/sun.bmp";
    char earth[] = "./tex/earth.bmp";
    char moon[] = "./tex/moon.bmp";
    int image_width = 2048, image_height = 1024;
    Texture Sun(image_width, image_height, 24, GL_BGR_EXT, GL_LINEAR, tex_id[0]);
    Texture Earth(image_width, image_height, 24, GL_BGR_EXT, GL_LINEAR, tex_id[1]);
    Texture Moon(image_width, image_height, 24, GL_BGR_EXT, GL_LINEAR, tex_id[2]);
    // 请求纹理单元
    // glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenTextures(3, tex_id);

    Sun.loadImage(sun, GL_REPLACE);
    Earth.loadImage(earth, GL_MODULATE);
    Moon.loadImage(moon, GL_MODULATE);
}

// 将地球画在(0, 0, -400)处，半径为50
void drawSun() {
    glColor3f(1.0f, 0.0f, 0.0f);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, tex_id[0]);
    glTranslatef(0.0f, 0.0f, -400.0f); // z轴负向移动400
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f); // 绕x轴顺时针转90，使z轴向上
    gluSphere(q, 50.0f, 100, 100);
}

// 以(0, 0, -400)为圆心画地球，半径为20
void drawEarth() {
    glColor3f(0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // 设置漫反射系数、镜面反射系数与材料反射指数
    GLfloat mat_diffuse[] = {0.8f, 0.8f, 1.0f, 0.0};
    GLfloat mat_specular[] = {0.5, 0.5, 0.5, 0.0};
    GLfloat mat_shininess[] = {50.0};


    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);//设置环境光系数和漫反射光系数
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);//set material 镜面光反射
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//设置材料反射指数

    glTranslatef(0.0f, 0.0f, -400.0f); // z轴负向移动400
    glRotatef(earthDegree, 0.0f, 1.0f, 0.0f); // 绕y轴逆时针转earthDegree，做出地球绕太阳公转的角度
    glTranslatef(200.0f, 0.0f, 0.0f); // 向x轴平移200，即轨道半径

    glRotatef(earthDegree, 0.0f, -1.0f, 0.0f); // 绕y轴顺时针转earthDegree，y、z轴归位
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f); // 绕x轴顺时针转90，使z轴向上
    glRotatef(23.4f, 0.0f, 1.0f, 0.0f); // 绕y轴逆时针转23.4°，做出地轴的倾斜
    glRotatef(earthSelfDegree, 0.0, 0.0, -1.0f); // 绕z逆时针自转

    glBindTexture(GL_TEXTURE_2D, tex_id[1]);
    gluSphere(q, 20.0f, 50, 50);

    glutPostRedisplay();
}

// 以地球为圆心画月球，半径为5
void drawMoon() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    GLfloat mat_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.2, 1.0};
    GLfloat mat_shininess[] = {50.0};


    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);//设置环境光系数和漫反射光系数
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);//set material 镜面光反射
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//设置材料反射指数

    glBindTexture(GL_TEXTURE_2D, tex_id[2]);
    glTranslatef(0.0f, 0.0f, -400.0f); // z轴负向移动400
    glRotatef(earthDegree, 0.0f, 1.0f, 0.0f); // 绕y轴逆时针转earthDegree公转角
    glTranslatef(200.0f, 0.0f, 0.0f); // 向x轴移200，原点到达地球位置
    glRotatef(earthDegree, 0.0f, -1.0f, 0.0f); // 绕y轴顺时针转earthDegree，y、z轴归位
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f); // 绕x轴顺时针转90，使z轴向上
    glRotatef(5.14f, 0.0f, -1.0f, 1.0f); // 绕y轴顺时针转5.14°，做出黄白轨道倾斜角
    glRotatef(moonDegree, 0.0f, 0.0f, 1.0f); // 绕y轴转moonDegree，作为月球的公转角
    glTranslatef(40.0f, 0.0f, 0.0f); // 月球公转轨道半径40

    gluSphere(q, 5.0f, 20, 20);

    glutPostRedisplay();
}


void myInit() {
    glEnable(GL_DEPTH_TEST); //启用深度测试
    glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LESS);
    LoadTextures();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(0.0f, 0.0f, 0.0f, 0.8f); //背景为黑色

//    glClearColor(0.0, 0.0, 0.0, 0.0);
//    LoadTextures();
//    glEnable(GL_TEXTURE_2D);
//    glClearDepth(1.0f);    // 设置深度缓存
//    glDepthFunc(GL_LESS);  // 选择深度测试方式
//    glEnable(GL_DEPTH_TEST);  // 开启深度测试
    glShadeModel(GL_SMOOTH);  // 阴暗处理采用平滑方式
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // 最精细的透视计算
//    glBindTexture(GL_TEXTURE_2D, 1);
    gluQuadricDrawStyle(q, GLU_FILL);
    gluQuadricNormals(q, GLU_SMOOTH);
    gluQuadricTexture(q, GL_TRUE);


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // glEnable(GL_COLOR_MATERIAL_FACE);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat light_position[] = {0.0, 0.0, -400.0, 1.0};//最后一个参数为0，表示光源在无穷远处
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // glColor3f(1.0f, 0.0f, 0.0f);
    drawSun();
    drawEarth();
    drawMoon();

    camera.refreshCamera();
    glFlush();
}

void myReshape(int w, int h) {
    window_width = w;
    window_height = h;
    glViewport(0, 0, w, h); // 设置视口大小，保持和窗口大小相同
    glMatrixMode(GL_PROJECTION); // 操作投影矩阵
    glLoadIdentity(); // 先归到单位矩阵
    gluPerspective(50.0f, (float) w / (float) h, 1.0f, 1000.0f); // 指定透视投影的观察空间
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': // 地球公转
        case 'S':
            earthDegree += 2.5f;
            glutPostRedisplay();
            break;
        case 'l':// 通过操作二次曲面绘制实体，进行线框绘制
        case 'L':
            gluQuadricDrawStyle(q, GLU_LINE);
            glutPostRedisplay();
            break;
        case 'f':// 通过操作二次曲面绘制实体，进行填充绘制
        case 'F':
            gluQuadricDrawStyle(q, GLU_FILL);
            glutPostRedisplay();
            break;
        case 'e': // 地球自转
        case 'E':
            earthSelfDegree += 2.5f;
            glutPostRedisplay();
            break;
        case 'y': // 月球公转
        case 'Y':
            moonDegree += 2.5f;
            glutPostRedisplay();
            break;
        case 'm': // 进行鼠标捕获，以进行视角变换
        case 'M':
            mouse_capture = !mouse_capture;
            glutWarpPointer(window_width / 2, window_height / 2);
            if (mouse_capture)
                glutSetCursor(GLUT_CURSOR_NONE);
            else
                glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
            break;
        case 'q': // 退出
        case 'Q':
            exit(0);
        case 'r': // 重置视角到初始位置和角度
        case 'R':
            camera.reset();
            camera.refreshCamera();
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

void specFunc(int key, int x, int y) {
    switch (key) {// 使用方向键进行相机位置的移动
        case GLUT_KEY_LEFT:
            camera.move_left(MOVE_STEP);
            camera.refreshCamera();
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            camera.move_right(MOVE_STEP);
            camera.refreshCamera();
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            camera.move_forward(MOVE_STEP);
            camera.refreshCamera();
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            camera.move_backward(MOVE_STEP);
            camera.refreshCamera();
            break;
        default:
            break;
    }
}

void mouseMove(int x, int y) { // 鼠标移动时，进行视角变换
    if (!mouse_capture)
        return;
    float delta_x = x - window_width / 2;
    float delta_y = y - window_height / 2;
    camera.rotate(delta_y * ROTATE_STEP, delta_x * ROTATE_STEP);
    camera.refreshCamera();
    glutPostRedisplay();
    glutWarpPointer(window_width / 2, window_height / 2); // 强制将鼠标放在窗口中心，进行鼠标捕获
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    //窗口使用RGB颜色，双缓存和深度缓存
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Solar System");
    myInit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(myDisplay);
    // glutSetCursor(GLUT_CURSOR_NONE);
    // glutIdleFunc(myDisplay);
    // glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
    glutSpecialFunc(specFunc);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouseMove);
    glutMainLoop();
    return 0;
}


void load_image(char *filename, int width, int height, int depth, GLubyte **data) {
    // 以二进制读取图片文件
    FILE *file;
    int errNum;
    errNum = fopen_s(&file, filename, "rb");
    if (errNum == ENOENT) {
        std::cout << "file " << filename << " not exist." << std::endl;
        exit(ENOENT);
    } else if (errNum != 0) {
        std::cout << "file " << filename << "read failed with error code " << errNum << std::endl;
    }

    // 先申请空间以存放图片文件
    *data = (GLubyte *) malloc(width * height * depth * sizeof(GLubyte));
    if (*data == nullptr) {
        std::cout << "image memory malloc failed." << std::endl;
        exit(ENOMEM);
    }

    // 读取图片数据到data
    fread(*data, width * height * depth * sizeof(GLubyte), sizeof(GLubyte), file);
    fclose(file);
}
