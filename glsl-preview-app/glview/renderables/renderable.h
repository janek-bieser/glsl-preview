#ifndef RENDERABLE
#define RENDERABLE

class Renderable {
public:
    virtual ~Renderable() = default;
    virtual void render() = 0;
};

#endif // RENDERABLE

