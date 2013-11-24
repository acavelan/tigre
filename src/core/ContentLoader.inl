template<class T>
ContentLoader<T>::~ContentLoader()
{
	unregisterLoaders();
}

template<class T>
T* ContentLoader<T>::loadFromFile(const std::string &filename)
{
	Loader<T> *loader = findLoader(filename);
	T *resource = loader->loadFromFile(filename);
	return resource;
}

template<class T>
void ContentLoader<T>::saveToFile(const std::string &filename, const T *resource)
{
	Loader<T> *loader = findLoader(filename);
	loader->saveToFile(filename, resource);
}

template<class T>
void ContentLoader<T>::registerLoader(Loader<T> *loader, const std::string &extensions)
{
	std::vector<std::string> extList;
	split(extensions, extList, " /\\*.,;|-_\t\n'\"");

	std::vector<std::string>::iterator it, end = extList.end();
	for(it = extList.begin(); it != end; ++it)
		_loaderMap[toLower(*it)] = loader;
	
	_loaderList.push_back(loader);
}

template<class T>
void ContentLoader<T>::unregisterLoaders()
{
	typename LoaderList::iterator it, end = _loaderList.end();
	for(it = _loaderList.begin(); it != end; it++)
	{
		delete *it;
	}
	_loaderList.clear();
}

template<class T>
Loader<T>* ContentLoader<T>::findLoader(const std::string &filename)
{
	std::string extension = toLower(getSuffix(filename, "."));
	
	typename LoaderMap::iterator it = _loaderMap.find(extension);

	if(it != _loaderMap.end())
		return it->second;
	
	it = _loaderMap.find("*");
	
	bool any = (it != _loaderMap.end());
	
	if(any)
		return it->second;
	else
		throw LoadingFailed("No loaders for this extension: " + extension + "\n");
}
