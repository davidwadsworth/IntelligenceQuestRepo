#pragma once
#include "SDL.h"

class Collider
{
	virtual bool collide(const Collider& col) = 0;
};


class BoxCollider2D : public Collider
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);

};