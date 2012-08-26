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

#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include "Exceptions.hpp"

namespace tigre
{
    namespace core
    {
        template<class T>
        class SharedPtr
        {
            public:

                SharedPtr();
                SharedPtr(const SharedPtr &copy);
                SharedPtr(T *pointer);
                ~SharedPtr();

                void release();
                int count() const;

                T *ptr() const;

                T &operator  *() const;
                T *operator ->() const;
                operator    T*() const;

                const SharedPtr &operator =(const SharedPtr &pointer);

                const SharedPtr &operator =(T *ptr);

            private :

                void swap(SharedPtr &ptr);

                T *_data;
                int *_counter;
        };

        #include "SharedPtr.inl"
    }
}

#endif // SHAREDPTR_H
