#ifndef RENDEROPENGL_H
#define RENDEROPENGL_H

#include <QWindow>
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_3_Core>

class RenderOpenGL: public QWindow
{

    QOpenGLContext* m_context;
    QOpenGLFunctions_3_3_Core* m_funcs;

public:
    RenderOpenGL(QScreen* screen);
};

#endif // RENDEROPENGL_H
