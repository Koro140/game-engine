#include "Core/ResourceManager/ResourceManager.h"

#include <map>
#include <memory>

static std::map<std::string, std::unique_ptr<Engine::Shader>> s_shaderMap;
static std::map<std::string, std::unique_ptr<Engine::Texture>> s_textureMap;

namespace Engine
{
    Texture* ResourceManager::LoadTexture(const char *filePath, std::string name)
    {
        std::unique_ptr<Texture> texture = std::make_unique<Texture>(filePath);
        s_textureMap[name] = std::move(texture);
        return s_textureMap[name].get();
    }
    
    Texture *ResourceManager::GetTexture(std::string name)
    {
        auto it = s_textureMap.find(name);
        if (it != s_textureMap.end())
        {
            return it->second.get();
        }
        return nullptr;
    }
    
    Shader *ResourceManager::LoadShader(const char *vFilePath, const char *fFilePath, const char *gFilePath, std::string name)
    {
        std::unique_ptr<Shader> shader = std::make_unique<Shader>(vFilePath, fFilePath);
        s_shaderMap[name] = std::move(shader);
        return s_shaderMap[name].get();
    }

    Shader *ResourceManager::GetShader(std::string name)
    {
        auto it = s_shaderMap.find(name);
        if (it != s_shaderMap.end())
        {
            return it->second.get();
        }
        return nullptr;
    }

    void ResourceManager::clear() {
        s_shaderMap.clear();
        s_textureMap.clear();
    }
}
