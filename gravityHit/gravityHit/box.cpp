#pragma once
#include "box.h"
#include "function.h"

CBox::CBox()
{
	pos.x = WINDOW_WIDTH / 2;
	pos.y = WINDOW_HEIGHT - 50;

	ImgWidth = WINDOW_WIDTH;
	ImgHeight = 100;

	VW.x = ImgWidth / 2;
	VW.y = 0;

	VH.x = 0;
	VH.y = ImgHeight / 2;

	ID = B1;
}

CBox::CBox(Point p, int w, int h)
{
	ID = B1;
}

int CBox::Action(vector<unique_ptr<BaseVector>>& base)
{
	return 0;
}

void CBox::Draw()
{
	DrawBox(pos.x - VW.x + VH.x, pos.y - VW.y + VH.y, pos.x + VW.x - VH.x, pos.y + VW.y - VH.y, GetColor(100, 100, 100), true);
	DrawCircle(pos.x, pos.y, 2, GetColor(255, 0, 0), true);
}