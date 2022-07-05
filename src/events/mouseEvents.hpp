#ifndef MOUSEEVENTS_HPP
#define MOUSEEVENTS_HPP

#include "event.hpp"

class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(float x, float y)
        : m_x(x), m_y(y) {}
    float getX() const {return m_x;}
    float getY() const {return m_y;}

    std::string toString() const override
    {
        return "MouseMovedEvent: " + std::to_string(m_x) + ", " + std::to_string(m_y);
    }
private:
    float m_x, m_y;
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(float xoffset, float yoffset)
        : m_xoffset(xoffset), m_yoffset(yoffset) {}
    float getXOffset() const {return m_xoffset;}
    float getYOffset() const {return m_yoffset;}

    std::string toString() const override
    {
        return "MouseScrolledEvent: " + std::to_string(m_xoffset) + ", " + std::to_string(m_yoffset);
    }
private:
    float m_xoffset, m_yoffset;
};

class MouseButtonEvent : public Event
{
public:
    // returns GLFW code for mouse button
    int getButton() const {return m_button;}
    int getMods() const {return m_mods;}
protected:
    MouseButtonEvent(int button, int mods)
        : m_button(button)
        , m_mods(mods) {}
private:
    int m_button;
    int m_mods;
};

class MouseButtonPressed : public MouseButtonEvent
{
public:
    MouseButtonPressed(int button, int mods)
        : MouseButtonEvent(button, mods) {}

    std::string toString() const override
    {
        return "MouseButtonPressed: " + std::to_string(getButton()) + ", " + std::to_string(getMods());
    }
};

class MouseButtonReleased : public MouseButtonEvent
{
public:
    MouseButtonReleased(int button, int mods)
        : MouseButtonEvent(button, mods) {}

    std::string toString() const override
    {
        return "MouseButtonReleased: " + std::to_string(getButton()) + ", " + std::to_string(getMods());
    }
};

#endif /* MOUSEEVENTS_HPP */
