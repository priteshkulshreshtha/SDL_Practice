#include <iostream>
#include <cmath>

#include "GameObject.h"
#include "TextureLoader.h"


const int FORCE_SCALE = 50;


float getAngle(float forceX, float forceY)
{
	float angle = atan(forceY / forceX) * 180 / 3.1415;
	if (forceX > 0 && forceY < 0)
	{
		angle = 90 - angle;

	}
	if (forceX < 0 && forceY > 0)
	{
		angle = 360 + angle;

	}
	if (forceX > 0 && forceY > 0)
	{
		angle = 180 + angle;

	}
	return angle;

}

GameObject::GameObject(const char* texturePath, SDL_Renderer* ren, int x, int y)
	:xpos(x), ypos(y), dstRect({}), srcRect({}), mouseX(NULL), mouseY(NULL), forceX(0), forceY(0)
{
	renderer = ren;
	objTexture = TextureLoader::loadTexture(texturePath, ren);
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	if (std::abs(forceX) > 0.1 && std::abs(forceY) > 0.1)
	{
		float frictionX, frictionY;
		

		frictionX = std::abs(friction * cos(angle));
		frictionY = std::abs(friction * sin(angle));

	
		if (std::abs(forceX) > std::abs(frictionX))
		{
			forceX = forceX + (forceX > 0 ? -1 : 1) * frictionX;
		}
		else
		{
			forceX = 0;
		}

		if (std::abs(forceY) > std::abs(frictionY))
		{
			forceY = forceY + (forceY > 0 ? -1 : 1) * frictionY;
		}
		else
		{
			forceY = 0;
		}

		float accx = forceX / mass;
		float accy = forceY / mass;

		xpos += accx * FORCE_SCALE;
		ypos += accy * FORCE_SCALE;

		collisionDetection();

	}
	else
	{
		forceX = 0;
		forceY = 0;
	}

	srcRect = { 0, 0, 64, 64 };
	dstRect = { xpos, ypos, 64, 64 };
}

void GameObject::render()
{
	SDL_RenderCopy(renderer, objTexture, &srcRect, &dstRect);
}

void GameObject::handleInputMouseDown(int p_mouseX, int p_mouseY)
{
	if ((xpos <= p_mouseX && p_mouseX <= xpos + 64) && (ypos <= p_mouseY && p_mouseY <= ypos + 64))
	{
		mouseX = p_mouseX;
		mouseY = p_mouseY;
	}
}


void GameObject::handleInputMouseUp(int p_mouseX, int p_mouseY)
{
	forceX = std::max(-2.0, std::min((mouseX - p_mouseX) / 300.0, 2.0));
	forceY = std::max(-2.0, std::min((mouseY - p_mouseY) / 300.0, 2.0));	
	
	//angle = getAngle(forceX, forceY);
	angle = atan(forceY / forceX);

	std::cout << angle << " " << forceX << " " << forceY << std::endl;
}

void GameObject::collisionDetection()
{
	if (xpos <= 0 || xpos + 64 >= 1280) {
		forceX *= -1;
	}
	if (ypos <= 0 || ypos + 64 >= 720) {
		forceY *= -1;
	}
	
}