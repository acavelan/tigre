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

#ifndef SHAREDLIBRARY_H
#define SHAREDLIBRARY_H

#include <map>

#include "config.h"
#include "String.hpp"
#include "Exceptions.hpp"

#if defined(_WIN32) || defined(__WIN32__)
    #include <windows.h>
    #define DYNLIB_HANDLE           HMODULE
    #define DYNLIB_LOAD( a )        LoadLibrary( a )
    #define DYNLIB_GETSYM( a, b )   GetProcAddress( a, b )
    #define DYNLIB_UNLOAD( a )      !FreeLibrary( a )
    #define DYNLIB_ERROR( )         "Unknown Error"
    #define SHARED_LIBRARY_EXT      "dll"
#elif defined(__linux__) || defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__) || defined(__FreeBSD__)
    #include <dlfcn.h>
    #define DYNLIB_HANDLE           void*
    #define DYNLIB_LOAD( a )        dlopen( a, RTLD_LAZY )
    #define DYNLIB_GETSYM( a, b )   dlsym( a, b )
    #define DYNLIB_UNLOAD( a )      dlclose( a )
    #define DYNLIB_ERROR( )         dlerror( )
    #define SHARED_LIBRARY_EXT      "so"
#endif

namespace tigre
{
    namespace core
    {
        class SHARED SharedLibraryException : public Exception
        {
            public:

                SharedLibraryException(const String &filename, const String &message);
        };

        class SHARED SharedLibrary
        {
            public:

                SharedLibrary();
                SharedLibrary(const String &filename);
                ~SharedLibrary();

                const String &filename() const;

                bool isLoaded() const;

                void load();
                void load(const String &filename);
                void unload();

                void *resolve(const String &symbol);

                const SharedLibrary &operator=(const SharedLibrary &other);

            private:

                String _filename;
                bool _isloaded;
                DYNLIB_HANDLE _lib;
        };
    }
}

#endif // SHAREDLIBRARY_H
