#ifndef DESTRINGIFY_HH
#define DESTRINGIFY_HH 1

#include <sstream>
#include <stdexcept>

template <typename T_>
inline T_ destringify(const std::string & s)
{
    T_ t;
    std::istringstream ss(s);
    ss >> t;
    if (! ss.eof() || ss.fail())
        throw std::runtime_error("Could not destringify: '" + s + "'");
    return t;
}

template<>
inline std::string destringify(const std::string & s)
{
    return s;
}

template<>
inline bool destringify(const std::string & s)
{
    if ("true" == s)
        return true;
    else if ("false" == s)
        return false;
    throw std::runtime_error("Could not destringify<bool>: '" + s + "'");
}

#endif
