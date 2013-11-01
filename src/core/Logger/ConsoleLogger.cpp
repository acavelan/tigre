/*
TIGRE (https://gitorious.org/tigre) is made available under the MIT License.

Copyright (c) 2012 - 2013 Aurélien Cavelan (razlock)

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
*/

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
