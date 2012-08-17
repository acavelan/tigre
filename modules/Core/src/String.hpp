/*
--------------------------------------------------------------------------------
This source file is part of TIGRE.

TIGRE (https://gitorious.org/tigre) is made available under the MIT License.

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

#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstdlib>
#include <string>

#include "export.h"

namespace tigre
{
    namespace core
    {
        typedef char Char;

        class SHARED String
        {
            public:

                String();
                String(Char ch);
                String(const Char *unicode);
                String(const String &other);

                ~String();

                // Operators
                String operator+(Char ch) const;
                String operator+(const Char *unicode) const;
                String operator+(const String &other) const;

                String &operator+=(Char ch);
                String &operator+=(const Char *unicode);
                String &operator+=(const String &other);

                bool operator> (const Char *other) const;
                bool operator> (const String &other) const;

                bool operator>=(const Char *other) const;
                bool operator>=(const String &other) const;

                bool operator< (const Char *other) const;
                bool operator< (const String &other) const;

                bool operator<=(const Char *other) const;
                bool operator<=(const String &other) const;

                bool operator==(const Char *other) const;
                bool operator==(const String &other) const;

                bool operator!=(const Char *other) const;
                bool operator!=(const String &other) const;

                Char  operator[](int pos) const;
                Char &operator[](int pos);

                // Getter
                const Char *unicode() const;
                int size() const;

                // Converters
                const char *toCString() const;

                short toShort(bool *ok = 0, int base = 10) const;
                unsigned short toUShort(bool *ok = 0, int base = 10) const;

                int toInt(bool *ok = 0, int base = 10) const;
                unsigned int toUInt(bool *ok = 0, int base = 10) const;

                long toLong(bool *ok = 0, int base = 10) const;
                unsigned long toULong(bool *ok = 0, int base = 10) const;

                float toFloat(bool *ok = 0) const;
                double toDouble(bool *ok = 0) const;

                // Static initializers
                template<typename T>
                static String number(T n, int base = 10);

                static String number(float n, int precision = 6);
                static String number(double n, int precision = 6);

                // Friend related operators
                friend std::ostream &operator<<(std::ostream &os, const String &str);
                friend std::istream &operator>>(std::istream &is, String &str);

                friend String operator+(Char ch, const String &str);
                friend String operator+(const Char *unicode, const String &str);

            private:

                std::string data;
        };

        #include "String.inl"
    }
}

#endif // STRING_H
