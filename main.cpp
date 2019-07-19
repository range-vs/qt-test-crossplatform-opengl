#include <QApplication>
#include <QScreen>
#include <QGuiApplication>

#include "openglrender.h"
#include  "renderopengl.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    OpenGLRender openGlRender;
    openGlRender.resize(600, 400);
    openGlRender.show();

//    QScreen* screen = QGuiApplication::primaryScreen();
//    RenderOpenGL* renderOpenGL = new RenderOpenGL(screen);
//    renderOpenGL->resize(600, 400);
//    renderOpenGL->show();

    return a.exec();
}
