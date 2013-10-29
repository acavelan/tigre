#ifndef SHADERS_H
#define SHADERS_H

static const char vertexShader[] =
	"#version 130																\n"
    "in vec3 position;                                                 		    \n"
    "in vec3 normal;                                                   		    \n"
    "in vec2 texCoord;                                                          \n"
    "out vec3 vnormal;                                                          \n"
    "out vec2 vtexCoord;                                                        \n"
    "out vec4 vcolor;                                                           \n"
    "uniform mat4 projection;													\n"
    "uniform mat4 model;														\n"
    "uniform mat4 view;															\n"
    "uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);                             \n"
    "void main()                                                                \n"
    "{                                                                          \n"
    "   vnormal = normal;                                                       \n"
    "   vtexCoord = texCoord;                                                   \n"
    "	vcolor = color;															\n"
    "   gl_Position = projection * view * model * vec4(position, 1.0);     		\n"
    "}                                                                          \n";

static const char fragmentShader[] =
	"#version 130																\n"
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
    
#endif
