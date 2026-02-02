#pragma once
#include "boxs.h"
#include "function.h"
#include <math.h>

CBoxs::CBoxs()
{
	ImgWidth = 100 / HARF;
	ImgHeight = 100 / HARF;

	pos = { WINDOW_WIDTH / 2,200 };

	VW.x = ImgWidth;
	VW.y = 0;

	VH.x = 0;
	VH.y = ImgHeight;

	radian = 0;

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
	vec.y += g;

	//当たり判定
	for (auto i = 0; i < base.size(); i++)
	{
		if (base[i]->ID == B1)
		{
			//４頂点の当たり判定を求める
			for (int a = 0; a < 4; a++)
			{
				//現在調べている頂点からそれぞれの辺までの最短距離を調べる
				Vector v = vertex_vec[a];						//現在調べている頂点までのベクトルを記録
				Point p = { pos.x + v.x,pos.y + v.y };		//現在調べている頂点のワールド座標
				near_line = Near_Point_BoxLine(p, base[i]->pos, base[i]->VW, base[i]->VH);

				//最短距離の長さを保存
				float length[4];
				for (int a = 0; a < 4; a++)
					length[a] = Vector_Length(near_line.vec[a]);

				//頂点が箱の中にいるなら当たっている判定
				if (length[0] < base[i]->ImgHeight * HARF && length[3] < base[i]->ImgHeight * HARF && length[1] < base[i]->ImgWidth * HARF && length[2] < base[i]->ImgWidth * HARF)
				{
					//距離の短い順にソートする
					Fix_Length(&length[0], &near_line);

					//四角がめり込んだ分だけ戻す
					Vector point_normal_force = { near_line.vec[0].x,near_line.vec[0].y };
					pos.x += point_normal_force.x;
					pos.y += point_normal_force.y;
					
					//現在四角が持っている速度ベクトルとめり込んだ長さを足して頂点にかかった力の長さを求め、垂直にかかる抗力として適応する
					float f_length = Vector_Length(vec) + Vector_Length(point_normal_force);
					normal_force = Vector_SetLength(point_normal_force, f_length);

					//頂点座標に抗力分を足す
					p.x += normal_force.x;
					p.y += normal_force.y;

					//現在の頂点までのベクトルの傾きと長さを適応させる
					float pnf_l = Vector_Length(v);						//元の中心点から頂点までの長さ
					Vector pnf_vec{ p.x - pos.x,p.y - pos.y };		//現在の中心点から頂点までのベクトル
					vertex_vec[a] = Vector_SetLength(pnf_vec, pnf_l);

					//現在調べている頂点から各頂点までのベクトルの傾きと長さを計算し適応させる
					for (int i = a; i < a + 4; i++)
					{
						int j = i;
						int k = j + 1;
						if (j > 3)j -= 4;
						if (k > 3)k -= 4;
						vertex_vec[k].x = -vertex_vec[j].y; vertex_vec[k].y = vertex_vec[j].x;
					}

					//当たったという判定を返す
					hit = true;
				}
			}
		}
	}

	//中心座標の座標更新処理
	{
		//当たっていたら重量加速分減らしていく
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










	//リセット用
	if (CheckHitKey(KEY_INPUT_R) && !radian_click)
	{
		pos = { WINDOW_WIDTH / 2,200 };

		VW.x = ImgWidth;
		VW.y = 0;

		VH.x = 0;
		VH.y = ImgHeight;

		int r = Range_Random_Number(0, 359);

		VW.x = cos(RADIAN(r));
		VW.y = -sin(RADIAN(r));

		VW = Vector_SetLength(VW, ImgWidth);

		VH.x = -VW.y; VH.y = VW.x;

		VH = Vector_SetLength(VH, ImgHeight);

		vertex_vec[BOXPOINT::LEFTUP] = { -VW.x - VH.x, -VW.y - VH.y };
		vertex_vec[BOXPOINT::RIGHTUP] = { VW.x - VH.x, VW.y - VH.y };
		vertex_vec[BOXPOINT::RIGHTDOWN] = { VW.x + VH.x, VW.y + VH.y };
		vertex_vec[BOXPOINT::LEFTDOWN] = { -VW.x + VH.x, -VW.y + VH.y };

		normal_force = { 0,0 };
		radian_force = { 0,0 };

		vec.x = vec.y = 0.0f;
	}
	radian_click = CheckHitKey(KEY_INPUT_R);

	//GetMousePoint(&x, &y);

	/*if ((GetMouseInput() & MOUSE_INPUT_LEFT))
	{
		ClickX = vertex_vec[BOXPOINT::RIGHTDOWN].x;
		ClickY = vertex_vec[BOXPOINT::RIGHTDOWN].y;
	}
	click = (GetMouseInput() & MOUSE_INPUT_LEFT);*/

	//移動処理
	/*{
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
	}*/

	//回転処理
	//{
	//	if (CheckHitKey(KEY_INPUT_E))
	//	{
	//		radian += 1.2;
	//		radian_click = true;
	//	}
	//	if (CheckHitKey(KEY_INPUT_Q))
	//	{
	//		radian -= 1.2;
	//		radian_click = true;
	//	}

	//	if (radian < 0)
	//		radian = 359;
	//	if (radian >= 360)
	//		radian = 0;
	//}

	////角度からベクトルの傾きを求める
	//if(radian_click){
	//	VW.x = cos(RADIAN(radian));
	//	VW.y = -sin(RADIAN(radian));

	//	VW = Vector_SetLength(VW, ImgWidth);

	//	VH.x = -VW.y; VH.y = VW.x;

	//	VH = Vector_SetLength(VH, ImgHeight);
	//	radian_click = false;
	//}

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

	Vector v = { vertex_vec[BOXPOINT::RIGHTDOWN].x + vertex_vec[BOXPOINT::RIGHTUP].x,vertex_vec[BOXPOINT::RIGHTDOWN].y + vertex_vec[BOXPOINT::RIGHTUP].y };
	v = Vector_SetLength(v, ImgWidth);

	DrawLine(pos.x, pos.y, pos.x + v.x, pos.y + v.y, GetColor(255, 255, 255), true);

	if (click)
	{
		DrawLine(pos.x, pos.y, ClickX, ClickY, GetColor(255, 0, 0), true);
	}

	DrawFormatString(5, 40, GetColor(255, 255, 255), "%f,%f", normal_force.x, normal_force.y);
}
