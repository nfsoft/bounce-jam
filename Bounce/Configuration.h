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

#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include "global.h"
#include <map>
#include <fstream>

class Configuration
{
private:
	map<string,float> dict;
public:
	void loadFile(string filename)
	{
		ifstream in;
		in.open(filename.c_str());

		while (!in.eof())
		{
			string id;
			float val;
			in >> id >> val;
			setValue(id,val);
		}

		in.close();
	}
	void setValue(string id, float val)
	{
		map<string,float>::iterator it = dict.find(id);
		if (it == dict.end())
			dict[id] = val;
		else
			dict.insert(pair<string,float>(id,val));
	}
	float getValue(string id)
	{
		map<string,float>::iterator it = dict.find(id);
		if (it == dict.end())
			return .0f;
		else
			return dict[id];
	}
	int getValueInt(string id)
	{
		return (int)getValue(id);
	}
	bool getValueBool(string id)
	{
		return getValue(id) != 0;
	}
	static Configuration* getSingleton() {static Configuration instance; return &instance;}
};

#endif