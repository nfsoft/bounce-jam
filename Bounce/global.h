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

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define ERR_UGLY(x) cerr << "ERR at " << __FILE__ << ":" << __LINE__ << " (" << x << ")" << endl;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define MIN(x,y) ((x) > (y) ? (y) : (x))

#define POLYGON_DECOMPOSITION_LIMIT 64
#define TIMESTEP (1.0f/120.0f)

#define GAMEWIDTH 32
#define GAMEHEIGHT 18

#endif