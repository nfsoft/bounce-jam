/*
Bounce Jam - Physics-based platform game
Copyright (C) 2010 NewFolder Software

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "global.h"
#include <map>

#include "GLFW/include/glfw.h"
#include <GL/glext.h>

void decodePNGFile(const std::string& filename, std::vector<unsigned char>& out_image_32bit, unsigned long& image_width, unsigned long& image_height);

class TextureManager
{
private:
	map<string,GLuint> dict;
	int mipMappingMode;
	PFNGLGENERATEMIPMAPEXTPROC glGenerateMipmapEXT;
public:
	TextureManager();
	~TextureManager();
	GLuint loadTexture(string filename, bool repeat = false);
	static TextureManager* getSingleton() {static TextureManager instance; return &instance;}
};

#endif