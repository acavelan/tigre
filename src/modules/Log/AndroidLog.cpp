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

#include <android/log.h>

#include "Log.hpp"

#define APP_NAME "TIGRE"

void Log::info(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	__android_log_vprint(ANDROID_LOG_INFO, APP_NAME, fmt, args);
	va_end(args);
}

void Log::warning(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	__android_log_vprint(ANDROID_LOG_WARN, APP_NAME, fmt, args);
	va_end(args);
}

void Log::error(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	__android_log_vprint(ANDROID_LOG_ERROR, APP_NAME, fmt, args);
	va_end(args);
}

