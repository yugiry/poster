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

CBoxs::CBoxs(Point p, int w, int h)
{
	pos = p;

	ImgWidth = w;
	ImgHeight = h;

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
	//vec.y = 0.0f;
	vec.y += 0.5f;

	GetMousePoint(&x, &y);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !click)
	{
		ClickX = x;
		ClickY = y;
	}

	//当たり判定
	for (int i = 0; i < base.size(); i++)
	{
		//四角形
		if (base[i]->ID == B1)
		{
			//それぞれの頂点からそれぞれの辺への最短距離を調べる
			Point p[4];
			p[0] = pos;
			line[0] = Near_Point_BoxLine(p[0], base[i]->pos, base[i]->VW, base[i]->VH);
			p[1] = {pos.x + VW.x,pos.y + VW.y};
			line[1] = Near_Point_BoxLine(p[1], base[i]->pos, base[i]->VW, base[i]->VH);
			p[2] = {pos.x + VH.x,pos.y + VH.y};
			line[2] = Near_Point_BoxLine(p[2], base[i]->pos, base[i]->VW, base[i]->VH);
			p[3] = {pos.x + VW.x + VH.x,pos.y + VW.y + VH.y};
			line[3] = Near_Point_BoxLine(p[3], base[i]->pos, base[i]->VW, base[i]->VH);

			Point mp = { pos.x + VW.x / 2 + VH.x / 2,pos.y + VW.y / 2 + VH.y / 2 };

			//各頂点ごとの辺への当たり判定
			for (int j = 0; j < 4; j++)
			{
				float l1 = Vector_Length(line[j].vec[0]);
				float l2 = Vector_Length(line[j].vec[3]);

				if (l1 < base[i]->ImgHeight && l2 < base[i]->ImgHeight)
				{
					if (l1 < l2)
					{
						pos.x += VW.x / 2 + VH.x / 2;
						pos.y += VW.y / 2 + VH.y / 2;

						power = line[j].vec[0];
						distance = { p[j].x - mp.x,p[j].y - mp.y };
						resultpower = Vector_Length(power) * 700 / Vector_Length(distance);
						if (power.x != 0 || power.y != 0)
							I = Vector_SetLength(VH, resultpower);
						else
							I.x = I.y = 0;

						Vector disright{ -distance.y,distance.x };
						radian = Twe_Vector_Angle(disright, power);

						if (radian < 90)
						{
							VW.x += I.x;
							VW.y += I.y;
						}
						else if (radian >= 90)
						{
							VW.x -= I.x;
							VW.y -= I.y;
						}
						pos.x += line[j].vec[0].x;
						pos.y += line[j].vec[0].y;
						vec.y -= vec.y * 0.6f;

						pos.x -= VW.x / 2 + VH.x / 2;
						pos.y -= VW.y / 2 + VH.y / 2;
					}
					if (l1 > l2)
					{
						pos.x += VW.x / 2 + VH.x / 2;
						pos.y += VW.y / 2 + VH.y / 2;

						power = line[j].vec[3];
						distance = { p[j].x - mp.x,p[j].y - mp.y };
						resultpower = Vector_Length(power) * 700 / Vector_Length(distance);
						if (power.x != 0 || power.y != 0)
							I = Vector_SetLength(VH, resultpower);
						else
							I.x = I.y = 0;

						Vector disright{ -distance.y,distance.x };
						radian = Twe_Vector_Angle(disright, power);

						if (radian < 90)
						{
							VW.x += I.x;
							VW.y += I.y;
						}
						else if (radian >= 90)
						{
							VW.x -= I.x;
							VW.y -= I.y;
						}
						pos.x += line[j].vec[3].x;
						pos.y += line[j].vec[3].y;
						vec.y -= vec.y * 0.6f;

						pos.x -= VW.x / 2 + VH.x / 2;
						pos.y -= VW.y / 2 + VH.y / 2;
					}
				}
			}
		}
		if (base[i]->ID == B2 && (pos.x != base[i]->pos.x || pos.y != base[i]->pos.y))
		{
			//それぞれの頂点からそれぞれの辺への最短距離を調べる
			Point p[4];
			p[0] = pos;
			line[0] = Near_Point_BoxLine(p[0], base[i]->pos, base[i]->VW, base[i]->VH);
			p[1] = { pos.x + VW.x,pos.y + VW.y };
			line[1] = Near_Point_BoxLine(p[1], base[i]->pos, base[i]->VW, base[i]->VH);
			p[2] = { pos.x + VH.x,pos.y + VH.y };
			line[2] = Near_Point_BoxLine(p[2], base[i]->pos, base[i]->VW, base[i]->VH);
			p[3] = { pos.x + VW.x + VH.x,pos.y + VW.y + VH.y };
			line[3] = Near_Point_BoxLine(p[3], base[i]->pos, base[i]->VW, base[i]->VH);

			Point mp = { pos.x + VW.x / 2 + VH.x / 2,pos.y + VW.y / 2 + VH.y / 2 };

			//各頂点ごとの辺への当たり判定
			for (int j = 0; j < 4; j++)
			{
				float l1 = Vector_Length(line[j].vec[0]);
				float l2 = Vector_Length(line[j].vec[3]);

				if (l1 < base[i]->ImgHeight && l2 < base[i]->ImgHeight)
				{
					if (l1 < l2)
					{
						pos.x += VW.x / 2 + VH.x / 2;
						pos.y += VW.y / 2 + VH.y / 2;

						power = line[j].vec[0];
						distance = { p[j].x - mp.x,p[j].y - mp.y };
						resultpower = Vector_Length(power) * 700 / Vector_Length(distance);
						if (power.x != 0 || power.y != 0)
							I = Vector_SetLength(VH, resultpower);
						else
							I.x = I.y = 0;

						Vector disright{ -distance.y,distance.x };
						radian = Twe_Vector_Angle(disright, power);

						if (radian < 90)
						{
							VW.x += I.x;
							VW.y += I.y;
						}
						else if (radian >= 90)
						{
							VW.x -= I.x;
							VW.y -= I.y;
						}
						pos.x += line[j].vec[0].x;
						pos.y += line[j].vec[0].y;
						vec.y -= vec.y * 0.6f;

						pos.x -= VW.x / 2 + VH.x / 2;
						pos.y -= VW.y / 2 + VH.y / 2;
					}
					if (l1 > l2)
					{
						pos.x += VW.x / 2 + VH.x / 2;
						pos.y += VW.y / 2 + VH.y / 2;

						power = line[j].vec[3];
						distance = { p[j].x - mp.x,p[j].y - mp.y };
						resultpower = Vector_Length(power) * 700 / Vector_Length(distance);
						if (power.x != 0 || power.y != 0)
							I = Vector_SetLength(VH, resultpower);
						else
							I.x = I.y = 0;

						Vector disright{ -distance.y,distance.x };
						radian = Twe_Vector_Angle(disright, power);

						if (radian < 90)
						{
							VW.x += I.x;
							VW.y += I.y;
						}
						else if (radian >= 90)
						{
							VW.x -= I.x;
							VW.y -= I.y;
						}
						pos.x += line[j].vec[3].x;
						pos.y += line[j].vec[3].y;
						vec.y -= vec.y * 0.6f;

						pos.x -= VW.x / 2 + VH.x / 2;
						pos.y -= VW.y / 2 + VH.y / 2;
					}
				}
			}
		}
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

	if (CheckHitKey(KEY_INPUT_W))vec.y = -5.0f;
	if (CheckHitKey(KEY_INPUT_S))vec.y = 5.0f;
	if (CheckHitKey(KEY_INPUT_A))vec.x = -5.0f;
	if (CheckHitKey(KEY_INPUT_D))vec.x = 5.0f;

	pos.x += vec.x;
	pos.y += vec.y;

	return 0;
}

void CBoxs::Draw()
{
	DrawLine(pos.x, pos.y, pos.x + VW.x, pos.y + VW.y, GetColor(255, 255, 255), true);
	DrawLine(pos.x, pos.y, pos.x + VH.x, pos.y + VH.y, GetColor(0, 255, 255), true);
	DrawLine(pos.x + VW.x + VH.x, pos.y + VW.y + VH.y, pos.x + VW.x, pos.y + VW.y, GetColor(255, 0, 255), true);
	DrawLine(pos.x + VW.x + VH.x, pos.y + VW.y + VH.y, pos.x + VH.x, pos.y + VH.y, GetColor(255, 255, 0), true);

	/*for (int i = 0; i < 4; i++)
	{
		Point p = pos;
		DrawLine(p.x, p.y, p.x + line[0].vec[i].x, p.y +line[0].vec[i].y, GetColor(255, 150, 255), true);
		p = { pos.x + VW.x,pos.y + VW.y };
		DrawLine(p.x, p.y, p.x + line[1].vec[i].x, p.y + line[1].vec[i].y, GetColor(150, 255, 255), true);
		p = { pos.x + VH.x,pos.y + VH.y };
		DrawLine(p.x, p.y, p.x + line[2].vec[i].x, p.y + line[2].vec[i].y, GetColor(255, 255, 150), true);
		p = { pos.x + VW.x + VH.x,pos.y + VW.y + VH.y };
		DrawLine(p.x, p.y, p.x + line[3].vec[i].x, p.y + line[3].vec[i].y, GetColor(150, 150, 150), true);
	}*/

	if (click)
	{
		DrawLine(pos.x + VW.x / 2 + VH.x / 2, pos.y + VW.y / 2 + VH.y / 2, ClickX, ClickY, GetColor(255, 0, 0), true);
		DrawLine(x, y, ClickX, ClickY, GetColor(0, 255, 0), true);
		DrawFormatString(10, 20, GetColor(255, 255, 255), "%f,%f", I.x, I.y);
		DrawFormatString(10, 40, GetColor(255, 255, 255), "%f", radian);
	}
}
