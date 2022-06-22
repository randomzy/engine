#ifndef SHADER_HPP
#define SHADER_HPP

#include <vector>
#include "opengl.hpp"

class Shader
{
public:
    Shader(const char * source, GLenum shader_type)
    {
        m_shader = glCreateShader(shader_type);
        glShaderSource(m_shader, 1, &source, NULL);
        glCompileShader(m_shader);

        GLint is_compiled = 0;
        glGetShaderiv(m_shader, GL_COMPILE_STATUS, &is_compiled);
    
        if(is_compiled == GL_FALSE)
        {
            GLint max_length = 0;
            glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<GLchar> error_log(max_length);
            glGetShaderInfoLog(m_shader, max_length, &max_length, error_log.data());
            std::string error(error_log.data());
            
            glDeleteShader(m_shader);
            m_shader = 0;

            throw gl_error(error.c_str());
        }
    }
    ~Shader()
    {
        glDeleteShader(m_shader);
        m_shader=0;
    }
    GLuint getHandle() const
    {
        return m_shader;
    }
private:
    GLuint m_shader;
};

#endif /* SHADER_HPP */
