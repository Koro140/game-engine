#include "Core/ResourceManager/ResourceManager.h"

#include <map>
#include <memory>
#include <iostream>
#include "ResourceManager.h"

static std::map<std::string, std::unique_ptr<Engine::Shader>> s_shaderMap;
static std::map<std::string, std::unique_ptr<Engine::Texture>> s_textureMap;
static std::map<std::string, std::unique_ptr<Engine::Audio>> s_audioMap;

namespace Engine
{
    Texture* ResourceManager::LoadTexture(const char *filePath, const std::string& name)
    {
        if (s_textureMap.find(name) != s_textureMap.end())
        {
            std::cout << "Texture " << filePath << " already loaded" << std::endl;
            return s_textureMap[name].get(); 
        }
        
        std::unique_ptr<Texture> texture = std::make_unique<Texture>(filePath);
        s_textureMap[name] = std::move(texture);
        return s_textureMap[name].get();
    }
    
    Texture *ResourceManager::GetTexture(const std::string& name)
    {
        auto it = s_textureMap.find(name);
        if (it != s_textureMap.end())
        {
            return it->second.get();
        }
        return nullptr;
    }
    
    Shader *ResourceManager::LoadShader(const char *vFilePath, const char *fFilePath, const char *gFilePath, const std::string& name)
    {
        auto it = s_shaderMap.find(name);
        if (it != s_shaderMap.end())
        {
            std::cout << "Shader '" << name << "' already loaded, returning cached\n";
            return it->second.get();
        }

        std::unique_ptr<Shader> shader = std::make_unique<Shader>(vFilePath, fFilePath);
        s_shaderMap[name] = std::move(shader);
        return s_shaderMap[name].get();
    }

    Shader *ResourceManager::GetShader(const std::string& name)
    {
        auto it = s_shaderMap.find(name);
        if (it != s_shaderMap.end())
        {
            return it->second.get();
        }
        return nullptr;
    }

    Audio *ResourceManager::LoadAudio(const char *filePath, const std::string &name)
    {
        std::unique_ptr<Audio> audio = std::make_unique<Audio>(filePath);
        s_audioMap[name] = std::move(audio);
        return s_audioMap[name].get();
    }

    Audio *ResourceManager::GetAudio(const std::string &name)
    {
        auto it = s_audioMap.find(name);
        if (it != s_audioMap.end())
        {
            return it->second.get();
        }
        return nullptr;
    }

    void ResourceManager::clear() {
        s_shaderMap.clear();
        s_textureMap.clear();
        s_audioMap.clear();
    }
}
