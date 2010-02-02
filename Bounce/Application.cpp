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

#include "global.h"
#include "Application.h"

#include "GLFW/include/glfw.h"

#include "MainGameState.h"

#include "Configuration.h"

Application::Application()
{
	if (!glfwInit()) {ERR_UGLY(""); return;}

	Configuration* config = Configuration::getSingleton();
	config->loadFile("Bounce.cfg");

	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, config->getValueInt("window_fsaa_samples"));
	if( !glfwOpenWindow( config->getValueInt("window_width"),config->getValueInt("window_height"), 0,0,0,0,0,0, config->getValueBool("fullscreen") ? GLFW_FULLSCREEN : GLFW_WINDOW ) )
	{
		ERR_UGLY("");
		glfwTerminate();
		return;
	}

	glfwSetWindowTitle("Bounce Jam");
	glfwSwapInterval(0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float windowAspRat = config->getValue("window_width") / config->getValue("window_height");
	float gameAspRat = ((float)GAMEWIDTH)/((float)GAMEHEIGHT);
	float xpadding = .0f, ypadding = .0f;
	if (windowAspRat < gameAspRat) //more square than 16:9 (16:10,4:3,5:4,..)
	{
		ypadding = (GAMEWIDTH/windowAspRat - GAMEHEIGHT)/2.0f;
	} else { // wider than 16:9 (strange..)
		xpadding = (GAMEHEIGHT*windowAspRat - GAMEWIDTH)/2.0f;
	}
	glOrtho(-xpadding,GAMEWIDTH+xpadding,-ypadding,GAMEHEIGHT+ypadding,-1.0f,1.0f);
	if (config->getValueBool("scissor"))
	{
		glScissor((int)(xpadding/((float)GAMEWIDTH+2*xpadding)*config->getValue("window_width")),
			(int)(ypadding/((float)GAMEHEIGHT+2*ypadding)*config->getValue("window_height")),
			(int)((GAMEWIDTH)/((float)GAMEWIDTH+2*xpadding)*config->getValue("window_width")),
			(int)((GAMEHEIGHT)/((float)GAMEHEIGHT+2*ypadding)*config->getValue("window_height")));
		glEnable(GL_SCISSOR_TEST);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_DITHER);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

}

Application::~Application()
{
	while (!GSStack.empty()) popGS();
	glfwTerminate();
}

void Application::run()
{
	pushGS(new MainGameState());
	GSStack.top()->init(this);

	float time = (float)glfwGetTime();

	float fpstime = 0;
	int fpsframes = 0;

	bool running=true;
	while (running)
	{
		GSStack.top()->processEvents();
		float newtime = (float)glfwGetTime();
		GSStack.top()->processLogic(newtime - time);
		++fpsframes;
		fpstime+= newtime - time;
		if (fpstime >= 1) { printf("%f\n",((float)fpsframes)/fpstime); fpsframes=1; fpstime=newtime - time;}
		
		time = newtime;

		glClear( GL_COLOR_BUFFER_BIT );

		glLoadIdentity();

		GSStack.top()->processGraphics();

		glfwSwapBuffers();
		running = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
	
	}
}
void Application::pushGS(GameState* gameState)
{
	GSStack.push(gameState);
}
void Application::popGS()
{
	if (GSStack.empty()) return;
	delete GSStack.top();
	GSStack.pop();
}