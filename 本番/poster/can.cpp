#pragma once
#include "can.h"
#include "function.h"

CCan::CCan(Point p)
{
	dpos = p;

	img = LoadGraph("image\\Trash.png");

	ImgWidth = 32;
	ImgHeight = 32;

	CutX = 0;
	CutY = 0;

	pos.x = dpos.x - ImgWidth / 2;
	pos.y = dpos.y - ImgHeight / 2;

	weight = 1;
	pri = 1;
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
		if ((*i)->ID == CRUMB && (pos.x != (*i)->pos.x || pos.y != (*i)->pos.y))
		{
			if (HitCheck_box(pos.x,pos.y + vec.y,(*i)->pos.x,(*i)->pos.y,ImgWidth,ImgHeight,(*i)->ImgWidth,(*i)->ImgHeight))
			{
				vec.y = 0;
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
	DrawRectRotaGraph(dpos.x, dpos.y,CutX,CutY,ImgWidth,ImgHeight,1, RADIAN(0), img, true);
}