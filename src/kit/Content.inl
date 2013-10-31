template<class T>
T* Content::load(const std::string &filename)
{
	return ContentManager<T>::load(filename);
}

template<class T>
void Content::save(const std::string &filename, const T *resource)
{
	ContentManager<T>::save(filename, resource);
}

template<class T>
inline void Content::registerLoader(core::Loader<T> *loader, const std::string &extensions)
{
	ContentManager<T>::registerLoader(loader, extensions);
}

