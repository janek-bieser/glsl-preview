#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <qopengl.h>
#include <qstring.h>

/*!
 * \brief Utility class to load and cache images/textures.
 */
class TextureCache
{
public:

    /*!
     * \brief Information about one texture.
     */
    struct TextureInfo
    {
        /*!
         * \brief The texture id.
         */

        GLuint texId;
        /*!
         * \brief The texture slot.
         */
        GLuint slot;
    };

    /*!
     * \brief Load a texture.
     * \param imgpath Path to the image file.
     */
    static void LoadTexture(const QString& imgpath);

    /*!
     * \brief Clear the cached texture and reload it from a file.
     * \param imgpath Path to the image file.
     */
    static void Reloadtexture(const QString& imgpath);

    /*!
     * \brief Remove a texture from the cache.
     * \param imgpath Path to the image file.
     */
    static void UnloadTexture(const QString& imgpath);

    /*!
     * \brief Bind a certain texture to a certain texture location. This will use
     *        the cached texture if it exists, it will be loaded otherwise.
     * \param imgpath Path to the image file.
     * \param location Location
     */
    static void BindTexture(const QString& imgpath, GLuint location);

private:
    TextureCache() {}
};

#endif // TEXTURECACHE_H
