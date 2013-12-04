#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>

#include "string.hpp"

namespace tigre
{
    namespace core
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

        std::string toLower(const std::string &str)
        {
            std::string lower(str.size(), ' ');

            std::transform(str.begin(), str.end(), lower.begin(), static_cast<int (*)(int)>(std::tolower));

            return lower;
        }

        std::string toUpper(const std::string &str)
        {
            std::string upper(str.size(), ' ');

            std::transform(str.begin(), str.end(), upper.begin(), static_cast<int (*)(int)>(std::toupper));

            return upper;
        }

        void split(const std::string &str, std::vector<std::string> &tokens, const std::string &delim)
        {
            tokens.clear();

            for(std::string::size_type p1 = 0, p2 = 0; p1 != std::string::npos;)
            {
                p1 = str.find_first_not_of(delim, p1);
                if(p1 != std::string::npos)
                {
                    p2 = str.find_first_of(delim , p1);
                    tokens.push_back(str.substr(p1, p2 - p1));
                    p1 = p2;
                }
            }
        }

        std::string cut(const std::string &str, const std::string &delim, int occurrence)
        {
            std::vector<std::string> tokens;

            split(str, tokens, delim);

            if(tokens.size() > 0 && occurrence == -1)
            {
                return tokens[tokens.size() - 1];
            }
            else if(tokens.size() > (unsigned int)occurrence)
            {
                return tokens[occurrence];
            }
            else
                return "";
        }

        std::string getPrefix(const std::string &str, const std::string &delim)
        {
            return cut(str, delim, 0);
        }

        std::string getSuffix(const std::string &str, const std::string &delim)
        {
            return cut(str, delim, -1);
        }

        bool startsWith(const std::string &s1, const std::string &s2)
        {
            return !s1.compare(0, s2.size(), s2);
        }
    }
}
