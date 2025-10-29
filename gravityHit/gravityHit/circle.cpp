#pragma once
#include "circle.h"
#include "math.h"

CCircle::CCircle()
{
	pos.x = WINDOW_WIDTH / 2 + 5;
	pos.y = 50;

	radius = 32;

	ID = C1;
}

int CCircle::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec.y += g;

	for (int i = 0; i < base.size(); i++)
	{
		if (base[i]->ID == C2)
		{
			Vector length{ (pos.x + vec.x) - base[i]->pos.x,(pos.y + vec.y) - base[i]->pos.y };
			float l = sqrt(length.x * length.x + length.y * length.y);
			if (l < radius + base[i]->radius)
			{
				float ll = (radius + base[i]->radius) - l;
				length.x = (length.x / l) * ll;
				length.y = (length.y / l) * ll;
				vec.x += length.x * 0.6f;
				vec.y += length.y * 0.6f;
			}
		}

		if (base[i]->ID == B2)
		{

		}
	}

	if (pos.y + vec.y > WINDOW_HEIGHT - radius)
	{
		vec.y = -vec.y * 0.6f;
		vec.x = vec.x * 0.6f;
	}
	if (pos.x + vec.x > WINDOW_WIDTH - radius || pos.x + vec.x < radius)
	{
		vec.x = -vec.x * 0.6f;
	}

	if (vec.x < 0.01f && vec.x > -0.01f)vec.x = 0;
	if (vec.y < 0.01f && vec.y > -0.01f)vec.y = 0;

	pos.x += vec.x;
	pos.y += vec.y;

	return 0;
}

void CCircle::Draw()
{
	DrawCircle(pos.x, pos.y, radius, GetColor(0, 0, 255), true);
}