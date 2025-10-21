#pragma once
#include "can.h"
#include "function.h"

CCan::CCan(Point p)
{
	dpos = p;

	img = LoadGraph("image\\can.png");

	ImgWidth = 24;
	ImgHeight = 64;

	pos.x = dpos.x - ImgWidth / 2;
	pos.y = dpos.y - ImgHeight / 2;

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
	dpos.x = pos.x + ImgWidth / 2;
	dpos.y = pos.y + ImgHeight / 2;

	return 0;
}

void CCan::Draw()
{
	DrawRotaGraph(dpos.x, dpos.y, 1, RADIAN(90), img, true);
}