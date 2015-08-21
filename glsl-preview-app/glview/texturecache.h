#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <qopengl.h>
#include <qstring.h>

class TextureCache
{
public:
    struct TextureInfo
    {
        GLuint texId;
        GLuint slot;
    };

    static void LoadTexture(const QString& imgpath);
    static void BindTexture(const QString& imgpath, GLuint location);

private:
    TextureCache() {}
};

#endif // TEXTURECACHE_H
