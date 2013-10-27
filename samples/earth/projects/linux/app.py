env = Environment()

target = "app"

tigre = '../../../..'
tigresrc = tigre + '/src'

root = '../..'
rootsrc = root + '/src'

cxxflags = ['-O2', '-W', '-Wall', '-Wextra', '-DGL_GLEXT_PROTOTYPES']
# '-Werror'

sources =  [
	rootsrc + '/linux/main.cpp',
	rootsrc + '/Application.cpp',
	rootsrc + '/SphereMesh.cpp'
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
