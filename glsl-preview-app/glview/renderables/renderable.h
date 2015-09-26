#ifndef RENDERABLE
#define RENDERABLE

/*!
 * \brief Abstract base class for renderable objects.
 */
class Renderable {
public:
    virtual ~Renderable() = default;

    /*!
     * \brief Renders the object.
     */
    virtual void render() = 0;
};

#endif // RENDERABLE

