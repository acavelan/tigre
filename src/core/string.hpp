#ifndef CORE_STRING_H
#define CORE_STRING_H

#include <string>
#include <vector>

namespace tigre
{
    namespace core
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

        std::string cut(const std::string &str, const std::string &delim, int occurrence);

        std::string getPrefix(const std::string &str, const std::string &delim);

        std::string getSuffix(const std::string &str, const std::string &delim);

        bool startsWith(const std::string &s1, const std::string &s2);
    }
}

#endif
