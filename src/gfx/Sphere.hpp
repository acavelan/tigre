#ifndef SPHERE_H
#define SPHERE_H

#include "../gfx/Mesh.hpp"

namespace tigre
{
    namespace gfx
    {
        class Sphere : public tigre::gfx::Mesh
        {
            public:

                Sphere(float radius, int latitudeBands, int longitudeBands);
        };
    }
}

#endif
