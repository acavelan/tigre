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

#include "os.hpp"
#include "file.hpp"
#include "Exceptions.hpp"

#if defined(OS_ANDROID)
	#include "../core/string.hpp"
	#include "../os/android/activity.hpp"
#endif

namespace tigre
{
	namespace core
	{
		void loadFile(const std::string &filename, std::string &buffer)
		{
			#if defined(OS_ANDROID)
				std::string asset_direcorty = "file:///android_asset/";
				
				if(core::startsWith(filename, asset_direcorty))
				{
					std::string asset_path = filename.substr(asset_direcorty.size());
					AAssetManager* assetManager = os::android::getAssetManager();
					AAsset* asset = AAssetManager_open(assetManager, (const char *)asset_path.c_str(), AASSET_MODE_UNKNOWN);
					
					if(asset == NULL)
						throw core::LoadingFailed(asset_path + ": lol file not found\n");
					
					long size = AAsset_getLength(asset);
					
					buffer.resize(size);
					
					AAsset_read(asset, &buffer[0], size);
			
					AAsset_close(asset);
					
					return;
				}
			#endif
			
			FILE *fp = fopen(filename.c_str(), "rb");
			
			if(fp)
			{
				fseek(fp, 0, SEEK_END);
				long fsize = ftell(fp);
				fseek(fp, 0, SEEK_SET);
				
				buffer.resize(fsize + 1);
				fread(&buffer[0], fsize, 1, fp);
				buffer[fsize] = 0;
				
				fclose(fp);
			}
			else
				throw core::LoadingFailed(filename + ": file not found\n");
		}
	}
}
