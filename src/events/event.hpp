#ifndef EVENT_HPP
#define EVENT_HPP

#include "opengl.hpp"
#include <functional>
#include <iostream>

class Event
{
public:
    virtual ~Event() = default;
    bool handled = false;
    virtual std::string toString() const {return std::string();}
};

#endif /* EVENT_HPP */
