#include <cstdio>
#include <cstdarg>

#include "ConsoleLogger.hpp"

namespace tigre
{
    namespace core
    {
        ConsoleLogger::ConsoleLogger(const std::string &tag) :
            _tag(tag)
        {
        }

        void ConsoleLogger::setTag(const std::string &tag)
        {
            _tag = tag;
        }

        void ConsoleLogger::info(const char *fmt, ...) const
        {
            va_list args;
            va_start(args, fmt);
            printf("%s::", _tag.c_str());
            vprintf(fmt, args);
            va_end(args);
        }

        void ConsoleLogger::warning(const char *fmt, ...) const
        {
            va_list args;
            va_start(args, fmt);
            printf("%s::", _tag.c_str());
            vprintf(fmt, args);
            va_end(args);
        }

        void ConsoleLogger::error(const char *fmt, ...) const
        {
            va_list args;
            va_start(args, fmt);
            printf("%s::", _tag.c_str());
            vprintf(fmt, args);
            va_end(args);
        }
    }
}

