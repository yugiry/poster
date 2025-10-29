#pragma once
#include "circles.h"

CCircles::CCircles()
{
	pos.x = WINDOW_WIDTH / 2;
	pos.y = WINDOW_HEIGHT / 2;

	radius = 32;

	ID = C2;
}

int CCircles::Action(vector<unique_ptr<BaseVector>>& base)
{
	return 0;
}

void CCircles::Draw()
{
	DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 255), false);
}