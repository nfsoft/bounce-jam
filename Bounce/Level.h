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

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "global.h"

#include "GLFW/include/glfw.h"
#include "Box2D/include/Box2D.h"

#include "Drawable.h"
#include "Actor.h"

class Level
{
private:
	vector<Drawable*> drawables;
	Actor* actor;
	b2World* world;
	string filename;
	GLuint groundTexture;
public:
	Level(b2World* world);
	Actor* loadLevel(string filename);
	Actor* restart();
	void draw();
	void clear();
	~Level();
};

#endif