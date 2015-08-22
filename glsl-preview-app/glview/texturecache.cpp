#include "texturecache.h"
#include <qmap.h>
#include <qstack.h>
#include <qdebug.h>
#include <FreeImage.h>
#include "logger.h"

static QMap<QString, TextureCache::TextureInfo> cache;

static QStack<GLuint> InitTextureSlots()
{
    QStack<GLuint> texSlots;
    for (int i = 31; i >= 0; i--) {
        texSlots.push(i);
    }
    return texSlots;
}

static QStack<GLuint> availableSlots = InitTextureSlots();

static TextureCache::TextureInfo GetNextTextureInof()
{
    TextureCache::TextureInfo info;
    info.texId = 0;
    info.slot = availableSlots.pop();
    return info;
}

void TextureCache::LoadTexture(const QString &imgpath)
{

    if (cache.contains(imgpath)) {
        Logger::info("Using cached texture: " + imgpath);
        return;
    }

    //qDebug() << cache.size();

    if (availableSlots.size() == 0) {
        Logger::error("Full Texture Cache. Cannot load " + imgpath);
        return;
    }

    TextureInfo info = GetNextTextureInof();

    const char* image_source = imgpath.toStdString().c_str();
    FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(image_source, 0), image_source);

    if (!bitmap) {
        Logger::error("Cannot load texture: " + imgpath);
        return;
    }


    FIBITMAP* bitmap32bit = FreeImage_ConvertTo32Bits(bitmap);
    FreeImage_Unload(bitmap);

    int width = FreeImage_GetWidth(bitmap32bit);
    int height = FreeImage_GetHeight(bitmap32bit);

    glActiveTexture(GL_TEXTURE0 + info.slot);
    glGenTextures(1, &info.texId);
    glBindTexture(GL_TEXTURE_2D, info.texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(bitmap32bit));

    cache[imgpath] = info;

    FreeImage_Unload(bitmap32bit);

    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
}

void TextureCache::Reloadtexture(const QString& imgpath)
{
    TextureCache::UnloadTexture(imgpath);
    TextureCache::LoadTexture(imgpath);
}

void TextureCache::UnloadTexture(const QString& imgpath)
{
    if (!cache.contains(imgpath)) {
        return;
    }

    TextureInfo info = cache[imgpath];
    glDeleteTextures(1, &info.texId);
    availableSlots.push(info.slot);
    cache.remove(imgpath);
}

void TextureCache::BindTexture(const QString &imgpath, GLuint location)
{
    if (!cache.contains(imgpath)) {
        //Logger::error("Cannot bind texture: " + imgpath);
        return;
    }

    TextureInfo info = cache[imgpath];
    glUniform1i(location, info.slot);
    glActiveTexture(GL_TEXTURE0 + info.slot);
    glBindTexture(GL_TEXTURE_2D, info.texId);
}

















