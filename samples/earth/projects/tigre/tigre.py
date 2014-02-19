import os, platform

env = Environment()

target = "tigre"

root = '../../../..'
src = root + '/src'

sources = [
	src + '/core/file.cpp',
	src + '/core/string.cpp',
	src + '/core/Resource.cpp',
	src + '/core/Exceptions.cpp',
	src + '/core/Timer.cpp',
	src + '/gfx/Mesh.cpp',
	src + '/gfx/ModelMesh.cpp',
	src + '/gfx/Shader.cpp',
	src + '/gfx/Color.cpp',
	src + '/gfx/Image.cpp',
	src + '/gfx/Texture2D.cpp',
	src + '/gfx/ImageLoader.cpp',
	src + '/gfx/Rectangle.cpp',
	src + '/gfx/Sphere.cpp',
	src + '/hl/Content.cpp',
	src + '/hl/RenderView.cpp'
]

cpppath = [
	src,
	root + '/local',
	root + '/local/soil/src'
]

cxxflags = ['-O2', '-fPIC', '-W', '-Wall', '-Wextra', '-DGL_GLEXT_PROTOTYPES']
# '-Werror'

libs = []
libpath = []

if platform.system() == "Linux":
	print "Compiling for : ", platform.system()
	
	sources.append([
		src + '/core/Logger/ConsoleLogger.cpp',
		src + '/gfx/Display/GLFWDisplay.cpp',
		src + '/gfx/Context/OpenGLContext.cpp',
		src + '/gfx/Renderer/OpenGLRenderer.cpp'
	])
	
	SOIL = env.File('libSOIL.a')
	
	libs.append(['GL', 'glfw', SOIL])

env.Append(CXXFLAGS = cxxflags)
env.Append(LIBS = libs)
env.Append(LIBPATH = libpath)
env.Append(CPPPATH = cpppath)

env.SharedLibrary(target, sources)
