#ifndef WINDOW_H
#define WINDOW_H

#include "opengl.hpp"
#include "context.hpp"
#include <memory>

class Window
{
public:
    Window(int width, int height, std::string const &name);
    ~Window();
    
    void update();
    bool shouldClose() const;
private:
    GLFWwindow * m_window;
    std::unique_ptr<Context> m_context;
};

#endif /* WINDOW_H */
