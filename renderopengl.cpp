#include "renderopengl.h"

RenderOpenGL::RenderOpenGL(QScreen* screen): QWindow(screen)
{
    setSurfaceType(OpenGLSurface);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
    create();

    m_context = new QOpenGLContext;
    m_context->setFormat(format);
    m_context->create();

    m_context->makeCurrent(this);

    m_funcs = dynamic_cast<QOpenGLFunctions_3_3_Core*>(m_context->versionFunctions());

    if (!m_funcs)
    {
        qWarning("Could not obtain OpenGL versions object");
        exit(1);
    }

    m_funcs->initializeOpenGLFunctions();
}
