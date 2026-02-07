#pragma once
#include "lines.h"

CLines::CLines()
{
	pos = { WINDOW_WIDTH - 50,WINDOW_HEIGHT - 50 };

	VW = { WINDOW_WIDTH,0 };

	ID = L2;
}

int CLines::Action(vector<unique_ptr<BaseVector>>& base)
{
	vec = { 0,0 };

	if (CheckHitKey(KEY_INPUT_I))vec.y = -4.0f;
	if (CheckHitKey(KEY_INPUT_K))vec.y = 4.0f;
	if (CheckHitKey(KEY_INPUT_J))vec.x = -4.0f;
	if (CheckHitKey(KEY_INPUT_L))vec.x = 4.0f;

	pos.x += vec.x;
	pos.y += vec.y;

	return 0;
}

void CLines::Draw()
{

	DrawLine(WINDOW_WIDTH, 0, pos.x, pos.y, GetColor(0, 255, 0), true);
}