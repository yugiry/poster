#pragma once
#include "boxs.h"
#include "function.h"

CBoxs::CBoxs()
{
	ImgWidth = 300;
	ImgHeight = 80;

	pos.x = WINDOW_WIDTH / 2 - ImgWidth / 2;
	pos.y = 50;

	Pos[0] = pos;
	Pos[1] = { pos.x + ImgWidth,pos.y };
	Pos[2] = { pos.x + ImgWidth,pos.y + ImgHeight };
	Pos[3] = { pos.x,pos.y + ImgHeight };

	ID = B2;
}

int CBoxs::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec.x = 0.0f;
	vec.y += g;

	for (int i = 0; i < 4; i++)
	{
		Pos[i].x += vec.x;
		Pos[i].y += vec.y;
	}

	//‰æ–ÊŠO
	if (Pos[2].y > WINDOW_HEIGHT / 2 - 150)
	{
		vec.y = 0;
		Pos[2].y = WINDOW_HEIGHT / 2 - 150;
		Vector v { Pos[3].x - Pos[2].x,Pos[3].y - Pos[2].y };
		v = Vector_SetLength(v, ImgWidth);
		Pos[3].x = Pos[2].x + v.x;
		Pos[3].y = Pos[2].y + v.y;
		v = { Pos[1].x - Pos[0].x,Pos[1].y - Pos[0].y };
		v = Vector_SetLength(v, ImgWidth);
		Pos[1].x = Pos[0].x + v.x;
		Pos[1].y = Pos[0].y + v.y;
		v = { Pos[1].x - Pos[2].x,Pos[1].y - Pos[2].y };
		v = Vector_SetLength(v, ImgHeight);
		Pos[1].x = Pos[2].x + v.x;
		Pos[1].y = Pos[2].y + v.y;
		v = { Pos[0].x - Pos[1].x,Pos[0].y - Pos[1].y };
		if (sqrtf(v.x * v.x + v.y * v.y) > ImgWidth)
		{
			v = Vector_SetLength(v, ImgWidth);
			Pos[0].x = Pos[1].x + v.x;
			Pos[0].y = Pos[1].y + v.y;
		}
	}
	/*if (Pos[3].y > WINDOW_HEIGHT)
	{
		vec.y = 0;
		Pos[3].y = WINDOW_HEIGHT;
		Vector v{ Pos[0].x - Pos[3].x,Pos[0].y - Pos[3].y };
		v = Vector_SetLength(v, ImgHeight);
		Pos[0].x = Pos[3].x + v.x;
		Pos[0].y = Pos[3].y + v.y;
	}*/

	return 0;
}

void CBoxs::Draw()
{
	DrawLine(Pos[0].x, Pos[0].y, Pos[1].x, Pos[1].y, GetColor(255, 255, 255), true);
	DrawLine(Pos[0].x, Pos[0].y, Pos[3].x, Pos[3].y, GetColor(0, 255, 255), true);
	DrawLine(Pos[2].x, Pos[2].y, Pos[1].x, Pos[1].y, GetColor(255, 0, 255), true);
	DrawLine(Pos[2].x, Pos[2].y, Pos[3].x, Pos[3].y, GetColor(255, 255, 0), true);

	DrawFormatString(10, 20, GetColor(255, 255, 255), "%f:%f", Pos[0].x, Pos[0].y);
	DrawFormatString(10, 35, GetColor(255, 255, 255), "%f:%f", Pos[1].x, Pos[1].y);
}
