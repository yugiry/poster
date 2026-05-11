#pragma once
#include "line.h"
#include "function.h"

CLine::CLine()
{


	ID = L1;
}

int CLine::Action(vector<unique_ptr<BaseVector>>& base)
{


	return 0;
}

void CLine::Draw()
{
	DrawLine(WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2 + 50, WINDOW_HEIGHT / 2, 0x0000ff, true);
}