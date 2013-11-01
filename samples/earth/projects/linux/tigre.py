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
	src + '/graphics/Mesh.cpp',
	src + '/graphics/ModelMesh.cpp',
	src + '/graphics/Shader.cpp',
	src + '/graphics/Color.cpp',
	src + '/graphics/Image.cpp',
	src + '/graphics/Texture2D.cpp',
	src + '/graphics/ImageLoader.cpp',
	src + '/graphics/Rectangle.cpp'
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
		src + '/graphics/Display/GLFWDisplay.cpp',
		src + '/graphics/Context/OpenGLContext.cpp',
		src + '/graphics/Renderer/OpenGLRenderer.cpp'
	])
	
	SOIL = env.File(root + '/local/soil/lib/libSOIL.a')
	
	libs.append(['GL', 'glfw', SOIL])

env.Append(CXXFLAGS = cxxflags)
env.Append(LIBS = libs)
env.Append(LIBPATH = libpath)
env.Append(CPPPATH = cpppath)

env.SharedLibrary(target, sources)
