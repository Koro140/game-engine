#include "Shader.h"

namespace Engine
{
    class Renderer2D
    {
    private:
        Shader* shader2D;
        unsigned int VAO, VBO, EBO;
    public:
        static Renderer2D& getInstance() {
            static Renderer2D renderer;
            return renderer;
        }

        void LoadTexture();
        void DrawTexture();
    private:
        Renderer2D();
        
        // deleting operators
        Renderer2D(const Renderer2D&) = delete;
        Renderer2D& operator=(const Renderer2D&) = delete;
        Renderer2D(Renderer2D&&) = delete;
        Renderer2D& operator=(Renderer2D&&) = delete;
        void destroy();
        
        friend class Application;
    };
}
