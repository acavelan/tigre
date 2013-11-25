#version 100	

in vec3 position;
in vec3 normal;
in vec2 texCoord;

varying vec3 vnormal;
varying vec2 vtexCoord;
varying vec4 vcolor;

uniform mat4 projection;										
uniform mat4 model;												
uniform mat4 view;												
uniform vec4 color;

void main()
{
	vnormal = normal;
	vtexCoord = texCoord;
	vcolor = color;												
	gl_Position = projection * view * model * vec4(position, 1.0);
}
