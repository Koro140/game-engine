#pragma once

#include <string>

namespace Engine {
    class Texture {
    private:
        int m_Width;
        int m_Height;
        int m_nChannels;
        unsigned int m_Id;
        
    public:
        Texture(const char* fileName);
        void Bind();
        ~Texture();

        void Destroy();
    };
}