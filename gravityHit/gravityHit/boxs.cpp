#pragma once
#include "boxs.h"
#include "function.h"

CBoxs::CBoxs()
{
	ImgWidth = 300;
	ImgHeight = 80;

	pos.x = WINDOW_WIDTH / 2 - ImgWidth / 2 + 100;
	pos.y = WINDOW_HEIGHT / 2 - ImgHeight / 2;

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

	//‰æ–ÊŠO‚Æ‚Ì“–‚½‚è”»’è
	{
		HitLeft_Window(this);
		HitRight_Window(this);
		HitUp_Window(this);
		HitDown_Window(this);
	}

	for (int i = 0; i < 4; i++)
	{
		Pos[i].x += vec.x;
		Pos[i].y += vec.y;
	}

	return 0;
}

void CBoxs::Draw()
{
	DrawLine(Pos[0].x, Pos[0].y, Pos[1].x, Pos[1].y, GetColor(255, 255, 255), true);
	DrawLine(Pos[0].x, Pos[0].y, Pos[3].x, Pos[3].y, GetColor(255, 255, 255), true);
	DrawLine(Pos[2].x, Pos[2].y, Pos[1].x, Pos[1].y, GetColor(255, 255, 255), true);
	DrawLine(Pos[2].x, Pos[2].y, Pos[3].x, Pos[3].y, GetColor(255, 255, 255), true);
}