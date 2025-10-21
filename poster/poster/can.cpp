#pragma once
#include "can.h"
#include "function.h"

CCan::CCan(Point p)
{
	pos = p;

	ImgWidth = 32;
	ImgHeight = 32;

	weight = 1;

	ID = CRUMB;
}

int CCan::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec.y += g;

	for (auto i = base.begin(); i != base.end(); i++)
	{
		if ((*i)->ID == WALL)
		{
			if (HitCheck_box(this, (*i).get()))
			{
				vec.y = 0;
				pos.y = (*i)->pos.y - ImgHeight;
			}
		}
	}

	pos.x += vec.x;
	pos.y += vec.y;

	return 0;
}

void CCan::Draw()
{
	//DrawBox(pos.x, pos.y, pos.x + ImgWidth, pos.y + ImgHeight, GetColor(255, 255, 255), true);

	DrawBox(pos.x, pos.y, pos.x + ImgWidth, pos.y + ImgHeight, GetColor(0, 255, 255), true);
}