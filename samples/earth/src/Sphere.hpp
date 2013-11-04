#ifndef SPHERE_H
#define SPHERE_H

#include "gfx/Mesh.hpp"

class Sphere : public tigre::gfx::Mesh
{
    public:

        Sphere(float radius, int latitudeBands, int longitudeBands);
		
		float radius;
		
        int latitudeBands, longitudeBands;
};

#endif
