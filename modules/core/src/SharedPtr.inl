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

template <class T, template <class> class Ownership>
inline SharedPtr<T, Ownership>::SharedPtr() :
    _data(0)
{
}

template <class T, template <class> class Ownership>
inline SharedPtr<T, Ownership>::SharedPtr(const SharedPtr<T, Ownership> &copy) :
    Ownership<T>(copy), _data(Ownership<T>::clone(copy._data))
{
}

template <class T, template <class> class Ownership>
inline SharedPtr<T, Ownership>::SharedPtr(T *pointer) :
    _data(pointer)
{
}

template <class T, template <class> class Ownership>
inline SharedPtr<T, Ownership>::~SharedPtr()
{
    Ownership<T>::release(_data);
}

template <class T, template <class> class Ownership>
inline void SharedPtr<T, Ownership>::swap(SharedPtr<T, Ownership> &ptr)
{
    Ownership<T>::swap(ptr);
    std::swap(_data, ptr._data);
}

template <class T, template <class> class Ownership>
inline T *SharedPtr<T, Ownership>::ptr() const
{
    return _data;
}

template <class T, template <class> class Ownership>
inline T &SharedPtr<T, Ownership>::operator  *() const
{
    Assert(_data != 0);
    return *_data;
}

template <class T, template <class> class Ownership>
inline T *SharedPtr<T, Ownership>::operator ->() const
{
    Assert(_data != 0);
    return _data;
}

template <class T, template <class> class Ownership>
inline SharedPtr<T, Ownership>::operator    T*() const
{
    return _data;
}

template <class T, template <class> class Ownership>
inline const SharedPtr<T, Ownership> &SharedPtr<T, Ownership>::operator =(const SharedPtr<T, Ownership> &pointer)
{
    SharedPtr<T, Ownership>(pointer).swap(*this);
    return *this;
}

template <class T, template <class> class Ownership>
inline const SharedPtr<T, Ownership> &SharedPtr<T, Ownership>::operator =(T *ptr)
{
    if(_data != ptr)
        SharedPtr<T, Ownership>(ptr).swap(*this);

    return *this;
}
