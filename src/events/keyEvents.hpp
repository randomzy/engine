#ifndef KEYEVENTS_HPP
#define KEYEVENTS_HPP

#include "event.hpp"

class KeyEvent : public Event
{
public:
    int getKey() const {return m_key;}
    int getMods() const {return m_mods;}
protected:
    KeyEvent(int key, int mods)
        : m_key(key), m_mods(mods) {}
private:
    int m_key;
    int m_mods;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(int key, int mods, bool repeat = false)
        : KeyEvent(key, mods), m_repeat(repeat) {}
    std::string toString() const override
    {
        return "KeyPressedEvent: " + std::to_string(getKey()) + ", " + std::to_string(getMods()) + ", " + std::to_string(m_repeat);
    }
private:
    bool m_repeat;
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(int key, int mods)
        : KeyEvent(key, mods) {}
    std::string toString() const override
    {
        return "KeyReleasedEvent: " + std::to_string(getKey()) + ", " + std::to_string(getMods());
    }
};

class KeyTypedEvent : public Event
{
public:
    KeyTypedEvent(unsigned int code)
        : m_code(code) {}
    unsigned int getCode() const {return m_code;}
    std::string toString() const override
    {
        return "KeyTypedEvent: " + std::to_string(getCode());
    }
private:
    unsigned int m_code;
};

#endif /* KEYEVENTS_HPP */
