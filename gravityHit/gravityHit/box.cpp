#pragma once
#include "box.h"
#include "function.h"

CBox::CBox()
{
	pos.x = WINDOW_WIDTH / 2;
	pos.y = WINDOW_HEIGHT - 100;

	ImgWidth = WINDOW_WIDTH / HARF;
	ImgHeight = 100 / HARF;

	radian = 0;

	{
		VW.x = cos(RADIAN(radian));
		VW.y = sin(RADIAN(radian));

		VW = Vector_SetLength(VW, ImgWidth);

		VH.x = -VW.y; VH.y = VW.x;

		VH = Vector_SetLength(VH, ImgHeight);
	}

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
	DrawLine(pos.x - VW.x - VH.x, pos.y - VW.y - VH.y, pos.x + VW.x - VH.x, pos.y + VW.y - VH.y, GetColor(150, 150, 150), true);
	DrawLine(pos.x - VW.x - VH.x, pos.y - VW.y - VH.y, pos.x - VW.x + VH.x, pos.y - VW.y + VH.y, GetColor(150, 150, 150), true);
	DrawLine(pos.x + VW.x + VH.x, pos.y + VW.y + VH.y, pos.x + VW.x - VH.x, pos.y + VW.y - VH.y, GetColor(150, 150, 150), true);
	DrawLine(pos.x + VW.x + VH.x, pos.y + VW.y + VH.y, pos.x - VW.x + VH.x, pos.y - VW.y + VH.y, GetColor(150, 150, 150), true);
	DrawCircle(pos.x, pos.y, 2, GetColor(255, 0, 0), true);
}