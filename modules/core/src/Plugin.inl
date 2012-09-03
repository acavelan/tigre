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

template<class T>
inline Plugin<T>::Plugin() :
    _ptr(0), _lib(new SharedLibrary())
{
}

template<class T>
inline Plugin<T>::Plugin(const Plugin &other) :
    _ptr(0), _filename(other._filename), _lib(other._lib)
{
    load();
}


template<class T>
inline Plugin<T>::Plugin(const String &filename) :
    _lib(new SharedLibrary(filename)), _filename(filename)
{
    _lib->load();
}

template<class T>
inline  Plugin<T>::~Plugin()
{
    if(_ptr)
        delete _ptr;
}

template<class T>
inline const String &Plugin<T>::name() const
{
    return _filename;
}

template<class T>
inline void Plugin<T>::load()
{
    if(_ptr)
    {
        delete _ptr;
        _ptr = 0;
    }

    _lib->load(_filename);

    typedef T *(*init_f)();

    init_f init = (init_f)_lib->resolve("init_plugin");

    _ptr = init();
}

template<class T>
inline void Plugin<T>::load(const String &filename)
{
    _filename = filename;

    load();
}

template<class T>
inline const Plugin<T> &Plugin<T>::operator =(const Plugin &other)
{
    _filename = other._filename;
    _lib = other._lib;

    load();

    return *this;
}

template<class T>
inline const Plugin<T> &Plugin<T>::operator =(const String &filename)
{
    load(filename);

    return *this;
}

template <class T>
inline T *Plugin<T>::ptr() const
{
    return _ptr;
}

template<class T>
inline T &Plugin<T>::operator *() const
{
    return *_ptr;
}

template<class T>
T *Plugin<T>::operator ->() const
{
    return _ptr;
}

template<class T>
inline Plugin<T>::operator T*() const
{
    return _ptr;
}
