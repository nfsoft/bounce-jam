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

#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "Object.h"

#define JUMP_INTERVAL .2f //in seconds

class Actor : public Object
{
private:
	float timeSinceLastJump;
public:
	int getObjectType() {return OBJECT_ACTOR;}
	Actor(float posx, float posy, float rot) : Object(posx,posy,rot)
	{
		timeSinceLastJump = .0f;
	}
	void addTime(float passed)
	{
		timeSinceLastJump += passed;
	}
	bool canJump()
	{
		return timeSinceLastJump >= JUMP_INTERVAL;
	}
	void jump(b2Vec2& vector)
	{
		body->ApplyImpulse(vector, body->GetWorldCenter());
		timeSinceLastJump = .0f;
	}
};

#endif