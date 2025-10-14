#pragma once
#include "wall.h"

CWall::CWall(Point p, int w, int h)
{
	pos = p;

	ImgWidth = w;
	ImgHeight = h;
}

int CWall::Action(vector<unique_ptr<BaseVector>>& base)
{
	return 0;
}

void CWall::Draw()
{
	DrawBox(pos.x, pos.y, pos.x + ImgWidth, pos.y + ImgHeight, GetColor(100, 100, 100), true);
}