
#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>

bool GLWidget::m_transparent = false;
GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;
    int m_frame=0;
GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_xRot(0),
      m_yRot(0),
      m_zRot(0),
      m_program(0)
{
    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
    // --transparent causes the clear color to be transparent. Therefore, on systems that
    // support it, the widget will become transparent apart from the logo.
    if (m_transparent) {
        QSurfaceFormat fmt = format();
        fmt.setAlphaBufferSize(8);
        setFormat(fmt);
    }
}

GLWidget::~GLWidget()
{
    cleanup();
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void GLWidget::cleanup()
{
    if (m_program == nullptr)
        return;
    makeCurrent();
    m_logoVbo.destroy();
    delete m_program;
    m_program = 0;
    doneCurrent();
}


static const char *vertexShaderSource =
    "attribute highp vec4 posAttr;\n"
    "attribute lowp vec4 colAttr;\n"
    "varying lowp vec4 col;\n"
    "uniform highp mat4 matrix;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = matrix * posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying lowp vec4 col;\n"
    "void main() {\n"
    "   gl_FragColor = col;\n"
    "}\n";

void GLWidget::initializeGL()
{
//    // In this example the widget's corresponding top-level window can change
//    // several times during the widget's lifetime. Whenever this happens, the
//    // QOpenGLWidget's associated context is destroyed and a new one is created.
//    // Therefore we have to be prepared to clean up the resources on the
//    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
//    // the signal will be followed by an invocation of initializeGL() where we
//    // can recreate all resources.
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();
//    glClearColor(0, 0, 0, m_transparent ? 0 : 1);

//    m_program = new QOpenGLShaderProgram;
//    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, m_core ? vertexShaderSourceCore : vertexShaderSource);
//    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, m_core ? fragmentShaderSourceCore : fragmentShaderSource);
//    m_program->bindAttributeLocation("vertex", 0);
//    m_program->bindAttributeLocation("normal", 1);
//    m_program->link();

//    m_program->bind();
//    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
//    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
//    m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
//    m_lightPosLoc = m_program->uniformLocation("lightPos");

//    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
//    // implementations this is optional and support may not be present
//    // at all. Nonetheless the below code works in all cases and makes
//    // sure there is a VAO when one is needed.
//    m_vao.create();
//    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

//    // Setup our vertex buffer object.
//    m_logoVbo.create();
//    m_logoVbo.bind();
//    m_logoVbo.allocate(m_logo.constData(), m_logo.count() * sizeof(GLfloat));

//    // Store the vertex attribute bindings for the program.
//    setupVertexAttribs();

//    // Our camera never changes in this example.
//    m_camera.setToIdentity();
//    m_camera.translate(0, 0, -1);

//    // Light position is fixed.
//    m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

//    m_program->release();


        m_program = new QOpenGLShaderProgram(this);
          m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
          m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
          m_program->link();
          m_posAttr = m_program->attributeLocation("posAttr");
          m_colAttr = m_program->attributeLocation("colAttr");
          m_matrixUniform = m_program->uniformLocation("matrix");

}

void GLWidget::setupVertexAttribs()
{
//    m_logoVbo.bind();
//    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
//    f->glEnableVertexAttribArray(0);
//    f->glEnableVertexAttribArray(1);
//    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
//    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
//    m_logoVbo.release();
}

void GLWidget::paintGL()
{
      const qreal retinaScale = devicePixelRatio();
          glViewport(0, 0, width() * retinaScale, height() * retinaScale);

          glClear(GL_COLOR_BUFFER_BIT);

          m_program->bind();
          m_world.setToIdentity();

          QMatrix4x4 matrix;
          matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
          matrix.translate(0, 0, -2);
          matrix.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
          matrix.rotate(m_yRot / 16.0f, 0, 1, 0);
          matrix.rotate(m_zRot / 16.0f, 0, 0, 1);

//          matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

          m_program->setUniformValue(m_matrixUniform, matrix);

          GLfloat vertices[] = {
              0.0f, 0.707f,
              -0.5f, -0.5f,
              0.5f, -0.5f
          };

          GLfloat colors[] = {
              1.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 1.0f
          };

          glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
          glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

          glEnableVertexAttribArray(0);
          glEnableVertexAttribArray(1);

          glDrawArrays(GL_TRIANGLES, 0, 3);

          glDisableVertexAttribArray(1);
          glDisableVertexAttribArray(0);

          m_program->release();

          ++m_frame;
}

void GLWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xRot + 8 * dy);
        setYRotation(m_yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(m_xRot + 8 * dy);
        setZRotation(m_zRot + 8 * dx);
    }
    m_lastPos = event->pos();
}
