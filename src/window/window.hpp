#ifndef WINDOW_H
#define WINDOW_H

#include "opengl.hpp"
#include "context.hpp"
#include <memory>
#include "event.hpp"

using EventCallback = std::function<void(Event &&)>;

class Window
{
public:
    Window(int width, int height, std::string const &name, EventCallback event_callback = EventCallback());
    ~Window();

    void update();
    bool shouldClose() const;
    void setEventCallback(EventCallback);
private:
    GLFWwindow * m_window;
    std::unique_ptr<Context> m_context;
    
    // user pointer is cast to this struct in event callbacks instead of this
    struct WindowProps {
        EventCallback eventCallback;
    };

    WindowProps m_windowProps;

};

#endif /* WINDOW_H */
