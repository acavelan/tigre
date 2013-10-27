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

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <exception>

#ifndef TIGRE_NO_ASSERT
	#define Assert(condition) if (!(condition)) throw AssertException(__FILE__, __LINE__, #condition)
#else
	inline void doNothing(bool) {}
	#define Assert(condition) doNothing(!(condition))
#endif

namespace tigre
{
    namespace core
    {
        class Exception : public std::exception
        {
            public:

                Exception(const std::string &message = "");

                virtual ~Exception() throw();

                virtual const char *what() const throw();

            private:
				
                std::string _message;
        };
        
        class NotImplementedException : public Exception
        {
			public:
				NotImplementedException(const std::string &message = "") : Exception(message) {}
		};
		
        class LoadingFailed : public Exception
		{
			public:	
				LoadingFailed(const std::string &message = "") : Exception(message) {}
		};
    }
}

#endif
