#pragma once
#include "hitobj.h"

CHitobj::CHitobj(Point p, int w, int h)
{
	pos.x = p.x;
	pos.y = p.y + 60;

	ImgWidth = w;
	ImgHeight = h;
}

int CHitobj::Action(vector<unique_ptr<BaseVector>>& base)
{

	for (auto i = base.begin(); i != base.end(); i++)
	{
		if ((*i)->ID == BURNABLE)
		{
			
		}
	}

	return 0;
}

void CHitobj::Draw()
{
	DrawBox(pos.x, pos.y, pos.x + ImgWidth, pos.y + ImgHeight, GetColor(255, 255, 0), true);

	FLAG = false;
}