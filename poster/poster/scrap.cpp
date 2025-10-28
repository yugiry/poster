#pragma once
#include "scrap.h"
#include "function.h"

CScrap::CScrap(Point p)
{
	pos = p;

	ImgWidth = 230;
	ImgHeight = 100;

	ID = SCRAP;
}

int CScrap::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec.y += g;

	{
		Point p{ pos.x + vec.x,pos.y + vec.y };
		for (auto i = base.begin(); i != base.end(); i++)
		{
			if ((*i)->ID == WALL)
			{
				if (HitCheck_box(p.x, p.y, (*i)->pos.x, (*i)->pos.y, ImgWidth, ImgHeight, (*i)->ImgWidth, (*i)->ImgHeight))
				{
					vec.y = 0;
					pos.y = (*i)->pos.y - ImgHeight;
				}
			}
		}
	}

	pos.x += vec.x;
	pos.y += vec.y;

	return 0;
}

void CScrap::Draw()
{
	DrawBox(pos.x, pos.y, pos.x + ImgWidth, pos.y + ImgHeight, GetColor(0, 255, 0), true);
}