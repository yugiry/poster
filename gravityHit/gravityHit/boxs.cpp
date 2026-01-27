#pragma once
#include "boxs.h"
#include "function.h"
#include <math.h>

CBoxs::CBoxs()
{
	ImgWidth = 100 / HARF;
	ImgHeight = 100 / HARF;

	pos = { WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 };

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
	//vec.y = 0.0f;
	vec.y += 0.5f;

	GetMousePoint(&x, &y);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT))
	{
		ClickX = BoxPoint[BOXPOINT::RIGHTDOWN].x;
		ClickY = BoxPoint[BOXPOINT::RIGHTDOWN].y;
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
			radian_click = true;
		}
		if (CheckHitKey(KEY_INPUT_Q))
		{
			radian -= 1.2;
			radian_click = true;
		}

		if (radian < 0)
			radian = 359;
		if (radian >= 360)
			radian = 0;
	}

	//角度からベクトルの傾きを求める
	if(radian_click){
		VW.x = cos(RADIAN(radian));
		VW.y = sin(RADIAN(radian));

		VW = Vector_SetLength(VW, ImgWidth);

		VH.x = -VW.y; VH.y = VW.x;

		VH = Vector_SetLength(VH, ImgHeight);
		radian_click = false;
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
				Point p = BoxPoint[a];
				near_line = Near_Point_BoxLine(p, base[i]->pos, base[i]->VW, base[i]->VH);

				float length[4];
				for (int a = 0; a < 4; a++)
					length[a] = Vector_Length(near_line.vec[a]);

				//頂点が箱の中にいるなら当たっている判定
				if (length[0] < base[i]->ImgHeight * HARF && length[3] < base[i]->ImgHeight * HARF && length[1] < base[i]->ImgWidth * HARF && length[0] < base[i]->ImgWidth * HARF)
				{
					fix_length(&length[0], &near_line);

					//当たった辺まで戻る抗力ベクトルを求める
					normal_force = { near_line.vec[0].x,near_line.vec[0].y };
					float f_length = Vector_Length(vec) + Vector_Length(normal_force);
					normal_force = Vector_SetLength(normal_force, f_length);

					//抗力ベクトルを位置に追加する
					pos.x += normal_force.x;
					pos.y += normal_force.y;
					hit = true;

					//回転力を追加
				}
			}
		}
	}

	//中心座標の座標更新処理
	{
		pos.x += vec.x;
		pos.y += vec.y;

		if (hit)
		{
			vec.x = vec.y = 0.0f;
			hit = false;
		}
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
		DrawLine(BoxPoint[BOXPOINT::RIGHTDOWN].x, BoxPoint[BOXPOINT::RIGHTDOWN].y, BoxPoint[BOXPOINT::RIGHTDOWN].x + near_line.vec[i].x, BoxPoint[BOXPOINT::RIGHTDOWN].y + near_line.vec[i].y, GetColor(255, 255, 255), true);
	}

	if (click) {

		DrawLine(ClickX, ClickY, x, y, GetColor(0, 0, 255), true);

	}

	//向き表示
	DrawLine(pos.x, pos.y, pos.x + VW.x, pos.y + VW.y, GetColor(0, 255, 0), true);

	if (click)
	{
		DrawLine(pos.x, pos.y, ClickX, ClickY, GetColor(255, 0, 0), true);
	}
}
