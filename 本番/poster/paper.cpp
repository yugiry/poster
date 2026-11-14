#pragma once
#include "paper.h"
#include "function.h"

CPaper::CPaper(Point p)
{
	pos = p;
	ImgWidth = 32;
	ImgHeight = 32;
	img = LoadGraph("image\\Trash.png");
	radius = 16;
	CutX = 0;
	CutY = 32;
	weight = 1;

	ID = BURNABLE;
}

int CPaper::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec.y += g;

	for (auto i = base.begin(); i != base.end(); i++)
	{
		if ((*i)->ID == WALL)
		{
			if (HitCheck_Box_CircleB(this, (*i).get(), radius))
			{
				vec.y = 0;
			}
		}
	}

	pos.x += vec.x;
	pos.y += vec.y;

	return 0;
}

void CPaper::Draw()
{
	DrawRectRotaGraph(dpos.x, dpos.y, CutX, CutY, ImgWidth, ImgHeight, 1, RADIAN(0), img, true);
}