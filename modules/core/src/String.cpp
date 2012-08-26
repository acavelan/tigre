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

#include <cstring>
#include <cstdio>

#include "String.hpp"

namespace tigre
{
    namespace core
    {
        String::String() :
            _data()
        {
        }

        String::String(char ch) :
            _data(1, ch)
        {
        }

        String::String(const char *str) :
            _data(str)
        {
        }

        String::String(const String &other) :
            _data(other._data)
        {
        }

        String::~String()
        {
        }

        // Operators
        String String::operator +(Char ch) const
        {
            String str(_data.c_str());
            str._data += ch;
            return str;
        }

        String String::operator +(const Char *unicode) const
        {
            String str(_data.c_str());
            str._data += unicode;
            return str;
        }

        String String::operator +(const String &other) const
        {
            String str(_data.c_str());
            str._data += other._data;
            return str;
        }

        String &String::operator +=(Char ch)
        {
            _data += ch;
            return *this;
        }

        String &String::operator +=(const Char *unicode)
        {
            _data += unicode;
            return *this;
        }

        String &String::operator +=(const String &other)
        {
            _data += other._data;
            return *this;
        }

        bool String::operator >(const Char *other) const
        {
            return strcmp(_data.c_str(), other) > 0;
        }

        bool String::operator >(const String &other) const
        {
            return _data > other._data;
        }

        bool String::operator >=(const Char *other) const
        {
            return strcmp(_data.c_str(), other) >= 0;
        }

        bool String::operator >=(const String &other) const
        {
            return _data >= other._data;
        }

        bool String::operator <(const Char *other) const
        {
            return strcmp(_data.c_str(), other) < 0;
        }

        bool String::operator <(const String &other) const
        {
            return _data < other._data;
        }

        bool String::operator <=(const Char *other) const
        {
            return strcmp(_data.c_str(), other) <= 0;
        }

        bool String::operator <=(const String &other) const
        {
            return _data <= other._data;
        }

        bool String::operator ==(const Char *other) const
        {
            return strcmp(_data.c_str(), other) == 0;
        }

        bool String::operator ==(const String &other) const
        {
            return _data == other._data;
        }

        bool String::operator !=(const Char *other) const
        {
            return strcmp(_data.c_str(), other) != 0;
        }

        bool String::operator !=(const String &other) const
        {
            return _data != other._data;
        }

        char String::operator [](int pos) const
        {
            return _data[pos];
        }

        char &String::operator [](int pos)
        {
            return _data[pos];
        }

        // Setters
        void String::clear()
        {
            _data.clear();
        }

        // Getters
        const Char *String::unicode() const
        {
            return _data.c_str();
        }

        bool String::empty() const
        {
            return _data.empty();
        }

        int String::size() const
        {
            return _data.size();
        }

        // Converters
        const char *String::toCString() const
        {
            return _data.c_str();
        }

        short String::toShort(bool *ok, int base) const
        {
            char* end = 0;
            const char *str = _data.c_str();
            short number = strtol(str, &end, base);
            if(str == end && ok)
                *ok = false;
            return number;
        }

        unsigned short String::toUShort(bool *ok, int base) const
        {
            char* end = 0;
            const char *str = _data.c_str();
            unsigned short number = strtoul(str, &end, base);
            if(str == end && ok)
                *ok = false;
            return number;
        }

        int String::toInt(bool *ok, int base) const
        {
            char* end = 0;
            const char *str = _data.c_str();
            int number = strtol(str, &end, base);
            if(str == end && ok)
                *ok = false;
            return number;
        }

        unsigned int String::toUInt(bool *ok, int base) const
        {
            char* end = 0;
            const char *str = _data.c_str();
            unsigned int number = strtoul(str, &end, base);
            if(str == end && ok)
                *ok = false;
            return number;
        }

        long String::toLong(bool *ok, int base) const
        {
            char* end = 0;
            const char *str = _data.c_str();
            long number = strtol(str, &end, base);
            if(str == end && ok)
                *ok = false;
            return number;
        }

        unsigned long String::toULong(bool *ok, int base) const
        {
            char* end = 0;
            const char *str = _data.c_str();
            unsigned long number = strtoul(str, &end, base);
            if(str == end && ok)
                *ok = false;
            return number;
        }

        float String::toFloat(bool *ok) const
        {
            char* end = 0;
            const char *str = _data.c_str();
            float number = strtof(str, &end);
            if(str == end && ok)
                *ok = false;
            return number;
        }

        double String::toDouble(bool *ok) const
        {
            char* end = 0;
            const char *str = _data.c_str();
            double number = strtod(str, &end);
            if(str == end && ok)
                *ok = false;
            return number;
        }

        // Static initializers
        String String::number(float n, int precision)
        {
            Char str[32];
            sprintf(str, "%.*f", precision, n);
            return String(str);
        }

        String String::number(double n, int precision)
        {
            Char str[32];
            sprintf(str, "%.*f", precision, n);
            return String(str);
        }

        // Friend related members
        std::ostream &operator <<(std::ostream &os, const String &str)
        {
            os << str._data;
            return os;
        }

        std::istream &operator >>(std::istream &is, String &str)
        {
            is >> str._data;
            return is;
        }

        String operator +(char ch, const String &str)
        {
            String result(ch);
            result._data += str._data;
            return result;
        }

        String operator +(const Char *unicode, const String &str)
        {
            String result(unicode);
            result._data += str._data;
            return result;
        }
    }
}
