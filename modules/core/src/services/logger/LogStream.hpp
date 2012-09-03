/*
--------------------------------------------------------------------------------
This source file is part of TIGRE.

TIGRE is made available under the MIT License.

Refer to https://github.com/razlock/tigre for more informations.

Copyright (c) 2012 Aurélien Cavelan (razlock)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
--------------------------------------------------------------------------------
*/

#ifndef LOGSTREAM_H
#define LOGSTREAM_H

#include <sstream>

#include "config.h"
#include "String.hpp"
#include "Plugin.hpp"
#include "ILogWriter.hpp"

namespace tigre
{
    namespace core
    {
        namespace log
        {
            enum log_level_t
            {
                NOTHING = 0,
                CRITICAL,
                ERROR,
                WARNING,
                INFO,
                DEBUG,
                EVERYTHING
            };
        }

        class LogStream
        {
            public:

                Plugin<ILogWriter> writer;

                LogStream(const Plugin<ILogWriter> &writer, const String &channel, const log::log_level_t &verbosity);
                ~LogStream();

                LogStream &operator [](log::log_level_t log_level);

                template <class T>
                LogStream &operator <<(const T &toLog);

                LogStream &operator<<(LogStream &(*manipulator)(LogStream&));

                void flush();

            private:

                String _channel;
                log::log_level_t _log_level;
                const log::log_level_t &_verbosity;
                std::ostringstream _stream;
        };

        namespace log
        {
            LogStream &endl(LogStream &stream);
        }

        #include "LogStream.inl"
    }
}

#endif // LOGSTREAM_H
