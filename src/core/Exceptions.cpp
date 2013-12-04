#include "Exceptions.hpp"

namespace tigre
{
    namespace core
    {
        Exception::Exception(const std::string &message) :
            _message(message)
        {
        }

        Exception::~Exception() throw() {}

        const char *Exception::what() const throw()
        {
            return _message.c_str();
        }
    }
}

