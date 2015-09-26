#ifndef SHADERLIBRARY_H
#define SHADERLIBRARY_H

#include <qopenglshaderprogram.h>

/*!
 * \brief Utility class for builtin shaders.
 */
class ShaderLibrary
{
public:
    enum BuiltinShader {
        SolidFillShader = 0,
        CheckerShader,
        BuiltinShaderCount
    };

    /*!
     * \brief Compiles all the built-in shaders.
     */
    static void compileAll();

    /*!
     * \brief Get a shader object from the library.
     * \param shader The type of shader to get.
     * \return The shader object
     */
    static QOpenGLShaderProgram* getShader(BuiltinShader shader);

private:
    ShaderLibrary();
    static QOpenGLShaderProgram* shaders[BuiltinShaderCount];
};

#endif // SHADERLIBRARY_H
