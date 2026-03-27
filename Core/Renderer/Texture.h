#pragma once

#include <string>

namespace Engine {
    class Texture {
    private:
        unsigned int m_Id;
        
    public:
        int m_Width;
        int m_Height;
        int m_nChannels;
        
        Texture(const char* fileName);
        void Bind();
        ~Texture();

        void Destroy();
    };
}