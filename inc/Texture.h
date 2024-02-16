#pragma once
#include <iostream>
#include <SDL2/SDL.h>

class LTexture
{
public:
	virtual void RenderToScreen(SDL_Renderer* renderer);
};