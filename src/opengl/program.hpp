#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "opengl.hpp"
#include "shader.hpp"
#include <cstddef>
#include <string>
#include <vector>

class Program
{
public:
    Program(const std::vector<Shader> shaders)
    {
        m_program = glCreateProgram();

        for (auto shader : shaders)
            glAttachShader(m_program, shader.getHandle());

        glLinkProgram(m_program);

        for (auto shader : shaders)
            glDetachShader(m_program, shader.getHandle());

        GLint is_linked = 0;
        glGetProgramiv(m_program, GL_LINK_STATUS, &is_linked);
        if(is_linked == GL_FALSE) {
            GLint max_length = 0;
            glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<GLchar> error_log(max_length);
            glGetProgramInfoLog(m_program, max_length, &max_length, error_log.data());
            std::string error(error_log.data());

            throw gl_error(error.c_str());
        }
    }
    ~Program()
    {
        glDeleteProgram(m_program);
        m_program=0;
    }
    GLuint getHandle() const
    {
        return m_program;
    }
    void use() const
    {
        glUseProgram(m_program);
    }
    void disuse() const
    {
        glUseProgram(0);
    }
private:
    GLuint m_program = 0;
};

#endif /* PROGRAM_HPP */
