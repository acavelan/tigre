#version 100
			
#ifdef GL_ES										
	precision mediump float;						
#endif	
											
varying vec3 vnormal;
varying vec2 vtexCoord;
varying vec4 vcolor;
								
uniform sampler2D texture0;

void main()
{
	gl_FragColor = texture2D(texture0, vtexCoord) * vcolor;	
}
