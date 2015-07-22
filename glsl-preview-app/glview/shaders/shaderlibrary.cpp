#include "shaderlibrary.h"
#include <assert.h>

const char* PositionOnlyVertexSource = "#version 400\n"
        "layout(location=0) in vec3 slp_Vertex;\n"
        "void main() {\n"
        "    gl_Position = vec4(slp_Vertex, 1);\n"
        "}";

const char* PositionOutVertexSource = "#version 400\n"
        "layout(location=0) in vec3 slp_Vertex;\n"
        "out vec3 fragVertex;\n"
        "void main() {\n"
        "    fragVertex = slp_Vertex;\n"
        "    gl_Position = vec4(slp_Vertex, 1);\n"
        "}";

const char* SolidFillColorFragmentSource = "#version 400\n"
        "uniform vec4 SurfaceColor = vec4(1, 0, 0, 1);\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "    fragColor = SurfaceColor;"
        "}";

const char* CheckerFillFragmentSource = "#version 400\n"
        "uniform vec2 Scale = vec2(1, 1);\n"
        "in vec3 fragVertex;\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "    vec2 v = fragVertex.xy * Scale;\n"
        "    if( (int( floor(v.x) + floor(v.y) ) & 1) == 0) {\n"
        "        fragColor = vec4(0, 0, 0, .5);\n"
        "    } else {\n"
        "        fragColor = vec4(1, 1, 1, .5);\n"
        "    }\n"
        "}";

QOpenGLShaderProgram* ShaderLibrary::shaders[BuiltinShaderCount];

ShaderLibrary::ShaderLibrary()
{
}

QOpenGLShaderProgram* compileShaderProgram(const char* vertexSrc, const char* fragmentSrc)
{
    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    vertexShader.compileSourceCode(vertexSrc);

    QString vLog = vertexShader.log();
    if (vLog.length() > 0) {
        qDebug() << vLog;
    }

    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
    fragmentShader.compileSourceCode(fragmentSrc);

    QString fLog = fragmentShader.log();
    if (fLog.length() > 0) {
        qDebug() << fLog;
    }

    QOpenGLShaderProgram* prog = new QOpenGLShaderProgram();
    prog->addShader(&vertexShader);
    prog->addShader(&fragmentShader);
    prog->link();

    QString pLog = prog->log();
    if (pLog.length() > 0) {
        qDebug() << pLog;
    }

    return prog;
}

void ShaderLibrary::compileAll()
{
    shaders[SolidFillShader] = compileShaderProgram(PositionOnlyVertexSource, SolidFillColorFragmentSource);
    shaders[CheckerShader] = compileShaderProgram(PositionOutVertexSource, CheckerFillFragmentSource);
}

QOpenGLShaderProgram* ShaderLibrary::getShader(BuiltinShader shader)
{
    assert(shader >= 0 && shader < BuiltinShaderCount);
    return ShaderLibrary::shaders[shader];
}

