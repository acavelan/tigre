#version 130
			
#ifdef GL_ES										
	precision mediump float;						
#endif	
											
in vec3 vnormal;
in vec2 vtexCoord;
in vec4 vcolor;

out vec4 ocolor;	
								
uniform sampler2D texture0;

void main()
{
	ocolor = texture(texture0, vtexCoord) * vcolor;	
}
