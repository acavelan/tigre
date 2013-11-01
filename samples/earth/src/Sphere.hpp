#ifndef SPHERE_H
#define SPHERE_H

#include "graphics/Mesh.hpp"

class Sphere : public tigre::graphics::Mesh
{
    public:

        Sphere(float radius, int latitudeBands, int longitudeBands);
		
		float radius;
		
        int latitudeBands, longitudeBands;
};

#endif
