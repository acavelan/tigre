#ifndef SPHEREMESH_H
#define SPHEREMESH_H

#include "graphics/Mesh.hpp"

class SphereMesh : public tigre::graphics::Mesh
{
    public:

        SphereMesh(float radius, int latitudeBands, int longitudeBands);
        
        ~SphereMesh();
		
		float radius;
		
        int latitudeBands, longitudeBands;
};

#endif
