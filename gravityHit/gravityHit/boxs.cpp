#pragma once
#include "boxs.h"
#include "function.h"

CBoxs::CBoxs()
{
	ImgWidth = 300;
	ImgHeight = 80;

	pos.x = WINDOW_WIDTH / 2 - ImgWidth / 2 + 100;
	pos.y = WINDOW_HEIGHT / 2 - ImgHeight / 2 - 50;

	VW.x = cos(RADIAN(radian));
	VW.y = sin(RADIAN(radian));

	VW = Vector_SetLength(VW, ImgWidth);

	VH.x = -VW.y;
	VH.y = VW.x;

	VH = Vector_SetLength(VH, ImgHeight);

	ID = B2;
}

int CBoxs::Action(vector<unique_ptr<BaseVector>>& base)
{
	if (CheckHitKey(KEY_INPUT_Q))
	{
		radian-=3;
	}
	if (CheckHitKey(KEY_INPUT_E))
	{
		radian+=3;
	}

	//回転の制限
	if (radian <= -1)radian = 359;
	if (radian >= 360)radian = 0;

	pos.x += VW.x / 2 + VH.x / 2;
	pos.y += VW.y / 2 + VH.y / 2;

	//角度から傾きを求めてベクトルに代入
	VW.x = cos(RADIAN(radian));
	VW.y = sin(RADIAN(radian));
	//90度回転させたベクトルを代入
	VH.x = -VW.y; VH.y = VW.x;
	//代入したベクトルの長さを調整
	VW = Vector_SetLength(VW, ImgWidth);
	VH = Vector_SetLength(VH, ImgHeight);

	pos.x -= VW.x / 2 + VH.x / 2;
	pos.y -= VW.y / 2 + VH.y / 2;

	return 0;
}

void CBoxs::Draw()
{
	DrawLine(pos.x, pos.y, pos.x + VW.x, pos.y + VW.y, GetColor(255, 255, 255), true);
	DrawLine(pos.x, pos.y, pos.x + VH.x, pos.y + VH.y, GetColor(255, 255, 255), true);
}