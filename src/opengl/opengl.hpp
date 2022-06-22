#ifndef OPENGL_HPP
#define OPENGL_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <exception>
#include <string>

class gl_error : public std::exception
{
public:
    gl_error(std::string && msg = std::string())
        : m_msg("[GL ERROR] " + msg) {}

    const char * what() const throw()
    {
        return m_msg.c_str();
    }
private:
    std::string m_msg;
};

#endif /* OPENGL_HPP */
