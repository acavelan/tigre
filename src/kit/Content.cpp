#include <cstdio>

#include "Content.hpp"
#include "../core/Exceptions.hpp"
#include "../graphics/ImageLoader.hpp"

namespace tigre
{
	namespace kit
	{	
		Content::Content(graphics::Renderer *renderer) : _renderer(renderer)
		{
			registerLoader(new graphics::ImageLoader(), "jpg,bmp,png");
		}
		
		std::string Content::loadFile(const std::string &filename)
		{
			std::string source;
			
			FILE *fp = fopen(filename.c_str(), "rb");
			
			if(fp)
			{
				fseek(fp, 0, SEEK_END);
				long fsize = ftell(fp);
				fseek(fp, 0, SEEK_SET);
				
				source.resize(fsize + 1);
				fread(&source[0], fsize, 1, fp);
				source[fsize] = 0;
				
				fclose(fp);
			}
			else
				throw core::LoadingFailed("Couldn't load " + filename + ": file not found\n");
			
			return source;
		}
		
		// Texture specialization
		template<>
		graphics::Texture2D* Content::load<graphics::Texture2D>(const std::string &filename)
		{
			graphics::Image *image = ContentManager<graphics::Image>::load(filename);
			graphics::Texture2D *texture = _renderer->createTexture2D(image);
			ContentManager<graphics::Image>::unload(image);
			return texture;
		}
	}
}
