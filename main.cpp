#include <QApplication>

#include "openglrender.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    OpenGLRender openGlRender;
    openGlRender.resize(600, 400);
    openGlRender.show();

    return a.exec();
}
