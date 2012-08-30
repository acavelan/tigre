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

#include "SharedLibrary.hpp"
#include "Exceptions.hpp"

namespace tigre
{
    namespace core
    {
        SharedLibraryException::SharedLibraryException(const String &filename, const String &message) :
            Exception("Shared Library Exception: " + filename + ". Message: " + message)
        {}

        SharedLibrary::SharedLibrary() :
            _isloaded(false)
        {
        }

        SharedLibrary::SharedLibrary(const String &filename) :
            _filename(filename), _isloaded(false)
        {
            load();
        }

        SharedLibrary::~SharedLibrary()
        {
            try
            {
                if(_isloaded)
                    unload();
            }
            catch(SharedLibraryException &e)
            {
            }
        }

        const String &SharedLibrary::filename() const
        {
            return _filename;
        }

        bool SharedLibrary::isLoaded() const
        {
            return _isloaded;
        }

        void SharedLibrary::load()
        {
            if(_isloaded)
                unload();

            Assert(_filename.empty() == false);

            _lib = DYNLIB_LOAD(String(_filename + "." + SHARED_LIBRARY_EXT).toCString());

            if(!_lib)
                throw SharedLibraryException(_filename, DYNLIB_ERROR());

            _isloaded = true;
        }

        void SharedLibrary::load(const String &filename)
        {
            _filename = filename;

            load();
        }

        void SharedLibrary::unload()
        {
            if(_isloaded)
            {
                if(DYNLIB_UNLOAD(_lib))
                    throw SharedLibraryException(_filename, DYNLIB_ERROR());

                _isloaded = false;
            }
        }

        void *SharedLibrary::resolve(const String &symbol)
        {
            if(!_isloaded)
                load();

            void *sym = DYNLIB_GETSYM(_lib, symbol.toCString());

            if(!sym)
                throw SharedLibraryException(_filename, DYNLIB_ERROR());

            return sym;
        }
    }
}
