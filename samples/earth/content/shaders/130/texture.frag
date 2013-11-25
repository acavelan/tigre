#version 130
												
in vec3 vnormal;
in vec2 vtexCoord;
in vec4 vcolor;

out vec4 ocolor;	
								
uniform sampler2D texture0;

void main()
{
	ocolor = texture(texture0, vtexCoord) * vcolor;	
}
