#ifndef CONTENT_H
#define CONTENT_H

#include "user/core.hpp"
#include "user/graphics.hpp"

using namespace tigre;

class Content : public core::ContentLoader<graphics::Image>
{
	public:
		
		template<class T>
		T* load(const std::string &filename)
		{
			return ContentLoader<T>::load(filename);
		}
		
		template<class T>
		void save(const std::string &filename, const T *resource)
		{
			ContentLoader<T>::save(filename, resource);
		}
};

#endif
