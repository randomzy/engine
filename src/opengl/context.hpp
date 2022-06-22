#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "opengl.hpp"
#include <string>

// handle errors
inline void GLAPIENTRY
MessageCallback( GLenum source,
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
    Context(int width, int height, std::string const & windowName)
    {
        if (GLFW_FALSE == glfwInit()) {
            throw gl_error("Could not initialize GLFW");
        }

        /* Create a windowed mode window and its OpenGL context */
        m_window = glfwCreateWindow(640, 480, windowName.c_str(), NULL, NULL);
        if (!m_window) {
            glfwTerminate();
            throw gl_error("Could not initialize window");
        }

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw gl_error("Could not load glad");
        }
    }
    ~Context()
    {
        glfwTerminate();
    }

    void swapBuffers()
    {
        glfwSwapBuffers(m_window);
    }
private:
    GLFWwindow * m_window;
};

#endif /* CONTEXT_HPP */
