#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H


#include <QOpenGLWidget>
#include <QKeyEvent>

class MyGLWidget : public QOpenGLWidget
{

    Q_OBJECT

public:    
    MyGLWidget(QWidget *parent = nullptr);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void drawScene();
    void drawSquare(float*, float*);
    void drawCube();
    void drawField();

    void moveCamera();
    void movePointView(QKeyEvent *e);

    void startInit();
    void initLight();

    void rotateLight0();


public slots:
    void setRotateLight(bool);
    void changeHightLight0(int);
    void setIsDrawCube(bool);
    void setIsDrawField(bool);

    void setRotateX(bool);
    void setRotateY(bool);
    void setRotateZ(bool);


private:

    // вспомогательные
    //float vertex[12] = {-1,-1,0, 1,-1,0, 1,1,0, -1,1,0};
    //float normal[12] = {-1,-1,3, 1,-1,3, 1,1,3, -1,1,3};      // интерполяция нормалей


    // ориентирование и
    // передвижение
    float cam_x = 0.0;
    float cam_y = 0.0;
    float cam_z = -8.0;

    float x_alpha = 0.0;
    float y_alpha = 0.0;
    float z_alpha = 0.0;

    //куб
    float cubeSize = 0.4;
    bool isDrawCube = true;
    bool isDrawField = true;

    float fieldSize = 1.5;

    // свет
    bool rotateX = false;
    bool rotateY = true;
    bool rotateZ = false;

    bool rotateLight = true;
    float thetaLight0 = 0.0;
    float lightPosition0[4] = {0, 0, 1, 0};
    float hightLight0 = 2.0;

    float thetaLight1 = 0.0;
    float lightPosition1[4] = {0, 0, 1, 0};





};

#endif // MYGLWIDGET_H
