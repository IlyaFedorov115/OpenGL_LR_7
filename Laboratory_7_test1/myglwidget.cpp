#include "myglwidget.h"



MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}


void MyGLWidget::setRotateX(bool param) {rotateX = param; update();}
void MyGLWidget::setRotateY(bool param) {rotateY = param; update();}
void MyGLWidget::setRotateZ(bool param) {rotateZ = param; update();}

void MyGLWidget::setRotateLight(bool param){  rotateLight = param; update();}

void MyGLWidget::rotateLight0() { thetaLight0 += 1.0f; update();}

void MyGLWidget::changeHightLight0(int param){ hightLight0 = float(param)/10.0; update();}

void MyGLWidget::setIsDrawCube(bool param) { isDrawCube = param; update();}

void MyGLWidget::setIsDrawField(bool param) { isDrawField = param; update();}


void MyGLWidget::startInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-1,1, -1,1, 2,50);
    glFrustum(-0.1,0.1, -0.1,0.1, 0.2,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
}


void MyGLWidget::initializeGL()
{
    startInit();
    initLight();
    paintGL();
}


void MyGLWidget::paintGL()
{
    glPushMatrix();
        moveCamera();
        drawScene();
    glPopMatrix();
}
void MyGLWidget::resizeGL(int w, int h){
//    glViewport(0,0,w,h);
}


void MyGLWidget::initLight()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);         //нормализуем вектора нормали поверхностей
}

void MyGLWidget::drawScene()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glRotatef(-60, 1, 0, 0);
        glRotatef(33, 0,0,1);
        glTranslatef(2, 3, -2);

        // вращение 0-го источника
        glPushMatrix();
            if (rotateX) glRotatef(thetaLight0, 1,0,0);
            if (rotateY) glRotatef(thetaLight0, 0,1,0);
            if (rotateZ) glRotatef(thetaLight0, 0,0,1);

            glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);

            // отображение источника
            glTranslatef(0,0,hightLight0);
            glScalef(0.15, 0.15, 0.15);
            glColor3f(1,1,1);
            drawField();
        glPopMatrix();

        glColor3f(0,1,0);
        if (isDrawField) drawField();
        if (isDrawCube) drawCube();
    glPopMatrix();


}


void MyGLWidget::drawSquare(float* vertex, float* normal)
{
    //glNormal3f(0, 0, 1)
    glPushMatrix();
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, vertex);
            glNormalPointer(GL_FLOAT, 0, normal);       // задаем массив нормалей
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
    glPopMatrix();
}

void MyGLWidget::drawField()
{
    float vertex[12] = {-1,-1,0, 1,-1,0, 1,1,0, -1,1,0};
    float normal[12] = {-1,-1,3, 1,-1,3, 1,1,3, -1,1,3};
    glPushMatrix();
        glScalef(fieldSize, fieldSize, fieldSize);
        drawSquare(vertex, normal);
    glPopMatrix();
}

void MyGLWidget::drawCube()
{
    float vertex[12] = {-1,-1,1, 1,-1,1, 1,1,1, -1,1,1};
    float normal[12] = {-1,-1,1, 1,-1,1, 1,1,1, -1,1,1};
    glPushMatrix();
        glTranslatef(0, 0, 0.6);
        glScalef(cubeSize, cubeSize, cubeSize);
        drawSquare(vertex, normal);
        glRotatef(90, 1,0,0);
        drawSquare(vertex, normal);
        glRotatef(90, 1,0,0);
        drawSquare(vertex, normal);
        glRotatef(90, 1,0,0);
        drawSquare(vertex, normal);
        glRotatef(90, 0,1,0);
        drawSquare(vertex, normal);
        glRotatef(180, 0,1,0);
        drawSquare(vertex, normal);
    glPopMatrix();
}

void MyGLWidget::moveCamera()
{
    glRotatef(-x_alpha, 1,0,0);
    glRotatef(-y_alpha, 0,1,0);
    glRotated(-z_alpha, 0,0,1);
    glTranslatef(cam_x,cam_y,cam_z);
}


void MyGLWidget::movePointView(QKeyEvent *e)
{
    switch (e->key()) {
        case Qt::Key_W:
            x_alpha = ++(x_alpha) > 180 ? 180 : x_alpha;
            break;
        case Qt::Key_S:
            x_alpha = --(x_alpha) < 0 ? 0 : x_alpha;
            break;
        case Qt::Key_A:
            z_alpha++;
            break;
        case Qt::Key_D:
            z_alpha--;
            break;
        case Qt::Key_Z:
            y_alpha++;
            break;
        case Qt::Key_X:
            y_alpha--;
            break;
        // camera
        case Qt::Key_C:
            cam_x += 0.1;
            break;
        case Qt::Key_V:
            cam_x -= 0.1;
            break;
        case Qt::Key_B:
            cam_y += 0.1;
            break;
        case Qt::Key_N:
            cam_y -= 0.1;
            break;
        case Qt::Key_F:
            cam_z += 0.1;
            break;
        case Qt::Key_G:
            cam_z -= 0.1;
            break;
    }
    update();
}
