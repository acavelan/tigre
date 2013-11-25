#version 100
			
#ifdef GL_ES										
	precision mediump float;						
#endif	
											
in vec3 vnormal;
in vec2 vtexCoord;
in vec4 vcolor;
								
uniform sampler2D texture0;

void main()
{
	gl_FragColor = texture2D(texture0, vtexCoord) * vcolor;	
}
