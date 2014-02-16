env = Environment()

target = "glfw"

tigre = '../../../..'
tigresrc = tigre + '/src'

root = '../..'
rootsrc = root + '/src'

cxxflags = ['-O2', '-Wall', '-Wextra', '-DGL_GLEXT_PROTOTYPES']

sources =  [
	rootsrc + '/launchers/glfw/main.cpp',
	rootsrc + '/Earth.cpp'
]

cpppath = [
	tigre + '/local', 
	tigresrc, 
	rootsrc
]

libs = ['tigre', 'glfw']
libpath = ['.']

env.Append(CXXFLAGS = cxxflags)
env.Append(LIBS = libs)
env.Append(LIBPATH = libpath)
env.Append(CPPPATH = cpppath)

env.Program(target, sources)
