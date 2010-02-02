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

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "global.h"

#include "GLFW/include/glfw.h"
#include "Box2D/include/Box2D.h"

#include "Drawable.h"

#define OBJECT_GENERIC	0
#define OBJECT_ACTOR	1

class Object: public Drawable
{
protected:
	float rotation;
	float position[2];
	float size[2];
	GLuint texture;
	b2World* world;
	b2Body* body;
public:
	virtual int getObjectType() {return OBJECT_GENERIC;}
	Object(float posx, float posy, float rot);
	void loadAndPlace(b2World* world, string filename);
	void draw();
	void setTransform(float posx, float posy, float rot);
	b2Body* getBody();
	virtual ~Object();
};

#endif