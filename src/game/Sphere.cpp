/*
TIGRE (https://gitorious.org/tigre) is made available under the MIT License.

Copyright (c) 2012 - 2013 Aurélien Cavelan (razlock)

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
*/

#include <cmath>

#include "Sphere.hpp"

namespace tigre
{
	namespace game
	{
		Sphere::Sphere(float radius, int latitudeBands, int longitudeBands)
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
	}
}