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
	TextureManager()
	{
		mipMappingMode = 0;
		if (glfwExtensionSupported("GL_SGIS_generate_mipmap")) mipMappingMode = 1;
		if (glfwExtensionSupported("GL_EXT_framebuffer_object"))
		{
			if (glGenerateMipmapEXT = (PFNGLGENERATEMIPMAPEXTPROC)glfwGetProcAddress("glGenerateMipmapEXT"))
				mipMappingMode = 2;
		}
		//mipMappingMode = 0;
	}
	~TextureManager()
	{
		for (map<string,GLuint>::iterator it=dict.begin(); it!=dict.end(); ++it)
		{
			glDeleteTextures(1,&(*it).second);
		}
	}
	GLuint loadTexture(string filename, bool repeat = false)
	{
		map<string,GLuint>::iterator it = dict.find(filename);
		if (it != dict.end())
			return it->second;

		vector<unsigned char> buffer;
		unsigned long w, h;
		decodePNGFile(filename,buffer,w,h);

		if (buffer.size() < 4) ERR_UGLY("error loading " + filename);

		GLuint name;

		glGenTextures(1,&name);
		glBindTexture(GL_TEXTURE_2D, name);
		if (mipMappingMode==1)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_HINT_SGIS, GL_NICEST);
		}
		glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &buffer[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat ? GL_REPEAT : GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat ? GL_REPEAT : GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mipMappingMode ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (mipMappingMode==2) glGenerateMipmapEXT(GL_TEXTURE_2D);
		dict.insert(pair<string,GLuint>(filename,name));

		return name;
	}
	static TextureManager* getSingleton() {static TextureManager instance; return &instance;}
};

#endif