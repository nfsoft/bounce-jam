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

#include "Object.h"

#include "TextureManager.h"

#include <fstream>

Object::Object(float posx, float posy, float rot): rotation(rot*(b2_pi/180.f))
{
	position[0] = posx;
	position[1] = posy;
	size[0]=size[1]=1.0f;
	texture = TextureManager::getSingleton()->loadTexture("err.png");
}

void Object::loadAndPlace(b2World* world, string filename)
{
	this->world = world;

	//TODO: improve loading object definition from file or something
	
	ifstream in;
	in.open(filename.c_str());

	string what;
	in >> what;
	if (what != "size") ERR_UGLY("size expected");
	in >> size[0] >> size[1] >> what;
	if (what != "texture") ERR_UGLY("texture expected");
	string texturefname;
	in >> texturefname;
	texture = TextureManager::getSingleton()->loadTexture(texturefname);

	b2BodyDef bodydef;

	bodydef.position.x=position[0];
	bodydef.position.y=position[1];
	bodydef.angle=rotation;
	bodydef.userData = (void*)this;

	body = world->CreateBody(&bodydef);

	in >> what;
	while (what != "")
	{
		b2ShapeDef* def;
		if (what == "circle")
		{
			def = new b2CircleDef();
			in >> ((b2CircleDef*)def)->radius >> ((b2CircleDef*)def)->localPosition.x >> ((b2CircleDef*)def)->localPosition.y;
		} else if (what == "polygon")
		{
			def = new b2PolygonDef();
			in >> ((b2PolygonDef*)def)->vertexCount;
			for (int i=0;i<((b2PolygonDef*)def)->vertexCount;++i)
			{
				in >> ((b2PolygonDef*)def)->vertices[i].x >> ((b2PolygonDef*)def)->vertices[i].y;
			}
		} else {
			ERR_UGLY("unknown shape type: " + what);
		}
		in >> what;
		if (what != "density") ERR_UGLY("density expected");
		in >> def->density >> what;
		if (what != "friction") ERR_UGLY("friction expected");
		in >> def->friction >> what;
		if (what != "restitution") ERR_UGLY("restitution expected");
		in >> def->restitution >> what;

		body->CreateShape(def);
		delete def;
		if (!(in >> what)) what = "";
	}
	body->SetMassFromShapes();

	in.close();
}

void Object::draw()
{
	glBindTexture(GL_TEXTURE_2D, texture);

	glPushMatrix();
		glTranslatef(position[0],position[1],.0f);
		glRotatef(rotation,0,0,1);
		glBegin(GL_QUADS);
			glTexCoord2f(.0f, 1.0f);
			glVertex2f(.0f, .0f);
			glTexCoord2f(1.0, 1.0f);
			glVertex2f(size[0], .0f);
			glTexCoord2f(1.0, .0f);
			glVertex2f(size[0], size[1]);
			glTexCoord2f(.0f, .0f);
			glVertex2f(.0f, size[1]);
		glEnd();
	glPopMatrix();
}

void Object::setTransform(float posx, float posy, float rot)
{
	position[0] = posx;
	position[1] = posy;
	rotation = rot;
}
b2Body* Object::getBody()
{
	return body;
}
Object::~Object()
{
	world->DestroyBody(body);
}