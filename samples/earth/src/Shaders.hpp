#ifndef SHADERS_H
#define SHADERS_H

static const char vertexShader[] =
	"#version 150																\n"
    "in vec3 position;                                                 		    \n"
    "in vec3 normal;                                                   		    \n"
    "in vec2 texCoord;                                                          \n"
    "out vec3 vnormal;                                                          \n"
    "out vec2 vtexCoord;                                                        \n"
    "out vec4 vcolor;                                                           \n"
    "uniform mat4 projMat;                                            			\n"
    "uniform mat4 viewMat;                                                   	\n"
    "uniform mat4 modelMat;                                                  	\n"
    "uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);                             \n"
    "void main()                                                                \n"
    "{                                                                          \n"
    "   vnormal = normal;                                                       \n"
    "   vtexCoord = texCoord;                                                   \n"
    "	vcolor = color;															\n"
    "   gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0);     	\n"
    "}                                                                          \n";

static const char fragmentShader[] =
	"#version 150																\n"
	"#ifdef GL_ES																\n"
	"	precision mediump float;												\n"
	"#endif																		\n"
	"in vec3 vnormal;                                                       	\n"
    "in vec2 vtexCoord;                                                     	\n"
    "in vec4 vcolor;                                                     	    \n"
    "out vec4 ocolor;															\n"
    "uniform sampler2D texture0;                                                \n"
    "void main()                                                                \n"
    "{                                                                          \n"
    "   ocolor = texture(texture0, vtexCoord) * vcolor;							\n"
    "}                                                                          \n";
   
static const char noTextureVertexShader[] =
	"#version 150																\n"
    "in vec3 position;                                                 		    \n"
    "in vec3 normal;                                                   		    \n"
    "out vec3 vnormal;                                                          \n"
    "out vec4 vcolor;                                                           \n"
    "uniform mat4 projMat;                                            			\n"
    "uniform mat4 viewMat;                                                   	\n"
    "uniform mat4 modelMat;                                                  	\n"
    "uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);                             \n"
    "void main()                                                                \n"
    "{                                                                          \n"
    "   vnormal = normal;                                                       \n"
    "	vcolor = color;															\n"
    "   gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0);     	\n"
    "}                                                                          \n";

static const char noTextureFragmentShader[] =
	"#version 150																\n"
	"#ifdef GL_ES																\n"
	"	precision mediump float;												\n"
	"#endif																		\n"
	"in vec3 vnormal;                                                       	\n"
    "in vec2 vtexCoord;                                                     	\n"
    "in vec4 vcolor;                                                     	    \n"
    "out vec4 ocolor;															\n"
    "void main()                                                                \n"
    "{                                                                          \n"
    "   ocolor = vcolor;														\n"
    "}                                                        					\n";
    
#endif
