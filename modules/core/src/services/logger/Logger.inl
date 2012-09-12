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

Logger::Logger(const String &name) :
    verbosity(log::EVERYTHING), _name(name), _log_level(log::EVERYTHING)
{
}

Logger::~Logger()
{
    flush();
}

Logger &Logger::operator ()(log::LogLevel log_level)
{
    _log_level = log_level;

    return *this;
}

template <class T>
Logger &Logger::operator <<(const T &toLog)
{
    _stream << toLog;

    return *this;
}

Logger &Logger::operator <<(Logger &(*manipulator)(Logger&))
{
    return manipulator(*this);
}

void Logger::flush()
{
    Assert(writer != 0);

    writer->write(_name, _stream.str().c_str());

    _stream.str("");

    _log_level = log::EVERYTHING;
}

namespace log
{
    Logger &endl(Logger &stream)
    {
        stream << "\n";
        stream.flush();

        return stream;
    }
}
