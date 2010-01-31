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

#ifndef _CONTACTLISTENER_H_
#define _CONTACTLISTENER_H_

#include "Box2D/include/Box2D.h"

#include "Object.h"

class ContactListener : public b2ContactListener
{
private:
	bool actorAbleToJump;
	b2Vec2 actorJumpVector;
public:
	ContactListener() {reset();}
    void Result(const b2ContactResult* point)
    {
		void* udata1=point->shape1->GetBody()->GetUserData();
		void* udata2=point->shape2->GetBody()->GetUserData();
		if (udata1 && ((Object*)udata1)->getObjectType()==OBJECT_ACTOR)
		{
			actorJumpVector+=-point->normal;
			actorAbleToJump=true;
		}
		if (udata2 && ((Object*)udata2)->getObjectType()==OBJECT_ACTOR)
		{
			actorJumpVector+=point->normal;
			actorAbleToJump=true;
		}
    }
	bool isActorAbleToJump() {return actorAbleToJump;}
	b2Vec2& getActorJumpVector() {actorAbleToJump=false; return actorJumpVector;} //"destructive" read
	void reset()
	{
		actorAbleToJump=false;
		actorJumpVector.SetZero();
	}
};

#endif