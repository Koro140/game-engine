#include "Texture.h"

namespace Engine
{
    class Renderer
    {
    public:
        static Renderer& getInstance() {
            static Renderer renderer;
            return renderer;
        }

    private:
        Renderer() {}
        ~Renderer() {}

        // deleting operators
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer(Renderer&&) = delete;
        Renderer& operator=(Renderer&&) = delete;
    };
}
