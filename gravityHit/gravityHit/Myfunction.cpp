#pragma once
#include "function.h"
#include <math.h>

//P->点,A->直線の始点,B->直線の終点
Point Near_Point_Line(Point P, Point A, Point B)
{
	Point Q{ 0,0 };//直線上の点
	Vector n{ B.x - A.x,B.y - A.y };//直線の方向ベクトル
	Vector AP{ P.x - A.x,P.y - A.y };//始点からの点までのベクトル
	float t = (AP.x * n.x + AP.y * n.y) / (n.x * n.x + n.y * n.y);//投影係数
	if (t < 0)t = 0;//0より小さい場合は始点値
	if (t > 1)t = 1.0f;//1より大きい場合は終点値
	Q = Add_Point_Vector(A, Mul_Vector_Scaler(n, t));

	return Q;
}

//点と四角形それぞれの辺の近い距離を調べる
//(点の座標、四角形の座標、四角形の横幅、四角形の縦幅)
BoxLine Near_Point_BoxLine(Point p, Point b, Vector w, Vector h)
{
	BoxLine bl;
	Point pos;
	//上
	Point SL{ b.x - w.x - h.x,b.y - w.y - h.y };
	Point EL{ b.x + w.x - h.x,b.y + w.y - h.y };
	pos = Near_Point_Line(p, SL, EL);
	bl.vec[0] = { pos.x - p.x,pos.y - p.y };
	//左
	EL = { b.x - w.x + h.x,b.y - w.y + h.y };
	pos = Near_Point_Line(p, SL, EL);
	bl.vec[1] = { pos.x - p.x,pos.y - p.y };
	//右
	SL = { b.x + w.x + h.x,b.y + w.y + h.y };
	EL = { b.x + w.x - h.x,b.y + w.y - h.y };
	pos = Near_Point_Line(p, SL, EL);
	bl.vec[2] = { pos.x - p.x,pos.y - p.y };
	//下
	EL = { b.x - w.x + h.x,b.y - w.y + h.y };
	pos = Near_Point_Line(p, SL, EL);
	bl.vec[3] = { pos.x - p.x,pos.y - p.y };

	return bl;
}

bool Check_Hit_Point(BoxLine l, BaseVector* a)
{
	float length[4];
	for (int a = 0; a < 4; a++)
		length[a] = Vector_Length(l.vec[a]);

	if (length[0] < a->ImgHeight * HARF && length[3] < a->ImgHeight * HARF && length[1] < a->ImgWidth * HARF && length[0] < a->ImgWidth * HARF)
	{
		return true;
	}

	return false;
}

void Hit_Box_Vertex(BoxLine l, BaseVector* a, BaseVector* b)
{

}

//二つのベクトルのなす角を求める
float Twe_Vector_Angle(Vector a, Vector b)
{
	double la = Vector_Length(a);
	double lb = Vector_Length(b);

	double cos_sita = Dot(a, b) / (la * lb);
	
	double sita = acos(cos_sita);
	sita = sita * 180 / M_PI;

	return sita;
}

//長さの配列を短い順に揃える
void Fix_Length(float* l, BoxLine* nl)
{
	float l_tmp;
	Vector nl_tmp;

	for (int i = 0; i < 4; i++)
	{
		for (int j = i; j < 4; j++)
		{
			if (l[i] > l[j])
			{
				l_tmp = l[i];
				nl_tmp = nl->vec[i];
				l[i] = l[j];
				nl->vec[i] = nl->vec[j];
				l[j] = l_tmp;
				nl->vec[j] = nl_tmp;
			}
		}
	}
}

//四角形の当たり判定(座標、横幅ベクトル、縦幅ベクトル)
void HitLeft_Window(BaseVector* b)
{
	//左上が左下より左にいれば
	if (b->pos.x <= b->pos.x + b->VH.x)
	{
		//右上が左上より左にいれば
		if (b->pos.x + b->VW.x < b->pos.x && b->pos.x + b->VW.x < 0)
		{
			b->pos.x = -b->VW.x;
			return;
		}
		if (b->pos.x < 0)
		{
			b->pos.x = 0;
			return;
		}
	}
	//左下が左上より左にいれば
	else
	{
		//右下が左下より左にいれば
		if (b->pos.x + b->VH.x + b->VW.x < b->pos.x + b->VH.x && b->pos.x + b->VH.x + b->VW.x < 0)
		{
			b->pos.x = -(b->VW.x + b->VH.x);
			return;
		}
		if (b->pos.x + b->VH.x < 0)
		{
			b->pos.x = -b->VH.x;
			return;
		}
	}

	//何も当たっていなければ
	return;
}
void HitRight_Window(BaseVector* b)
{
	//左上が左下より右にいれば
	if (b->pos.x >= b->pos.x + b->VH.x)
	{
		//右上が左上より右にいれば
		if (b->pos.x + b->VW.x > b->pos.x && b->pos.x + b->VW.x > WINDOW_WIDTH)
		{
			b->pos.x = WINDOW_WIDTH - b->VW.x;
			return;
		}
		if (b->pos.x > WINDOW_WIDTH)
		{
			b->pos.x = WINDOW_WIDTH;
			return;
		}
	}
	//左下が左上より右にいれば
	else
	{
		//右下が左下より右にいれば
		if (b->pos.x + b->VH.x + b->VW.x > b->pos.x + b->VH.x && b->pos.x + b->VH.x + b->VW.x > WINDOW_WIDTH)
		{
			b->pos.x = WINDOW_WIDTH - b->VW.x - b->VH.x;
			return;
		}
		if (b->pos.x + b->VH.x > WINDOW_WIDTH)
		{
			b->pos.x = WINDOW_WIDTH - b->VH.x;
			return;
		}
	}

	//何も当たっていなければ
	return;
}
void HitUp_Window(BaseVector* b)
{
	//左上が左下より上にいれば
	if (b->pos.y <= b->pos.y + b->VH.y)
	{
		//右上が左上より上にいれば
		if (b->pos.y + b->VW.y < b->pos.y && b->pos.y + b->VW.y < 0)
		{
			b->pos.y = -b->VW.y;
			return;
		}
		if (b->pos.y < 0)
		{
			b->pos.y = 0;
			return;
		}
	}
	//左下が左上より上にいれば
	else
	{
		//右下が左下より上にいれば
		if (b->pos.y + b->VH.y + b->VW.y < b->pos.y + b->VH.y && b->pos.y + b->VH.y + b->VW.y < 0)
		{
			b->pos.y = -(b->VH.y + b->VW.y);
			return;
		}
		if (b->pos.y + b->VH.y < 0)
		{
			b->pos.y = -b->VH.y;
			return;
		}
	}

	//何も当たっていなければ
	return;
}
void HitDown_Window(BaseVector* b)
{
	//左上が左下より下にいれば
	if (b->pos.y >= b->pos.y + b->VH.y)
	{
		//右上が左上より下にいれば
		if (b->pos.y + b->VW.y > b->pos.y && b->pos.y + b->VW.y > WINDOW_HEIGHT)
		{
			b->pos.y = WINDOW_HEIGHT - b->VW.y;
			b->vec.y = 0;
			return;
		}

		if (b->pos.y > WINDOW_HEIGHT)
		{
			b->pos.y = WINDOW_HEIGHT;
			b->vec.y = 0;
			return;
		}

	}
	//左下が左上より下にいれば
	else
	{
		//右下が左下より下にいれば
		if (b->pos.y + b->VH.y + b->VW.y > b->pos.y + b->VH.y && b->pos.y + b->VH.y + b->VW.y > WINDOW_HEIGHT)
		{
			b->pos.y = WINDOW_HEIGHT - b->VW.y - b->VH.y;
			b->vec.y = 0; 
			return;
		}
		if (b->pos.y + b->VH.y > WINDOW_HEIGHT)
		{
			b->pos.y = WINDOW_HEIGHT - b->VH.y;
			b->vec.y = 0;
			return;
		}
	}

	//何も当たっていなければ
	return;
}
