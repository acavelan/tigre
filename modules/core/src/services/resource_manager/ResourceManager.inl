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
inline typename ResourceManager<T>::iterator ResourceManager<T>::begin()
{
    return _resources.begin();
}

template <class T>
inline typename ResourceManager<T>::iterator ResourceManager<T>::end()
{
    return _resources.end();
}

template <class T>
inline ResourceManager<T>::ResourceManager(Logger &logger) :
    _logger(logger)
{
}

template <class T>
inline ResourceManager<T>::~ResourceManager()
{
    if(_resources.size() > 0)
    {
        _logger(log::WARNING) << "ResourceManager > Deleting remaining resources ..." << log::endl;

        for(iterator it = begin(); it != end(); ++it)
            _logger(log::WARNING) << "ResourceManager > " << it->first << " (x" << it->second->refCount() << ")" << log::endl;

        clear();

        _logger(log::WARNING) << "ResourceManager > Done" << log::endl;
    }
}

template <class T>
inline T *ResourceManager<T>::get(const String &name) const
{
    const_iterator it = _resources.find(name);

    if(it != _resources.end())
    {
        it->second->grab();
        return it->second;
    }

    return 0;
}

template <class T>
inline T *ResourceManager<T>::add(T *resource)
{
    Assert(resource != 0);

    const_iterator it = _resources.find(resource->name());

    if(it == _resources.end())
    {
        resource->onDelete += slot(this, &ResourceManager::onDelete);
        _resources[resource->name()] = resource;
    }

    return resource;
}

template <class T>
inline void ResourceManager<T>::remove(const String &name)
{
    iterator it = _resources.find(name);

    if(it != _resources.end())
        _resources.erase(it);
}

template <class T>
inline void ResourceManager<T>::clear()
{
    for(iterator it = begin(); it != end(); ++it)
        delete it->second;

    _resources.clear();
}

template <class T>
inline void ResourceManager<T>::onDelete(Resource *resource)
{
    remove(resource->name());
}
