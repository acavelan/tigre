#version 130					

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec3 vnormal;
out vec2 vtexCoord;
out vec4 vcolor;

uniform mat4 projection;										
uniform mat4 model;												
uniform mat4 view;												
uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);

void main()
{
	vnormal = normal;
	vtexCoord = texCoord;
	vcolor = color;												
	gl_Position = projection * view * model * vec4(position, 1.0);
}
