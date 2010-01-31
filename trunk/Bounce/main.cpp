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

#include "Application.h"

#pragma comment(lib, "opengl32.lib")
#ifdef _DEBUG
	#pragma comment(lib, "GLFW/lib/GLFW_d.lib")
	#pragma comment(lib, "Box2D/lib/box2d_d.lib")
#else
	#pragma comment(lib, "GLFW/lib/GLFW.lib")
	#pragma comment(lib, "Box2D/lib/box2d.lib")
#endif


int main(int argc, const char* argv[])
{
	Application application;
	application.run();
	return 0;
}