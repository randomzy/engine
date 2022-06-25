#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "opengl.hpp"
#include <string>
#include <iostream>

// handle errors
inline void GLAPIENTRY
glMessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    if (type == GL_DEBUG_TYPE_ERROR) {
        throw gl_error(message);
    }
}

class Context
{
public:
    Context(GLFWwindow * window)
        : m_window(window)
    {
        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw gl_error("Could not load glad");
        }

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(glMessageCallback, 0);

        std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    }

    void swapBuffers()
    {
        glfwSwapBuffers(m_window);
    }
private:
    GLFWwindow * m_window;
};

#endif /* CONTEXT_HPP */
