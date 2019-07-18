#include "openglrender.h"


void OpenGLRender::initScene()
{
    const GLfloat g_vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // Треугольник 1 : начало
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // Треугольник 1 : конец
        1.0f, 1.0f,-1.0f, // Треугольник 2 : начало
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // Треугольник 2 : конец
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };
    func->glGenBuffers(1, &vertexbuffer);
    func->glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    func->glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    const GLfloat g_color_buffer_data[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.676f,  0.977f,  0.133f,
        0.971f,  0.572f,  0.833f,
        0.140f,  0.616f,  0.489f,
        0.997f,  0.513f,  0.064f,
        0.945f,  0.719f,  0.592f,
        0.543f,  0.021f,  0.978f,
        0.279f,  0.317f,  0.505f,
        0.167f,  0.620f,  0.077f,
        0.347f,  0.857f,  0.137f,
        0.055f,  0.953f,  0.042f,
        0.714f,  0.505f,  0.345f,
        0.783f,  0.290f,  0.734f,
        0.722f,  0.645f,  0.174f,
        0.302f,  0.455f,  0.848f,
        0.225f,  0.587f,  0.040f,
        0.517f,  0.713f,  0.338f,
        0.053f,  0.959f,  0.120f,
        0.393f,  0.621f,  0.362f,
        0.673f,  0.211f,  0.457f,
        0.820f,  0.883f,  0.371f,
        0.982f,  0.099f,  0.879f
    };

    func->glGenBuffers(1, &colorbuffer);
    func->glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    func->glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    programID = loadShaders( "shaders/cube.glvs", "shaders/cube.glps" );
    MatrixID = func->glGetUniformLocation(programID, "MVP");
}

void OpenGLRender::initRenderLoop()
{
    updateRender = new QTimer(this);
    updateRender->setInterval(10);
    connect(updateRender, &QTimer::timeout, this, &OpenGLRender::updateScene);
    updateRender->start();
}

void OpenGLRender::initCamera()
{
    Projection.perspective(qDegreesToRadians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);

    View.lookAt(
        QVector3D(0,180,300),
        QVector3D(0,0,0),
        QVector3D(0,1,0)
    );

    // Итоговая матрица ModelViewProjection, которая является результатом перемножения наших трех матриц
    MVP = Projection * View * Model; // умножение матрицы производиться в обратном порядке
}

void OpenGLRender::stepRotate()
{
    if(qAbs(angle - 360.f) <= 0.001f)
        angle = 0;
    else
        angle += 1.3f;
    Model.setToIdentity();
    Model.rotate(angle, QVector3D(0.f,1.f,0.f));
    MVP = Projection * View * Model;
}

GLuint OpenGLRender::loadShaders(const char *vertex_file_path, const char *fragment_file_path)
{
    // Создаем шейдеры
    GLuint VertexShaderID = func->glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = func->glCreateShader(GL_FRAGMENT_SHADER);

    // Загружаем код Вершинного Шейдера из файла
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }

    // Загружаем код Фрагментного шейдера из файла
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Компилируем Вершинный шейдер
    printf("Компиляция шейдера: %sn", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    func->glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    func->glCompileShader(VertexShaderID);

    // Выполняем проверку Вершинного шейдера
    func->glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    func->glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        func->glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        fprintf(stdout, "%sn", &VertexShaderErrorMessage[0]);
    }

    // Компилируем Фрагментный шейдер
    printf("Компиляция шейдера: %sn", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    func->glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    func->glCompileShader(FragmentShaderID);

    // Проверяем Фрагментный шейдер
    func->glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    func->glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        func->glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Создаем шейдерную программу и привязываем шейдеры к ней
    fprintf(stdout, "Создаем шейдерную программу и привязываем шейдеры к нейn");
    GLuint ProgramID = func->glCreateProgram();
    func->glAttachShader(ProgramID, VertexShaderID);
    func->glAttachShader(ProgramID, FragmentShaderID);
    func->glLinkProgram(ProgramID);

    // Проверяем шейдерную программу
    func->glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    func->glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        func->glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
    }

    func->glDeleteShader(VertexShaderID);
    func->glDeleteShader(FragmentShaderID);

    return ProgramID;
}

void OpenGLRender::initializeGL()
{
    func = QOpenGLContext::currentContext()->functions();
    func->glClearColor(0.27f, 0.29f, 0.31f, 1.f);

    vao1 = new QOpenGLVertexArrayObject(this);
    vao1->create();
    vao1->bind();

    initScene();
    initCamera();
    initRenderLoop();

    func->glEnable(GL_DEPTH_TEST);
    func->glDepthFunc(GL_LESS);

    // get version open gl
    /*QMessageBox msg;
    char* version = (char*)glGetString(GL_VERSION);
    msg.setText(QString(version));
    msg.exec();*/
}

void OpenGLRender::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0, static_cast<GLint>(w), static_cast<GLint>(h));
    glOrtho(0, 100, 100, 0, -1, -1);
}

void OpenGLRender::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->stepRotate();
    func->glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP(0, 0));

    func->glUseProgram(programID);

    func->glEnableVertexAttribArray(0);
    func->glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    func->glVertexAttribPointer(
       0,
       3,                  // Размер
       GL_FLOAT,           // Тип
       GL_FALSE,           // Указывает, что значения не нормализованы
       0,                  // Шаг
       static_cast<void*>(0)            // Смещение массива в буфере
    );

    func->glEnableVertexAttribArray(1);
    func->glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    func->glVertexAttribPointer(
        1,
        3,                                // Размер
        GL_FLOAT,                         // Тип
        GL_FALSE,                         // Нормализован?
        0,                                // Шаг
        static_cast<void*>(0)                           // Смещение
    );

    func->glDrawArrays(GL_TRIANGLES, 0, 36);

    func->glDisableVertexAttribArray(0);
    func->glDisableVertexAttribArray(1);
}

OpenGLRender::OpenGLRender(QWidget *parent): QGLWidget(parent), angle(0.f)
{
}

OpenGLRender::~OpenGLRender()
{
    delete vao1;
    delete updateRender;
}

void OpenGLRender::updateScene()
{
    updateGL();
}


