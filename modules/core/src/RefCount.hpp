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

#ifndef REFCOUNT_H
#define REFCOUNT_H

#include "config.h"

namespace tigre
{
    namespace core
    {
        template <class T>
        class RefCount
        {
            public :

                RefCount() :
                    _ref_counter(new int(1))
                {
                }

                T *clone(T *ptr)
                {
                    ++*_ref_counter;
                    return ptr;
                }

                void release(T *ptr)
                {
                    if(--*_ref_counter == 0)
                    {
                        delete _ref_counter;
                        delete ptr;
                    }
                }

                void swap(RefCount &other)
                {
                    std::swap(other._ref_counter, _ref_counter);
                }

            private :

                int *_ref_counter;
        };
    }
}

#endif // REFCOUNT_H