#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <exception>

#ifndef TIGRE_NO_ASSERT
#define Assert(condition) if (!(condition)) throw AssertException(__FILE__, __LINE__, #condition)
#else
inline void doNothing(bool) {}
#define Assert(condition) doNothing(!(condition))
#endif

namespace tigre
{
    namespace core
    {
        class Exception : public std::exception
        {
            public:

                Exception(const std::string &message = "");

                virtual ~Exception() throw();

                virtual const char *what() const throw();

            private:

                std::string _message;
        };

        class NotImplementedException : public Exception
        {
            public:
                NotImplementedException(const std::string &message = "") : Exception(message) {}
        };

        class LoadingFailed : public Exception
        {
            public:
                LoadingFailed(const std::string &message = "") : Exception(message) {}
        };
    }
}

#endif
