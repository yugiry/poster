#pragma once
#include "boxs.h"

CBoxs::CBoxs()
{
	ImgWidth = 200;
	ImgHeight = 80;

	pos.x = WINDOW_WIDTH / 2 - ImgWidth / 2;
	pos.y = WINDOW_HEIGHT / 2 - ImgHeight / 2;

	VW.x = vunit.x * ImgWidth;
	VW.y = vunit.y * ImgWidth;

	VH.x = vunit.y * ImgHeight;
	VH.y = vunit.x * ImgHeight;

	ID = B2;
}

int CBoxs::Action(vector<unique_ptr<BaseVector>>& base)
{
	return 0;
}

void CBoxs::Draw()
{
	DrawLine(pos.x, pos.y, pos.x + VW.x, pos.y + VW.y, GetColor(255, 255, 255), true);
	DrawLine(pos.x, pos.y, pos.x + VH.x, pos.y + VH.y, GetColor(255, 255, 255), true);
}