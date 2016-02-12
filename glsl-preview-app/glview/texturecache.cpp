#include "texturecache.h"
#include <qmap.h>
#include <qstack.h>
#include <qdebug.h>
#include <QImage>
#include <QGLWidget>
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

    if (availableSlots.size() == 0) {
        Logger::error("Full Texture Cache. Cannot load " + imgpath);
        return;
    }

    const char* image_source = imgpath.toStdString().c_str();

    QImage img;
    if (!img.load(image_source)) {
        Logger::error("Cannot load texture: " + imgpath);
        return;
    }

    QImage glFormattedImage = QGLWidget::convertToGLFormat(img);

    if (glFormattedImage.isNull()) {
        Logger::error("Cannot convert texture to OpenGL format: " + imgpath);
        return;
    }

    TextureInfo info = GetNextTextureInof();

    int width = glFormattedImage.width();
    int height = glFormattedImage.height();

    glActiveTexture(GL_TEXTURE0 + info.slot);
    glGenTextures(1, &info.texId);
    glBindTexture(GL_TEXTURE_2D, info.texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, glFormattedImage.bits());

    cache[imgpath] = info;

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

















