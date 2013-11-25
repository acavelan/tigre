#version 100	

attribute vec3 position;
//attribute vec3 normal;
attribute vec2 texCoord;

//varying vec3 vnormal;
varying vec2 vtexCoord;
varying vec4 vcolor;

uniform mat4 projection;										
uniform mat4 model;												
uniform mat4 view;												
uniform vec4 color;

void main()
{
	//vnormal = normal;
	vtexCoord = texCoord;
	vcolor = color;												
	gl_Position = projection * view * model * vec4(position, 1.0);
}
