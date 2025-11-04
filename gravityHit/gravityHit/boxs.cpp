#pragma once
#include "boxs.h"
#include "function.h"

CBoxs::CBoxs()
{
	ImgWidth = 300;
	ImgHeight = 80;

	pos.x = WINDOW_WIDTH / 2 - ImgWidth / 2 + 100;
	pos.y = WINDOW_HEIGHT / 2 - ImgHeight / 2;

	ID = B2;
}

int CBoxs::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec.x = 0.0f;
	vec.y += g;

	if (CheckHitKey(KEY_INPUT_W))vec.y = -4.0f;
	if (CheckHitKey(KEY_INPUT_S))vec.y = 4.0f;
	if (CheckHitKey(KEY_INPUT_A))vec.x = -4.0f;
	if (CheckHitKey(KEY_INPUT_D))vec.x = 4.0f;

	if (CheckHitKey(KEY_INPUT_U))
	{
		radian-=3;
	}
	if (CheckHitKey(KEY_INPUT_I))
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

	//当たり判定
	for (int i = 0; i < base.size(); i++)
	{
		//四角形と円の当たり判定
		if (base[i]->ID == C1)
		{
			Point P = base[i]->pos;
			Point A = pos;
			Point B{ pos.x + VW.x,pos.y + VW.y };
			Point C{ pos.x + VH.x,pos.y + VH.y };
			Point D{ pos.x + VW.x + VH.x,pos.y + VW.y + VH.y };
			//四辺それぞれの点から一番近い距離を求める
			line[0] = Near_Point_Line(P, A, B);
			line[1] = Near_Point_Line(P, A, C);
			line[2] = Near_Point_Line(P, D, B);
			line[3] = Near_Point_Line(P, D, C);
			//四辺との当たり判定
			for (int j = 0; j < 4; j++)
			{
				Vector v{ line[j].x - P.x,line[j].y - P.y };
				float l = sqrt(v.x * v.x + v.y * v.y);
				if (l < base[i]->radius)
				{
					v = Vector_SetLength(v, (base[i]->radius - l));

					//v.y *= 0.2f;
					vec.x += v.x;
					vec.y += v.y;
					vec.y = vec.y;
				}
			}
		}
	}

	//画面外との当たり判定
	{
		HitLeft_Window(this);
		HitRight_Window(this);
		HitUp_Window(this);
		HitDown_Window(this);
	}

	pos.x += vec.x;
	pos.y += vec.y;

	return 0;
}

void CBoxs::Draw()
{
	DrawLine(pos.x, pos.y, pos.x + VW.x, pos.y + VW.y, GetColor(255, 255, 255), true);
	DrawLine(pos.x, pos.y, pos.x + VH.x, pos.y + VH.y, GetColor(255, 255, 255), true);
	DrawLine(pos.x + VW.x + VH.x, pos.y + VW.y + VH.y, pos.x + VW.x, pos.y + VW.y, GetColor(255, 255, 255), true);
	DrawLine(pos.x + VW.x + VH.x, pos.y + VW.y + VH.y, pos.x + VH.x, pos.y + VH.y, GetColor(255, 255, 255), true);
}