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

Application::Application()
{
	if (!glfwInit()) {ERR_UGLY(""); return;}

	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	if( !glfwOpenWindow( 960,540, 0,0,0,4,0,0, GLFW_WINDOW ) ) //TODO: Settings loading
//	if( !glfwOpenWindow( 1920,1080, 0,0,0,4,0,0, GLFW_FULLSCREEN ) )
	{
		ERR_UGLY("");
		glfwTerminate();
		return;
	}

	glfwSetWindowTitle("Bounce Jam");
	glfwSwapInterval(0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f,GAMEWIDTH,0,GAMEHEIGHT,-1.0f,1.0f); //TODO: Different aspect ratio support
   
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.23f, 0.725f, 1.0f, 1.0f);

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

	double time = glfwGetTime();

	double fpstime = 0;
	int fpsframes = 0;

	bool running=true;
	while (running)
	{
		GSStack.top()->processEvents();
		double newtime = glfwGetTime();
		GSStack.top()->processLogic(newtime - time);
		++fpsframes;
		fpstime+= newtime - time;
		if (fpstime >= 1) { printf("%f\n",((double)fpsframes)/fpstime); fpsframes=1; fpstime=newtime - time;}
		
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