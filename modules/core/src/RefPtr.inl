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
inline RefPtr<T>::RefPtr() :
    _data(0)
{
}

template <class T>
inline RefPtr<T>::RefPtr(const RefPtr<T> &copy) :
    _data(copy._data)
{
    _data->grab();
}

template <class T>
inline RefPtr<T>::RefPtr(T *pointer) :
    _data(pointer)
{
}

template <class T>
inline RefPtr<T>::~RefPtr()
{
    if(_data)
        _data->release();
}

template <class T>
inline void RefPtr<T>::clear()
{
    if(_data)
    {
        _data->release();
        _data = 0;
    }
}

template <class T>
inline int RefPtr<T>::count() const
{
    if(_data)
        return _data->refCount();
    else
        return 0;
}

template <class T>
inline void RefPtr<T>::swap(RefPtr<T> &ptr)
{
    std::swap(_data, ptr._data);
}

template <class T>
inline T *RefPtr<T>::ptr() const
{
    return _data;
}

template <class T>
inline T &RefPtr<T>::operator  *() const
{
    Assert(_data != 0);
    return *_data;
}

template <class T>
inline T *RefPtr<T>::operator ->() const
{
    Assert(_data != 0);
    return _data;
}

template <class T>
inline RefPtr<T>::operator    T*() const
{
    return _data;
}

template <class T>
inline const RefPtr<T> &RefPtr<T>::operator =(const RefPtr<T> &pointer)
{
    RefPtr<T>(pointer).swap(*this);
    return *this;
}

template <class T>
inline const RefPtr<T> &RefPtr<T>::operator =(T *ptr)
{
    if(_data != ptr)
        RefPtr<T>(ptr).swap(*this);
    return *this;
}
