#ifndef CREATABLE_H
#define CREATABLE_H

#include <memory>

// TODO: remove this and add functions instead
template<typename T>
class Creatable
{
public:
    template<typename ...Args>
    static std::shared_ptr<T> create(Args &&... args){return std::make_shared<T>(std::forward<Args>(args)...);};
};

#endif /* CREATABLE_H */
