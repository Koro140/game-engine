#pragma once

#include <string>

namespace Engine {

    enum Shader_Type {
        SHADER_TYPE_VERTEX,
        SHADER_TYPE_FRAGMENT,
    };

    class Shader {
        private:
            std::string m_VertexSource;
            std::string m_FragmentSource;
            
            unsigned int m_Id;

            std::string readFile(const char* fileName);
        public:
            Shader(const char* shaderVertexSrc, const char* shaderFragmentSrc);
            ~Shader();
            void destroy();
            void use();

            void setBool(const std::string &name, bool value) const;
            void setInt(const std::string &name, int value) const;
            void setFloat(const std::string &name, float value) const;
    };
}