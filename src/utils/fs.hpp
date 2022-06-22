#ifndef FS_HPP
#define FS_HPP

#include <string>
#include <fstream>
#include <sstream>

inline std::string load_file(const std::string & fname)
{
    std::ifstream t(fname);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

#endif