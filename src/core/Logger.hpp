#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>

namespace tigre
{
    namespace core
    {
        class Logger
        {
            public:

                virtual void info(const char *fmt, ...) const = 0;

                virtual void warning(const char *fmt, ...) const = 0;

                virtual void error(const char *fmt, ...) const = 0;

        };
    }
}

#endif
