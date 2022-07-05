#include "window.hpp"
#include <atomic>
#include <stdexcept>
#include "keyEvents.hpp"
#include "mouseEvents.hpp"

static int window_count = 0;

void glfwErrorCallback(int error_code, const char * description)
{
    throw std::runtime_error("[GLFW] Erorr " + std::to_string(error_code) + ": " + description);
}

Window::Window(int width, int height, std::string const &name, EventCallback event_callback)
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

    // set event callback
    m_windowProps.eventCallback = event_callback;
    glfwSetWindowUserPointer(m_window, &m_windowProps);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow * window, int width, int height){
        WindowProps & windowProps = *(WindowProps*)(glfwGetWindowUserPointer(window));
        if (windowProps.eventCallback) {
            windowProps.eventCallback(Event());
        }
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow * window, double xpos, double ypos){
        WindowProps & windowProps = *(WindowProps*)(glfwGetWindowUserPointer(window));
        if (windowProps.eventCallback) {
            windowProps.eventCallback(MouseMovedEvent(xpos, ypos));
        }
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow * window, int button, int action, int mods){
        WindowProps & windowProps = *(WindowProps*)(glfwGetWindowUserPointer(window));
        if (windowProps.eventCallback) {
            switch (action) {
                case GLFW_PRESS:
                {
                    windowProps.eventCallback(MouseButtonPressed(button, mods));
                    break;
                }
                case GLFW_RELEASE:
                {
                    windowProps.eventCallback(MouseButtonReleased(button, mods));
                    break;
                }
            }
        }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow * window, double xoffset, double yoffset){
        WindowProps & windowProps = *(WindowProps*)(glfwGetWindowUserPointer(window));
        if (windowProps.eventCallback) {
            windowProps.eventCallback(MouseScrolledEvent(xoffset, yoffset));
        }
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow * window, int key, int scancode, int action, int mods){
        WindowProps & windowProps = *(WindowProps*)(glfwGetWindowUserPointer(window));
        if (windowProps.eventCallback) {
            switch (action) {
                case GLFW_PRESS:
                {
                    windowProps.eventCallback(KeyPressedEvent(key, mods, false));
                    break;
                }
                case GLFW_RELEASE:
                {
                    windowProps.eventCallback(KeyReleasedEvent(key, mods));
                    break;
                }
                case GLFW_REPEAT:
                {
                    windowProps.eventCallback(KeyPressedEvent(key, mods, true));
                    break;
                }
            }
        }
    });

    glfwSetCharCallback(m_window, [](GLFWwindow * window, unsigned int codepoint){
        WindowProps & windowProps = *(WindowProps*)(glfwGetWindowUserPointer(window));
        if (windowProps.eventCallback) {
            windowProps.eventCallback(KeyTypedEvent(codepoint));
        }
    });

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

void Window::setEventCallback(EventCallback eventCallback)
{
    m_windowProps.eventCallback = eventCallback;
}