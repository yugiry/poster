#pragma once
#include "function.h"

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

//四角形の当たり判定(座標、横幅ベクトル、縦幅ベクトル)
void HitLeft(BaseVector* b)
{
	//左上が左下より左にいれば
	if (b->pos.x <= b->pos.x + b->VH.x)
	{
		//右上が左上より左にいれば
		if (b->pos.x + b->VW.x < b->pos.x && b->pos.x + b->VW.x < 0);

		if (b->pos.x < 0);
		
	}
	//左下が左上より左にいれば
	else
	{
		//右下が左下より左にいれば
		if (b->pos.x + b->VH.x + b->VW.x < b->pos.x + b->VH.x && b->pos.x + b->VH.x + b->VW.x < 0);
		if (b->pos.x + b->VH.x < 0);
	}

	//何も当たっていなければ
	return;
}
void HitRight(BaseVector* b)
{
	//左上が左下より右にいれば
	if (b->pos.x >= b->pos.x + b->VH.x)
	{
		//右上が左上より右にいれば
		if (b->pos.x + b->VW.x > b->pos.x && b->pos.x + b->VW.x > WINDOW_WIDTH);

		if (b->pos.x > WINDOW_WIDTH);

	}
	//左下が左上より右にいれば
	else
	{
		//右下が左下より右にいれば
		if (b->pos.x + b->VH.x + b->VW.x > b->pos.x + b->VH.x && b->pos.x + b->VH.x + b->VW.x > WINDOW_WIDTH);
		if (b->pos.x + b->VH.x > WINDOW_WIDTH);
	}

	//何も当たっていなければ
	return;
}
void HitUp(BaseVector* b)
{
	//左上が左下より左にいれば
	if (b->pos.y <= b->pos.y + b->VH.y)
	{
		//右上が左上より左にいれば
		if (b->pos.y + b->VW.y < b->pos.y && b->pos.y + b->VW.y < 0);

		if (b->pos.y < 0);

	}
	//左下が左上より左にいれば
	else
	{
		//右下が左下より左にいれば
		if (b->pos.y + b->VH.y + b->VW.y < b->pos.y + b->VH.y && b->pos.y + b->VH.y + b->VW.y < 0);
		if (b->pos.y + b->VH.y < 0);
	}

	//何も当たっていなければ
	return;
}
void HitDown(BaseVector* b)
{
	//左上が左下より右にいれば
	if (b->pos.y >= b->pos.y + b->VH.y)
	{
		//右上が左上より右にいれば
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
	//左下が左上より右にいれば
	else
	{
		//右下が左下より右にいれば
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
