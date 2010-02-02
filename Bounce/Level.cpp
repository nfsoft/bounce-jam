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

#include "Level.h"

#include <fstream>

#include "b2Polygon.h"

#include "Object.h"
#include "Static.h"
#include "TextureManager.h"

Level::Level(b2World *world)
{
	this->world=world;
	actor=0;

	groundTexture = TextureManager::getSingleton()->loadTexture("ground01.png", true);
}

Actor* Level::loadLevel(string filename)
{
	this->filename = filename;
	clear();

	ifstream in;
	in.open(filename.c_str());

	string what;
	in >> what;
	
	if (what != "actor") ERR_UGLY("actor expected");
	float actx, acty;
	in >> actx >> acty;
	actor = new Actor(actx,acty,0);
	actor->loadAndPlace(world, "actor01.obj");
	drawables.push_back(actor);
	
	in >> what;
	if (what != "static") ERR_UGLY("static expected");

	in >> what;
	while (what == "body")
	{
		Static* body = new Static(world, groundTexture);

		//Here will be some definition loading for this body (restitution,friction,..)

		b2PolygonDef globdef;

		in >> what;
		while (what == "polygon")
		{
			int vertcount;
			in >> vertcount;
			b2Vec2* verts = new b2Vec2[vertcount];
			for (int i=0;i<vertcount;++i)
			{
				in >> verts[i].x >> verts[i].y;
			}

			b2Polygon polygon(verts,vertcount);

			delete [] verts;

			b2Polygon polys[POLYGON_DECOMPOSITION_LIMIT];
			int count = DecomposeConvex(&polygon,polys,32);

			for (int i=0;i<MIN(count,POLYGON_DECOMPOSITION_LIMIT);++i)
			{
				if (!polys[i].IsUsable()) continue;
				b2PolygonDef def = globdef;
				polys[i].AddTo(def);
				body->createAndAddPolygon(def);
			}

			if (!(in >> what)) what = "";
		}
		drawables.push_back(body);
	}

	in >> what;
	while (what == "dp")
	{
		string obj;
		float x,y,rot;

		in.ignore();
		in >> obj >> x >> y >> rot;

		Object* tmp = new Object(x,y,rot);
		tmp->loadAndPlace(world, obj);
		drawables.push_back(tmp);
		
		if (!(in >> what)) what = "";
	}

	/*Object* test = new Object(7,6,0);
	test->loadAndPlace(world, "ball01.obj");
	drawables.push_back(test);

	Object* test1 = new Object(5,5,10);
	test1->loadAndPlace(world, "box01.obj");
	drawables.push_back(test1);

	Object* test2 = new Object(6.5,5,0);
	test2->loadAndPlace(world, "box01.obj");
	drawables.push_back(test2);

	Object* test3 = new Object(9,3,46);
	test3->loadAndPlace(world, "box02.obj");
	drawables.push_back(test3);*/

	in.close();

	return actor;
}
Actor* Level::restart()
{
	return loadLevel(filename);
}
void Level::draw()
{
	for (vector<Drawable*>::iterator it = drawables.begin(); it != drawables.end(); ++it)
	{
		(*it)->draw();
	}
}
void Level::clear()
{
	for (vector<Drawable*>::iterator it = drawables.begin(); it != drawables.end(); ++it)
	{
		delete (*it);
	}
	drawables.clear();
}
Level::~Level()
{
	clear();
}