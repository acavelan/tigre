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

#ifndef CONV_STRING_H
#define CONV_STRING_H

#include <string>
#include <vector>

namespace tigre
{
	namespace conv
	{	
		short toShort(const std::string &str, bool *ok = 0, int base = 10);
		unsigned short toUShort(const std::string &str, bool *ok = 0, int base = 10);

		int toInt(const std::string &str, bool *ok = 0, int base = 10);
		unsigned int toUInt(const std::string &str, bool *ok = 0, int base = 10);

		long toLong(const std::string &str, bool *ok = 0, int base = 10);
		unsigned long toULong(const std::string &str, bool *ok = 0, int base = 10);

		float toFloat(const std::string &str, bool *ok = 0);
		double toDouble(const std::string &str, bool *ok = 0);

		std::string toString(int n, int base = 10);
		std::string toString(float n, int precision = 6);
		std::string toString(double n, int precision = 6);
		
		std::string toLower(const std::string &str);
		std::string toUpper(const std::string &str);
		
		void split(const std::string &str, std::vector<std::string> &tokens, const std::string &delim);
	}
}

#endif
