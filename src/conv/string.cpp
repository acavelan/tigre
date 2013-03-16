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

#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>

#include "string.hpp"

namespace tigre
{
	namespace conv
	{
		short toShort(const std::string &str, bool *ok, int base)
		{
			char* end = 0;
			short number = strtol(str.c_str(), &end, base);
			if(str == end && ok)
				*ok = false;
			return number;
		}

		unsigned short toUShort(const std::string &str, bool *ok, int base)
		{
			char* end = 0;
			unsigned short number = strtoul(str.c_str(), &end, base);
			if(str == end && ok)
				*ok = false;
			return number;
		}

		int toInt(const std::string &str, bool *ok, int base)
		{
			char* end = 0;
			int number = strtol(str.c_str(), &end, base);
			if(str == end && ok)
				*ok = false;
			return number;
		}

		unsigned int toUInt(const std::string &str, bool *ok, int base)
		{
			char* end = 0;
			unsigned int number = strtoul(str.c_str(), &end, base);
			if(str == end && ok)
				*ok = false;
			return number;
		}

		long toLong(const std::string &str, bool *ok, int base)
		{
			char* end = 0;
			long number = strtol(str.c_str(), &end, base);
			if(str == end && ok)
				*ok = false;
			return number;
		}

		unsigned long toULong(const std::string &str, bool *ok, int base)
		{
			char* end = 0;
			unsigned long number = strtoul(str.c_str(), &end, base);
			if(str == end && ok)
				*ok = false;
			return number;
		}

		float toFloat(const std::string &str, bool *ok)
		{
			char* end = 0;
			float number = strtof(str.c_str(), &end);
			if(str == end && ok)
				*ok = false;
			return number;
		}

		double toDouble(const std::string &str, bool *ok)
		{
			char* end = 0;
			double number = strtod(str.c_str(), &end);
			if(str == end && ok)
				*ok = false;
			return number;
		}
		
		std::string toString(int n, int base)
		{
			static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";

			char str[32];
			char *ptr = str;
			int sign;
			div_t res;

			// Validate base
			if(base < 2 || base > 35)
				return "";

			// Take care of sign
			if((sign = n) < 0)
				n = -n;

			// Conversion. Number is reversed.
			do
			{
				res = div(n, base);
				*ptr++ = num[res.rem];
			}
			while((n = res.quot));

			// Add sign
			if(sign < 0)
				*ptr++ = '-';

			*ptr = '\0';

			char aux;
			char *begin = str, *end = ptr-1;

			while(end>begin)
				aux=*end, *end--=*begin, *begin++=aux;

			return str;
		}

		std::string toString(float n, int precision)
		{
			char str[32];
			sprintf(str, "%.*f", precision, n);
			return std::string(str);
		}

		std::string toString(double n, int precision)
		{
			char str[32];
			sprintf(str, "%.*f", precision, n);
			return std::string(str);
		}
	}
}
