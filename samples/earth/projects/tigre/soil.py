env = Environment()

target = "SOIL"

tigre = '../../../..'
soilsrc = tigre + '/local/soil/src/'

cxxflags = ['-O2', '-s', '-fPIC']

sources =  [
	soilsrc + 'image_helper.c',
  	soilsrc + 'stb_image_aug.c',
  	soilsrc + 'image_DXT.c',
  	soilsrc + 'SOIL.c'
]

env.Append(CFLAGS = cxxflags)

env.StaticLibrary(target, sources)