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

#include "Static.h"

Static::Static(b2World* world, GLuint texture)
{
	this->world=world;
	this->texture = texture;
	b2BodyDef bodydef;
	body = world->CreateBody(&bodydef);
}
void Static::createAndAddPolygon(b2PolygonDef& def)
{
	polygons.push_back((b2PolygonShape*)body->CreateShape((b2ShapeDef*)&def));
}
void Static::draw()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	for (vector<b2PolygonShape*>::iterator it = polygons.begin(); it != polygons.end(); ++it)
	{
		glBegin(GL_POLYGON);
		const b2Vec2* vecs=(*it)->GetVertices();
		for (int i=0;i<(*it)->GetVertexCount();++i)
		{
			glTexCoord2f(vecs[i].x/4.0f,vecs[i].y/4.0f);
			glVertex2f(vecs[i].x,vecs[i].y);
		}
		glEnd();

#ifdef _DEBUG //Polygon outlines
		glColor3f(0,0,0);
		glDisable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT,GL_LINE);
		glBegin(GL_POLYGON);
		for (int i=0;i<(*it)->GetVertexCount();++i)
		{
			glTexCoord2f(vecs[i].x/4.0f,vecs[i].y/4.0f);
			glVertex2f(vecs[i].x,vecs[i].y);
		}
		glEnd();
		glPolygonMode(GL_FRONT,GL_FILL);
		glEnable(GL_TEXTURE_2D);
		glColor3f(1,1,1);
#endif
	}
}
Static::~Static()
{
	world->DestroyBody(body);
}