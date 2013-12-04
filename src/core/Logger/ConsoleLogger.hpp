#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include <string>

#include "../Logger.hpp"

namespace tigre
{
    namespace core
    {
        class ConsoleLogger : public Logger
        {
            public:

                ConsoleLogger(const std::string &tag);

                void setTag(const std::string &tag);

                void info(const char *fmt, ...) const;

                void warning(const char *fmt, ...) const;

                void error(const char *fmt, ...) const;

            private:

                std::string _tag;
        };
    }
}

#endif
