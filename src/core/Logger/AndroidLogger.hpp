#ifndef ANDROIDLOGGER_H
#define ANDROIDLOGGER_H

#include <string>

#include "../Logger.hpp"

namespace tigre
{
    namespace core
    {
        class AndroidLogger : public Logger
        {
            public:

                AndroidLogger(const std::string &tag);

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
