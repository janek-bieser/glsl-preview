#ifndef SHADERLIBRARY_H
#define SHADERLIBRARY_H

#include <qopenglshaderprogram.h>

class ShaderLibrary
{
public:
    enum BuiltinShader {
        SolidFillShader = 0,
        CheckerShader,
        BuiltinShaderCount
    };

    static void compileAll();
    static QOpenGLShaderProgram* getShader(BuiltinShader shader);

public:
    ShaderLibrary();

    static QOpenGLShaderProgram* shaders[BuiltinShaderCount];
};

#endif // SHADERLIBRARY_H
