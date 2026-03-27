#include "Core/Renderer/Texture.h"
#include "Core/Renderer/Shader.h"

namespace Engine
{
    namespace ResourceManager
    {
        Texture* LoadTexture(const char* filePath, std::string name);
        Texture* GetTexture(std::string name);

        Shader* LoadShader(const char* vFilePath, const char* fFilePath, const char* gFilePath, std::string name);
        Shader* GetShader(std::string name);

        void clear();
    }
}