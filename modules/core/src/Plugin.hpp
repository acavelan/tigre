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

#ifndef PLUGIN_H
#define PLUGIN_H

#include "config.h"
#include "String.hpp"
#include "SharedPtr.hpp"
#include "SharedLibrary.hpp"

namespace tigre
{
    namespace core
    {
        template<class T>
        class Plugin
        {
            public:

                Plugin();
                Plugin(const String &filename);

                virtual ~Plugin();

                const String &name() const;

                void load();
                void load(const String &filename);

                const Plugin &operator =(const String &filename);

                T &operator  *() const;
                T *operator ->() const;
                operator    T*() const;

            private:

                Plugin(const Plugin &);
                const Plugin &operator =(const Plugin &);

                SharedLibrary _plugin;
                SharedPtr<T> _ptr;
                String _filename;

        };

        #include "Plugin.inl"

        #define EXPORT_PLUGIN(T) \
            extern "C" DYNLIB_EXPORT T *init_plugin() \
            { \
                return new T(); \
            }
    }
}

#endif // PLUGIN_H