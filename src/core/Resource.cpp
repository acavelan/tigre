#include "Resource.hpp"

namespace tigre
{
    namespace core
    {
        Resource::Resource() : _refCount(1)
        {
        }

        Resource::~Resource()
        {
        }

        void Resource::grab()
        {
            _refCount++;
        }

        void Resource::release()
        {
            _refCount--;
        }

        int Resource::getRefCount() const
        {
            return _refCount;
        }

        void grab(Resource *resource)
        {
            resource->grab();
        }

        void release(Resource *resource)
        {
            resource->release();

            if(resource->getRefCount() <= 0)
                delete resource;
        }
    }
}
