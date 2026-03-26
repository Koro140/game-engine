#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
            
            void setVec2(const std::string &name, const glm::vec2 &value) const;

            void setVec3(const std::string &name, const glm::vec3 &value) const;
            void setVec3(const std::string &name, float x, float y, float z) const;

            void setVec4(const std::string &name, float x, float y, float z, float w) const;
            void setVec4(const std::string &name, const glm::vec4 &value) const;
            
            void setMat3(const std::string &name, const glm::mat3 &mat) const;
            void setMat4(const std::string &name, const glm::mat4 &mat) const;
    };
}