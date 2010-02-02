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

#include "TextureManager.h"

#include "Configuration.h"

TextureManager::TextureManager()
{
	mipMappingMode = 0;
	if (Configuration::getSingleton()->getValueBool("mipmaps"))
	{
		if (glfwExtensionSupported("GL_SGIS_generate_mipmap")) mipMappingMode = 1;
		if (glfwExtensionSupported("GL_EXT_framebuffer_object"))
		{
			if (glGenerateMipmapEXT = (PFNGLGENERATEMIPMAPEXTPROC)glfwGetProcAddress("glGenerateMipmapEXT"))
				mipMappingMode = 2;
		}
	}
}
TextureManager::~TextureManager()
{
	for (map<string,GLuint>::iterator it=dict.begin(); it!=dict.end(); ++it)
	{
		glDeleteTextures(1,&(*it).second);
	}
}
GLuint TextureManager::loadTexture(string filename, bool repeat)
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