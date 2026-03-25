#include "Shader.h"

#include <glad/glad.h>

#include <iostream>
#include <filesystem>
#include <fstream>

namespace Engine {
    std::string Shader::readFile(const char* fileName)
    {
        std::string line("",1024);
        std::ifstream file(fileName);
        std::string result;

        if (!file) {
            std::cerr << "Couldn't open shader file " <<  fileName << std::endl;
        }
        else {
            while (getline(file, line)) {
                result.append(line + "\n");
            
            }
            result[result.size() - 1] = '\0';
            file.close();
        }
        
        return result;
    }

    Shader::Shader(const char* shaderVertexSrc, const char* shaderFragmentSrc)
    {
        unsigned int vertex = 0;
        unsigned int fragment= 0;
        
        int success = 0;
        char infoLog[512] = {0};
        
        std::string m_VertexSource = readFile(shaderVertexSrc);
        std::string m_FragmentSource = readFile(shaderFragmentSrc);

        const char* vVertexSrc = m_VertexSource.c_str();
        const char* vFragmentSrc = m_FragmentSource.c_str();

        // VERTEX
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vVertexSrc, NULL);
        glCompileShader(vertex);
        
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        // FRAGMENT
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &vFragmentSrc, NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        // PROGRAM && LINKING
        m_Id = glCreateProgram();
        glAttachShader(m_Id, vertex);
        glAttachShader(m_Id, fragment);
        glLinkProgram(m_Id);
        
        glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(m_Id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }


    Shader::~Shader()
    {
        destroy();
    }

    void Shader::destroy()
    {
        if (m_Id != 0)
        {
            glDeleteProgram(m_Id);
            m_Id = 0;
        }
    }

    void Shader::use() { 
        glUseProgram(m_Id);
    }

    void Shader::setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(m_Id, name.c_str()), (int)value); 
    }
    void Shader::setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(m_Id, name.c_str()), value); 
    }
    void Shader::setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(m_Id, name.c_str()), value); 
    } 
}
