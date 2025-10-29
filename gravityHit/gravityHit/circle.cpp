#pragma once
#include "circle.h"
#include "math.h"
#include "function.h"

CCircle::CCircle()
{
	pos.x = WINDOW_WIDTH / 2 + 5;
	pos.y = 50;

	radius = 32;

	ID = C1;
}

int CCircle::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec.y += g;
	//vec = { 0,0 };

	//移動
	{
		if (CheckHitKey(KEY_INPUT_W))vec.y = -3.0f;
		if (CheckHitKey(KEY_INPUT_S)) vec.y = 3.0f;
		if (CheckHitKey(KEY_INPUT_A)) vec.x = -3.0f;
		if (CheckHitKey(KEY_INPUT_D)) vec.x = 3.0f;
	}

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		pos.y = 50;
	}

	if (pos.y + vec.y > WINDOW_HEIGHT - radius)
	{
		vec.y = -vec.y * bound;
		vec.x = vec.x * bound;
	}
	if (pos.x + vec.x > WINDOW_WIDTH - radius || pos.x + vec.x < radius)
	{
		vec.x = -vec.x * bound;
	}

	for (int i = 0; i < base.size(); i++)
	{
		/*if (base[i]->ID == C2)
		{
			Vector length{ (pos.x + vec.x) - base[i]->pos.x,(pos.y + vec.y) - base[i]->pos.y };
			float l = sqrt(length.x * length.x + length.y * length.y);
			if (l < radius + base[i]->radius)
			{
				float ll = (radius + base[i]->radius) - l;
				length.x = (length.x / l) * ll;
				length.y = (length.y / l) * ll;
				vec.x += length.x * 0.6f;
				vec.y += length.y * 0.6f;
			}
		}*/

		if (base[i]->ID == B2)
		{
			Point Q{ 0,0 };//直線上の点
			Point A = base[i]->pos;//直線の始点
			Point B{ base[i]->pos.x + base[i]->VW.x,base[i]->pos.y + base[i]->VW.y };//直線の終点
			Vector n{ B.x - A.x,B.y - A.y };//直線の方向ベクトル
			Point P = pos;
			Vector AP{ P.x - A.x,P.y - A.y };//始点からの点までのベクトル
			float t = (AP.x * n.x + AP.y * n.y) / (n.x * n.x + n.y * n.y);//投影係数
			if (t < 0)t = 0;//0より小さい場合は始点値
			if (t > 1)t = 1.0f;//1より大きい場合は終点値
			p = Add_Point_Vector(A, Mul_Vector_Scaler(n, t));
			Vector v{ pos.x - p.x,pos.y - p.y };
			float l = sqrt(v.x * v.x + v.y * v.y);
			if (l < radius)
			{
				v = Vector_SetLength(v, (radius - l));
				 
				//v.y *= 0.2f;
				vec.x += v.x;
				vec.y += v.y;
				vec.y = vec.y * bound;
			}
		}
	}

	if (vec.x < 0.01f && vec.x > -0.01f)vec.x = 0;
	if (vec.y < 0.01f && vec.y > -0.01f)vec.y = 0;

	pos.x += vec.x;
	pos.y += vec.y;

	return 0;
}

void CCircle::Draw()
{
	DrawCircle(pos.x, pos.y, radius, GetColor(0, 0, 255), true);

	//DrawLine(pos.x, pos.y, pos.x + vv1.x, pos.y + vv1.y, GetColor(255, 0, 0), true);
	//DrawLine(pos.x, pos.y, pos.x + vv2.x, pos.y + vv2.y, GetColor(255, 0, 0), true);
	DrawLine(pos.x, pos.y, p.x, p.y, GetColor(255, 0, 0), true);
}