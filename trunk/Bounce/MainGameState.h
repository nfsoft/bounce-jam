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

#ifndef _MAINGAMESTATE_H_
#define _MAINGAMESTATE_H_

#include "global.h"

#include "GameState.h"
#include "Actor.h"
#include "ContactListener.h"
#include "Level.h"

#include "Box2D/include/Box2D.h"

class MainGameState: public GameState
{
private:
	Application* application;
	b2World* world;
	float timeSinceLastSimulation;
	Actor* actor;
	ContactListener* contactListener;
	Level* level;
	GLuint sky;
public:
	int init(Application* application);
	void destroy();
	void processEvents();
	void processLogic(double time);
	void processGraphics();
};

#endif