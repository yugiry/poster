#pragma once
#include "boxs.h"
#include "function.h"
#include <math.h>

CBoxs::CBoxs()
{
	pos = { WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 };

	ImgWidth = 50;
	ImgHeight = 50;

	VW.x = ImgWidth;
	VW.y = 0;

	VH.x = 0;
	VH.y = ImgHeight;

	radian = 0;

	BoxPoint[BOXPOINT::LEFTUP] = { pos.x - VW.x - VH.x, pos.y - VW.y - VH.y };
	BoxPoint[BOXPOINT::RIGHTUP] = { pos.x + VW.x - VH.x, pos.y + VW.y - VH.y };
	BoxPoint[BOXPOINT::LEFTDOWN] = { pos.x - VW.x + VH.x, pos.y - VW.y + VH.y };
	BoxPoint[BOXPOINT::RIGHTDOWN] = { pos.x + VW.x + VH.x, pos.y + VW.y + VH.y };

	ID = B2;
}

CBoxs::CBoxs(Point p, int w, int h)
{
	

	ID = B2;
}

int CBoxs::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec.x = 0.0f; 
	vec.y = 0.0f;
	//vec.y += 0.5f;

	GetMousePoint(&x, &y);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !click)
	{
		ClickX = x;
		ClickY = y;
	}
	click = (GetMouseInput() & MOUSE_INPUT_LEFT);

	//移動処理
	{
		if (CheckHitKey(KEY_INPUT_W))
		{
			vec.y = -3.0f;
		}
		if (CheckHitKey(KEY_INPUT_S))
		{
			vec.y = 3.0f;
		}
		if (CheckHitKey(KEY_INPUT_A))
		{
			vec.x = -3.0f;
		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			vec.x = 3.0f;
		}
	}

	//回転処理
	{
		if (CheckHitKey(KEY_INPUT_E))
		{
			radian += 1.2;
		}
		if (CheckHitKey(KEY_INPUT_Q))
		{
			radian -= 1.2;
		}

		if (radian < 0)
			radian = 359;
		if (radian >= 360)
			radian = 0;
	}

	//角度からベクトルの傾きを求める
	{
		VW.x = cos(RADIAN(radian));
		VW.y = sin(RADIAN(radian));

		VW = Vector_SetLength(VW, ImgWidth);

		VH.x = -VW.y; VH.y = VW.x;

		VH = Vector_SetLength(VH, ImgHeight);
	}

	//当たり判定
	for (auto i = 0; i < base.size(); i++)
	{
		if (base[i]->ID == B1)
		{
			//４頂点の当たり判定を求める
			//for (int a = 0; a < 4; a++)
			{
				int a = BOXPOINT::RIGHTDOWN;
				Point NearPos;
				Point p = BoxPoint[a];
				Point linestart = { base[i]->pos.x - base[i]->VW.x + base[i]->VH.x,base[i]->pos.y - base[i]->VW.y + base[i]->VH.y };
				Point lineend = { base[i]->pos.x + base[i]->VW.x + base[i]->VH.x ,base[i]->pos.y + base[i]->VW.y + base[i]->VH.y };
				NearPos = Near_Point_Line(p, linestart, lineend);
				line.vec[0] = { NearPos.x - p.x,NearPos.y - p.y };
				lineend = { base[i]->pos.x - base[i]->VW.x - base[i]->VH.x ,base[i]->pos.y - base[i]->VW.y - base[i]->VH.y };
				NearPos = Near_Point_Line(p, linestart, lineend);
				line.vec[1] = { NearPos.x - p.x,NearPos.y - p.y };
				linestart = { base[i]->pos.x + base[i]->VW.x - base[i]->VH.x,base[i]->pos.y + base[i]->VW.y - base[i]->VH.y };
				lineend = { base[i]->pos.x + base[i]->VW.x + base[i]->VH.x ,base[i]->pos.y + base[i]->VW.y + base[i]->VH.y };
				NearPos = Near_Point_Line(p, linestart, lineend);
				line.vec[2] = { NearPos.x - p.x,NearPos.y - p.y };
				lineend = { base[i]->pos.x - base[i]->VW.x - base[i]->VH.x ,base[i]->pos.y - base[i]->VW.y - base[i]->VH.y };
				NearPos = Near_Point_Line(p, linestart, lineend);
				line.vec[3] = { NearPos.x - p.x,NearPos.y - p.y };
			}
		}
	}

	//中心座標の座標更新処理
	{
		pos.x += vec.x;
		pos.y += vec.y;
	}

	//４頂点の座標更新処理
	BoxPoint[BOXPOINT::LEFTUP] = { pos.x - VW.x - VH.x, pos.y - VW.y - VH.y };
	BoxPoint[BOXPOINT::RIGHTUP] = { pos.x + VW.x - VH.x, pos.y + VW.y - VH.y };
	BoxPoint[BOXPOINT::LEFTDOWN] = { pos.x - VW.x + VH.x, pos.y - VW.y + VH.y };
	BoxPoint[BOXPOINT::RIGHTDOWN] = { pos.x + VW.x + VH.x, pos.y + VW.y + VH.y };

	return 0;
}

void CBoxs::Draw()
{
	//中心点表示
	DrawCircle(pos.x, pos.y, 2, GetColor(255, 0, 0), true);

	//角度表示
	DrawFormatString(5, 20, GetColor(255, 255, 255), "角度＝%f", radian);

	//箱描画
	{
		DrawLine(BoxPoint[BOXPOINT::LEFTUP].x, BoxPoint[BOXPOINT::LEFTUP].y, BoxPoint[BOXPOINT::RIGHTUP].x, BoxPoint[BOXPOINT::RIGHTUP].y, GetColor(0, 255, 0), true);
		DrawLine(BoxPoint[BOXPOINT::LEFTUP].x, BoxPoint[BOXPOINT::LEFTUP].y, BoxPoint[BOXPOINT::LEFTDOWN].x, BoxPoint[BOXPOINT::LEFTDOWN].y, GetColor(0, 255, 0), true);
		DrawLine(BoxPoint[BOXPOINT::RIGHTUP].x, BoxPoint[BOXPOINT::RIGHTUP].y, BoxPoint[BOXPOINT::RIGHTDOWN].x, BoxPoint[BOXPOINT::RIGHTDOWN].y, GetColor(0, 255, 0), true);
		DrawLine(BoxPoint[BOXPOINT::LEFTDOWN].x, BoxPoint[BOXPOINT::LEFTDOWN].y, BoxPoint[BOXPOINT::RIGHTDOWN].x, BoxPoint[BOXPOINT::RIGHTDOWN].y, GetColor(0, 255, 0), true);
	}

	//当たり判定表示
	for (int i = 0; i < 4; i++)
	{
		DrawLine(BoxPoint[BOXPOINT::RIGHTDOWN].x, BoxPoint[BOXPOINT::RIGHTDOWN].y, BoxPoint[BOXPOINT::RIGHTDOWN].x + line.vec[i].x, BoxPoint[BOXPOINT::RIGHTDOWN].y + line.vec[i].y, GetColor(255,255,255), true);
	}

	//向き表示
	DrawLine(pos.x, pos.y, pos.x + VW.x, pos.y + VW.y, GetColor(0, 255, 0), true);

	if (click)
	{
		DrawLine(pos.x, pos.y, ClickX, ClickY, GetColor(255, 0, 0), true);
	}
}
