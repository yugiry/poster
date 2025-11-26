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

	GetMousePoint(&x, &y);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !click)
	{
		ClickX = x;
		ClickY = y;
	}

	pos.x += VW.x / 2 + VH.x / 2;
	pos.y += VW.y / 2 + VH.y / 2;

	if (click)
	{
		power.x = x - ClickX;
		power.y = y - ClickY;
		distance.x = ClickX - pos.x;
		distance.y = ClickY - pos.y;
		resultpower = Vector_Length(power) * 10 / Vector_Length(distance);
		if (power.x != 0 && power.y != 0)
			I = Vector_SetLength(VH, resultpower);
		else
			I.x = I.y = 0;

		Vector disright{ -distance.y,distance.x };
		radian = Twe_Vector_Angle(disright, power);

		if (radian < 90)
		{
			VW.x += I.x * 1;
			VW.y += I.y * 1;
		}
		else if (radian >= 90)
		{
			VW.x -= I.x * 1;
			VW.y -= I.y * 1;
		}
	}

	VW = Vector_SetLength(VW, ImgWidth);

	VH.x = -VW.y;
	VH.y = VW.x;

	VH = Vector_SetLength(VH, ImgHeight);

	/*if (radian < 0)radian = 359;
	if (radian >= 360)radian = 0;*/

	pos.x -= VW.x / 2 + VH.x / 2;
	pos.y -= VW.y / 2 + VH.y / 2;

	click = (GetMouseInput() & MOUSE_INPUT_LEFT);

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
		DrawLine(pos.x + VW.x / 2 + VH.x / 2, pos.y + VW.y / 2 + VH.y / 2, ClickX, ClickY, GetColor(255, 0, 0), true);
		DrawLine(x, y, ClickX, ClickY, GetColor(0, 255, 0), true);
		DrawFormatString(10, 20, GetColor(255, 255, 255), "%f,%f", I.x, I.y);
		DrawFormatString(10, 40, GetColor(255, 255, 255), "%f", radian);
	}
}
