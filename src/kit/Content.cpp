#include "Content.hpp"

namespace tigre
{
	namespace kit
	{
		Content::Content(graphics::Renderer *renderer) : _renderer(renderer)
		{
			registerLoader(new graphics::ImageLoader(), "jpg,bmp,png");
		}

		template<>
		graphics::Texture2D* Content::load<graphics::Texture2D>(const std::string &filename)
		{
			graphics::Image *image = ContentManager<graphics::Image>::load(filename);
			graphics::Texture2D *texture = _renderer->createTexture2D(image);
			ContentManager<graphics::Image>::unload(image);
			return texture;
		}

		template<>
		void Content::unload<graphics::Texture2D>(graphics::Texture2D *texture)
		{
			_renderer->destroy(texture);
		}
	}
}
