#pragma once
#include "line.h"
#include "function.h"

CLine::CLine()
{
	pos = { 50,50 };

	VW = { 0,0 };

	ID = L1;
}

int CLine::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec = { 0,0 };

	if (CheckHitKey(KEY_INPUT_W))vec.y=-4.0f;
	if (CheckHitKey(KEY_INPUT_S))vec.y=4.0f;
	if (CheckHitKey(KEY_INPUT_A))vec.x=-4.0f;
	if (CheckHitKey(KEY_INPUT_D))vec.x=4.0f;

	for (int i = 0; i < base.size(); i++)
	{
		if (base[i]->ID == L2)
		{

		}
	}

	pos.x += vec.x;
	pos.y += vec.y;

	return 0;
}

void CLine::Draw()
{
	DrawLine(0, 0, pos.x, pos.y, GetColor(255, 0, 0), true);
	DrawCircle(VH.x, VH.y, 2, GetColor(0, 255, 0), true);
}