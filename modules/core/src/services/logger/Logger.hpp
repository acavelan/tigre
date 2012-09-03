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

#ifndef LOGGER_H
#define LOGGER_H

#include <map>
#include <sstream>

#include "config.h"
#include "String.hpp"
#include "Plugin.hpp"
#include "Service.hpp"
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

                LogStream(const Plugin<ILogWriter> &writer, const String &channel, const log::log_level_t &verbosity) :
                    writer(writer), _channel(channel), _log_level(log::EVERYTHING), _verbosity(verbosity)
                {
                    writer->setChannel(channel);
                }

                LogStream &operator [](log::log_level_t log_level)
                {
                    Assert(log_level >= log::NOTHING && log_level < log::EVERYTHING);

                    _log_level = log_level;

                    return *this;
                }

                template <class T>
                LogStream &operator <<(const T &toLog)
                {
                    if(_log_level <= _verbosity)
                        _stream << toLog;

                    return *this;
                }

                LogStream &operator<<(LogStream &(*manipulator)(LogStream&))
                {
                    return manipulator(*this);
                }

                void flush()
                {
                    writer->write(_stream.str().c_str());
                    _stream.str("");
                }

            private:

                String _channel;
                log::log_level_t _log_level;
                const log::log_level_t &_verbosity;
                std::ostringstream _stream;
        };

        namespace log
        {
            LogStream &endl(LogStream &stream)
            {
                stream << "\n";
                stream.flush();
                return stream;
            }
        }

        class Logger : public Service<Logger>
        {
            public:

                Plugin<ILogWriter> writer;

                log::log_level_t verbosity;

                Logger() :
                    verbosity(log::EVERYTHING)
                {
                }

                ~Logger()
                {
                    for(iterator it = _streams.begin(); it != _streams.end(); ++it)
                        delete it->second;

                    _streams.clear();
                }

                LogStream &operator [](const String &stream)
                {
                    iterator it = _streams.find(stream);

                    LogStream *logstream = 0;

                    if(it == _streams.end())
                    {
                        logstream = new LogStream(writer, stream, verbosity);
                        _streams[stream] = logstream;
                    }
                    else
                        logstream = it->second;

                    return *logstream;
                }

                LogStream &operator [](log::log_level_t log_level)
                {
                    return (*this)["out"][log_level];
                }

                template <class T>
                LogStream &operator <<(const T &toLog)
                {
                    return (*this)["out"] << toLog;
                }

                LogStream &operator<<(LogStream &(*manipulator)(LogStream&))
                {
                    return manipulator((*this)["out"]);
                }

            private:

                typedef std::map<String, LogStream*>::iterator iterator;
                typedef std::map<String, LogStream*>::const_iterator const_iterator;

                std::map<String, LogStream*> _streams;
        };

        #include "Logger.inl"
    }
}

#endif // LOGGER_H
