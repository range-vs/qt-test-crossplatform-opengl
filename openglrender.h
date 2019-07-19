#ifndef OPENGLRENDER_H
#define OPENGLRENDER_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>

#include <fstream>
#include <sstream>

class OpenGLRender: public QOpenGLWidget
{
    QOpenGLFunctions* func;
    QOpenGLVertexArrayObject* vao1;
    GLuint vertexbuffer;
    GLuint colorbuffer;
    QTimer* updateRender;
    GLuint programID;
    QMatrix4x4 MVP;
    QMatrix4x4 Model;
    QMatrix4x4 Projection;
    QMatrix4x4 View;
    GLuint MatrixID;
    float angle;

    void initScene();
    void initRenderLoop();
    void initCamera();
    void stepRotate();
    GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path);
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
public:
    OpenGLRender(QWidget* parent = nullptr);
    ~OpenGLRender();
public slots:
    void updateScene();
};

#endif // OPENGLRENDER_H
