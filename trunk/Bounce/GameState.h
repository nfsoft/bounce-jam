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

#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

class Application;

class GameState
{
public:
	virtual int init(Application* application) = 0;
	virtual void destroy() = 0;
	virtual void processEvents() = 0;
	virtual void processLogic(double time) = 0;
	virtual void processGraphics() = 0;
	virtual ~GameState() = 0 {}
};

#endif