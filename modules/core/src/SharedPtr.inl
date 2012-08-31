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

template <class T>
inline SharedPtr<T>::SharedPtr() :
    _data(0), _counter(0)
{
}

template <class T>
inline SharedPtr<T>::SharedPtr(const SharedPtr<T> &copy) :
    _data(copy._data), _counter(copy._counter)
{
    if(_counter)
        ++(*_counter);
}

template <class T>
inline SharedPtr<T>::SharedPtr(T *pointer) :
    _data(pointer), _counter(0)
{
    if(_data)
        _counter = new int(1);
}

template <class T>
inline SharedPtr<T>::~SharedPtr()
{
    if(_data && _counter && --(*_counter) == 0)
    {
        delete _data;
        delete _counter;
    }
}

template <class T>
inline void SharedPtr<T>::clear()
{
    if(_data && _counter && --(*_counter) == 0)
    {
        delete _data;
        delete _counter;
        _data = 0;
        _counter = 0;
    }
}

template <class T>
inline int SharedPtr<T>::count() const
{
    if(_counter)
        return *_counter;
    else
        return 0;
}

template <class T>
inline void SharedPtr<T>::swap(SharedPtr<T> &ptr)
{
    std::swap(_data, ptr._data);
    std::swap(_counter, ptr._counter);
}

template <class T>
inline T *SharedPtr<T>::ptr() const
{
    return _data;
}

template <class T>
inline T &SharedPtr<T>::operator  *() const
{
    Assert(_data != 0);
    return *_data;
}

template <class T>
inline T *SharedPtr<T>::operator ->() const
{
    Assert(_data != 0);
    return _data;
}

template <class T>
inline SharedPtr<T>::operator    T*() const
{
    return _data;
}

template <class T>
inline const SharedPtr<T> &SharedPtr<T>::operator =(const SharedPtr<T> &pointer)
{
    SharedPtr<T>(pointer).swap(*this);
    return *this;
}

template <class T>
inline const SharedPtr<T> &SharedPtr<T>::operator =(T *ptr)
{
    if(_data != ptr)
        SharedPtr<T>(ptr).swap(*this);
    return *this;
}
