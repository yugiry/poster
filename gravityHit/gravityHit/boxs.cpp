#pragma once
#include "boxs.h"
#include "function.h"
#include <math.h>

CBoxs::CBoxs()
{
	ImgWidth = 300;
	ImgHeight = 80;

	pos.x = WINDOW_WIDTH / 2 - ImgWidth / 2;
	pos.y = WINDOW_HEIGHT / 2 - ImgHeight / 2;

	radian = 0;

	VW.x = cos(radian);
	VW.y = sin(radian);

	VW = Vector_SetLength(VW, ImgWidth);

	VH.x = VW.y;
	VH.y = VW.x;

	VH = Vector_SetLength(VH, ImgHeight);

	weight = 1;

	ID = B2;
}

int CBoxs::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec.x = 0.0f; 
	vec.y = 0.0f;

	pos.x += VW.x / 2 + VH.x / 2;
	pos.y += VW.y / 2 + VH.y / 2;

	I = Vector_SetLength(VH, 1);
	
	if (CheckHitKey(KEY_INPUT_U))
	{
		VW.x += I.x;
		VW.y += I.y;
	}
	if (CheckHitKey(KEY_INPUT_I))
	{
		VW.x -= I.x;
		VW.y -= I.y;
	}

	VW.x = cos(RADIAN(atan2(VW.y, VW.x)));
	VW.y = sin(RADIAN(atan2(VW.y, VW.x)));

	VW = Vector_SetLength(VW, ImgWidth);

	VH.x = -VW.y;
	VH.y = VW.x;

	VH = Vector_SetLength(VH, ImgHeight);

	if (radian < 0)radian = 359;
	if (radian >= 360)radian = 0;
	if (radian >= 360)radian = 0;

	pos.x -= VW.x / 2 + VH.x / 2;
	pos.y -= VW.y / 2 + VH.y / 2;

	return 0;
}

void CBoxs::Draw()
{
	DrawLine(pos.x, pos.y, pos.x + VW.x, pos.y + VW.y, GetColor(255, 255, 255), true);
	DrawLine(pos.x, pos.y, pos.x + VH.x, pos.y + VH.y, GetColor(0, 255, 255), true);
	DrawLine(pos.x + VW.x + VH.x, pos.y + VW.y + VH.y, pos.x + VW.x, pos.y + VW.y, GetColor(255, 0, 255), true);
	DrawLine(pos.x + VW.x + VH.x, pos.y + VW.y + VH.y, pos.x + VH.x, pos.y + VH.y, GetColor(255, 255, 0), true);

	if (click)
	{
		DrawLine(x, y, ClickX, ClickY, GetColor(0, 255, 0), true);
		DrawFormatString(10, 20, GetColor(255, 255, 255), "%f,%f", I.x, I.y);
	}
}
