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

#include "MainGameState.h"

#include "TextureManager.h"

int MainGameState::init(Application* application)
{
	contactListener=new ContactListener();

	b2AABB worldAABB;
	worldAABB.lowerBound.Set(-500.0f, -500.0f);
	worldAABB.upperBound.Set(500.0f, 500.0f);

	world = new b2World(worldAABB, b2Vec2(0.0f, -9.81f), true);
	world->SetContactListener(contactListener);
	timeSinceLastSimulation = .0f;
	rightAfterSimulation = false;

	level = new Level(world);

	actor = level->loadLevel("level01.lev");

	sky = TextureManager::getSingleton()->loadTexture("sky01.png", true); //TODO: think about putting sky into Level instead

	return 0;
}
void MainGameState::destroy()
{
	delete level;
	delete world;
	delete contactListener;
}
void MainGameState::processEvents()
{

//#ifdef _DEBUG

	if (glfwGetKey('W')) glPolygonMode(GL_FRONT,GL_LINE);
	if (glfwGetKey('F')) glPolygonMode(GL_FRONT,GL_FILL);

//#endif

	if (glfwGetKey('R')) actor=level->restart();


	if (glfwGetKey(GLFW_KEY_RIGHT) && actor->getBody()->GetAngularVelocity() > -10)
		actor->getBody()->ApplyForce(b2Vec2(300.0f,0.0f),actor->getBody()->GetWorldCenter()+b2Vec2(0,1));
	if (glfwGetKey(GLFW_KEY_LEFT) && actor->getBody()->GetAngularVelocity() < 10)
		actor->getBody()->ApplyForce(b2Vec2(-300.0f,0.0f),actor->getBody()->GetWorldCenter()+b2Vec2(0,1));
	if (glfwGetKey(GLFW_KEY_SPACE) && contactListener->isActorAbleToJump() && actor->canJump())
	{
		b2Vec2 vector(0,0);
		b2Vec2 normal = contactListener->getActorJumpVector();

		if (glfwGetKey(GLFW_KEY_LEFT)) {vector+=b2Vec2(-1,0);}
		if (glfwGetKey(GLFW_KEY_RIGHT)) {vector+=b2Vec2(1,0);}
		if (vector.Length() == 0)
		{
			vector+=b2Vec2(0,0.7f);
		} else {
			vector+=b2Vec2(0,0.7f);
			vector.Normalize();
		}
		vector += contactListener->getActorJumpVector();
		vector*=80.0f;
		actor->jump(vector);
	}
	if (glfwGetKey(GLFW_KEY_DOWN) && rightAfterSimulation) { //TODO: Probably just debugging purpose, doesn't respect slow motion
		b2Vec2 vel=actor->getBody()->GetLinearVelocity();
		vel.x*=0.96f;
		actor->getBody()->SetLinearVelocity(vel);
	}
}
void MainGameState::processLogic(float time)
{
	float slowMotionFactor = glfwGetKey('S') ? 2.0f : 1.0f; //Is it evil to call glfwGetKey here? :)
	timeSinceLastSimulation += time;
	actor->addTime(time/slowMotionFactor);
	if (timeSinceLastSimulation >= TIMESTEP)
	{
		if (!actor->getBody()->IsSleeping()) contactListener->reset();
		while (timeSinceLastSimulation >= TIMESTEP)
		{
			world->Step(TIMESTEP/slowMotionFactor,5);
			timeSinceLastSimulation -= TIMESTEP;
		}
		for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
		{
			if (b->GetUserData())
			{
				const b2Vec2& pos = b->GetPosition();
				((Object*)b->GetUserData())->setTransform(pos.x, pos.y, b->GetAngle()*(180.0f/b2_pi));
			}
		}
		rightAfterSimulation = true;
	} else {
		rightAfterSimulation = false;
	}
}
void MainGameState::processGraphics()
{
	float wx=actor->getBody()->GetWorldCenter().x;
	float wy=actor->getBody()->GetWorldCenter().y;

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, sky);

		glBegin(GL_QUADS);
			glTexCoord2f(wx/32.0f, -wy/32.0f+1.2f);
			glVertex2f(.0f, .0f);
			glTexCoord2f(wx/32.0f+2.1f, -wy/32.0f+1.2f);
			glVertex2f(GAMEWIDTH, .0f);
			glTexCoord2f(wx/32.0f+2.1f, -wy/32.0f);
			glVertex2f(GAMEWIDTH, GAMEHEIGHT);
			glTexCoord2f(wx/32.0f, -wy/32.0f);
			glVertex2f(.0f, GAMEHEIGHT);
		glEnd();

	glPopMatrix();

	glTranslatef(-wx+GAMEWIDTH/2.5f,-wy+GAMEHEIGHT/2.5f,0);

	level->draw();
}