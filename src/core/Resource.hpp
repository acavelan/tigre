#ifndef RESOURCE_H
#define RESOURCE_H

namespace tigre
{
    namespace core
    {
        class Resource
        {
            public:

                Resource();
                virtual ~Resource();

                void grab();

                void release();

                int getRefCount() const;

            private:

                int _refCount;
        };

        void grab(Resource *resource);

        void release(Resource *resource);
    }
}

#endif
