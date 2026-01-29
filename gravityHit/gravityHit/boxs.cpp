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

	VW.x = cos(RADIAN(radian));
	VW.y = -sin(RADIAN(radian));

	VW = Vector_SetLength(VW, ImgWidth);

	VH.x = -VW.y; VH.y = VW.x;

	VH = Vector_SetLength(VH, ImgHeight);

	vertex_vec[BOXPOINT::LEFTUP] = { -VW.x - VH.x, -VW.y - VH.y };
	vertex_vec[BOXPOINT::RIGHTUP] = { VW.x - VH.x, VW.y - VH.y };
	vertex_vec[BOXPOINT::RIGHTDOWN] = { VW.x + VH.x, VW.y + VH.y };
	vertex_vec[BOXPOINT::LEFTDOWN] = { -VW.x + VH.x, -VW.y + VH.y };

	normal_force = { 0,0 };
	radian_force = { 0,0 };

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
	vec.y += g;

	GetMousePoint(&x, &y);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT))
	{
		ClickX = vertex_vec[BOXPOINT::RIGHTDOWN].x;
		ClickY = vertex_vec[BOXPOINT::RIGHTDOWN].y;
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
	/*if(radian_click){
		VW.x = cos(RADIAN(radian));
		VW.y = -sin(RADIAN(radian));

		VW = Vector_SetLength(VW, ImgWidth);

		VH.x = -VW.y; VH.y = VW.x;

		VH = Vector_SetLength(VH, ImgHeight);
		radian_click = false;
	}*/

	//当たり判定
	for (auto i = 0; i < base.size(); i++)
	{
		if (base[i]->ID == B1)
		{
			//４頂点の当たり判定を求める
			for (int a = 0; a < 4; a++)
			{
				//int a = BOXPOINT::RIGHTDOWN;
				Vector v = vertex_vec[a];
				Point p = { pos.x + v.x,pos.y + v.y };
				near_line = Near_Point_BoxLine(p, base[i]->pos, base[i]->VW, base[i]->VH);

				float length[4];
				for (int a = 0; a < 4; a++)
					length[a] = Vector_Length(near_line.vec[a]);

				//頂点が箱の中にいるなら当たっている判定
				if (length[0] < base[i]->ImgHeight * HARF && length[3] < base[i]->ImgHeight * HARF && length[1] < base[i]->ImgWidth * HARF && length[0] < base[i]->ImgWidth * HARF)
				{
					Fix_Length(&length[0], &near_line);

					//当たった辺まで戻る抗力ベクトルを求める
					Vector point_normal_force = { near_line.vec[0].x,near_line.vec[0].y };
					pos.x += point_normal_force.x;
					pos.y += point_normal_force.y;
					Vector gv = { 0,vec.y };
					float f_length = Vector_Length(gv) + Vector_Length(point_normal_force);
					point_normal_force = Vector_SetLength(point_normal_force, f_length);

					if (point_normal_force.x != normal_force.x)
						normal_force.x = point_normal_force.x;
					if (point_normal_force.y != normal_force.y)
						normal_force.y = point_normal_force.y;

					hit = true;

					p.x += normal_force.x;
					p.y += normal_force.y;

					float pn_l = Vector_Length(v);
					Vector pn_vec{ p.x - pos.x,p.y - pos.y };

					vertex_vec[a] = Vector_SetLength(pn_vec, pn_l);
					for (int t = a; t < a + 4; t++)
					{
						int j = t;
						int k = j + 1;
						if (j > 3)j -= 4;
						if (k > 3)k -= 4;
						vertex_vec[k].x = -vertex_vec[j].y; vertex_vec[k].y = vertex_vec[j].x;
					}
				}
			}
		}
	}

	//中心座標の座標更新処理
	{
		if (hit)
		{
			vec.y -= g;
			if (vec.y > -0.5f && vec.y < 0.5f)
				vec.y = 0;
			hit = false;
		}

		pos.x += vec.x;
		pos.y += vec.y;
	}

	return 0;
}

void CBoxs::Draw()
{
	//中心点表示
	DrawCircle(pos.x, pos.y, 2, GetColor(255, 0, 0), true);

	//角度表示
	DrawFormatString(5, 20, GetColor(255, 255, 255), "角度＝%f:角速度=%f", radian, force_radian);

	//箱描画
	for(int i = 0; i < 4 ; i += 2)
	{
		for (int j = 1; j < 4; j += 2)
		{
			DrawLine(pos.x + vertex_vec[i].x, pos.y + vertex_vec[i].y, pos.x + vertex_vec[j].x, pos.y + vertex_vec[j].y, GetColor(0, 255, 0), true);
		}
	}

	//当たり判定表示
	for (int i = 0; i < 4; i++)
	{
		//DrawLine(BoxPoint[BOXPOINT::RIGHTDOWN].x, BoxPoint[BOXPOINT::RIGHTDOWN].y, BoxPoint[BOXPOINT::RIGHTDOWN].x + near_line.vec[i].x, BoxPoint[BOXPOINT::RIGHTDOWN].y + near_line.vec[i].y, GetColor(255, 255, 255), true);
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

	DrawFormatString(5, 40, GetColor(255, 255, 255), "%f,%f", normal_force.x, normal_force.y);
}
