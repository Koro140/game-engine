#include "Core/Renderer/Texture.h"
#include "Core/Renderer/Shader.h"
#include "Core/Audio/Audio.h"

namespace Engine
{
    namespace ResourceManager
    {
        Texture* LoadTexture(const char* filePath, const std::string& name);
        Texture* GetTexture(const std::string& name);

        Shader* LoadShader(const char* vFilePath, const char* fFilePath, const char* gFilePath, const std::string& name);
        Shader* GetShader(const std::string& name);

        Audio* LoadAudio(const char* filePath, const std::string& name);
        Audio* GetAudio(const std::string& name);


        void clear();
    }
}