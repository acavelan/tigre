#include <android/log.h>

#include "AndroidLogger.hpp"

namespace tigre
{
    namespace core
    {
        AndroidLogger::AndroidLogger(const std::string &tag) :
            _tag(tag)
        {
        }

        void AndroidLogger::setTag(const std::string &tag)
        {
            _tag = tag;
        }

        void AndroidLogger::info(const char *fmt, ...) const
        {
            va_list args;
            va_start(args, fmt);
            __android_log_vprint(ANDROID_LOG_INFO, _tag.c_str(), fmt, args);
            va_end(args);
        }

        void AndroidLogger::warning(const char *fmt, ...) const
        {
            va_list args;
            va_start(args, fmt);
            __android_log_vprint(ANDROID_LOG_WARN, _tag.c_str(), fmt, args);
            va_end(args);
        }

        void AndroidLogger::error(const char *fmt, ...) const
        {
            va_list args;
            va_start(args, fmt);
            __android_log_vprint(ANDROID_LOG_ERROR, _tag.c_str(), fmt, args);
            va_end(args);
        }
    }
}

