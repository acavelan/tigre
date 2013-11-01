/*
TIGRE (https://gitorious.org/tigre) is made available under the MIT License.

Copyright (c) 2012 - 2013 Aurélien Cavelan (razlock)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <cstdio>

#include "file.hpp"
#include "Exceptions.hpp"

namespace tigre
{
	namespace core
	{
		std::string loadFile(const std::string &filename)
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
		
		std::string getExtension(const std::string &filename)
		{
			std::string extension = "";
			bool find = false;
			
			int size = filename.size();
			for(int i=size-1; i>0 && !find; i--)
			{
				if(filename[i] == '.') find = true;
				else extension = filename[i] + extension;
			}
			
			return extension;
		}
	}
}
