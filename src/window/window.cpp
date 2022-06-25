#include "window.hpp"
#include <atomic>
#include <stdexcept>

static int window_count = 0;

void glfwErrorCallback(int error_code, const char * description)
{
    throw std::runtime_error("[GLFW] Erorr " + std::to_string(error_code) + ": " + description);
}

Window::Window(int width, int height, std::string const &name)
{
    if (window_count == 0) {
        if (GLFW_FALSE == glfwInit()) {
            throw std::runtime_error("[GLFW] Error: Could not initialize GLFW");
        }
        glfwSetErrorCallback(glfwErrorCallback);

        // the first version with compute shaders
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    }

    m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

    window_count++;

    m_context = std::make_unique<Context>(m_window);
};

Window::~Window()
{   
    glfwDestroyWindow(m_window);

    window_count--;

    if (window_count == 0) {
        glfwTerminate();
    }
}

void Window::update()
{
    m_context->swapBuffers();

    glfwPollEvents();
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}