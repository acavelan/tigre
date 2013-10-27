#include <cmath>
#include "SphereMesh.hpp"

#include <cstdio>

SphereMesh::SphereMesh(float radius, int latitudeBands, int longitudeBands) :
    radius(radius), latitudeBands(latitudeBands), longitudeBands(longitudeBands)
{
    vertexCount = (latitudeBands + 1) * (longitudeBands + 1) * 3;
    normalCount = (latitudeBands + 1) * (longitudeBands + 1) * 3;
    texCoordCount = (latitudeBands + 1) * (longitudeBands + 1) * 2;
    indexCount = (latitudeBands) * (longitudeBands) * 6;

    vertices = new float[vertexCount];
    normals = new float[normalCount];
    texCoords = new float[texCoordCount];
    indices = new unsigned int[indexCount];

    unsigned int vc = 0, nc = 0, tc = 0, ic = 0;
    for(int latNumber = 0; latNumber <= latitudeBands; latNumber++)
    {
        float theta = latNumber * M_PI / latitudeBands;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        for(int longNumber = 0; longNumber <= longitudeBands; longNumber++)
        {
            float phi = longNumber * 2 * M_PI / longitudeBands;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;
            float u = 1 - ((float)longNumber / longitudeBands);
            float v = (float)latNumber / latitudeBands;

            vertices[vc++] = radius * x;
            vertices[vc++] = radius * y;
            vertices[vc++] = radius * z;
            normals[nc++] = x;
            normals[nc++] = y;
            normals[nc++] = z;
            texCoords[tc++] = u;
            texCoords[tc++] = v;
        }
    }

    for(int latNumber = 0; latNumber < latitudeBands; latNumber++)
    {
        for(int longNumber = 0; longNumber < longitudeBands; longNumber++)
        {
            unsigned int first = (latNumber * (longitudeBands + 1)) + longNumber;
            unsigned int second = first + longitudeBands + 1;

            indices[ic++] = first;
            indices[ic++] = second;
            indices[ic++] = first + 1;

            indices[ic++] = second;
            indices[ic++] = second + 1;
            indices[ic++] = first + 1;
        }
    }
}

SphereMesh::~SphereMesh()
{
}
