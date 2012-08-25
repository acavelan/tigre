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

// Static initializers
template<typename T>
String String::number(T n, int base)
{
    static Char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";

    Char str[32];
    Char *ptr = str;
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

    Char aux;
    Char *begin = str, *end = ptr-1;

    while(end>begin)
        aux=*end, *end--=*begin, *begin++=aux;

    return String(str);
}
