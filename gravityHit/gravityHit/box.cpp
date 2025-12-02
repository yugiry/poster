#pragma once
#include "box.h"
#include "function.h"

CBox::CBox()
{
	pos.x = 300;
	pos.y = WINDOW_HEIGHT - 100;

	ImgWidth = 300;
	ImgHeight = 100;

	VW.x = ImgWidth;
	VW.y = 0;

	VH.x = 0;
	VH.y = ImgHeight;

	ID = B1;
}

CBox::CBox(Point p, int w, int h)
{
	pos = p;
	ImgWidth = w;
	ImgHeight = h;

	VW.x = ImgWidth;
	VW.y = 0;

	VH.x = 0;
	VH.y = ImgHeight;

	ID = B1;
}

int CBox::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec.x = vec.y = 0;

	if (CheckHitKey(KEY_INPUT_W))
	{
		vec.y = -2.0f;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		vec.y = 2.0f;
	}

	//pos.x += vec.x;
	//pos.y += vec.y;

	return 0;
}

void CBox::Draw()
{
	DrawBox(pos.x, pos.y, pos.x + VW.x + VH.x, pos.y + VW.y + VH.y, GetColor(100, 100, 100), false);
}