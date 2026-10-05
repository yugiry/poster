#pragma once
#include "triangle.h"

CTriangle::CTriangle()
{
	pos.x = WINDOW_WIDTH / 2;
	pos.y = WINDOW_HEIGHT / 2;

	radian = 0;
}

int CTriangle::Action(vector<unique_ptr<BaseVector>>& base)
{
	return 0;
}

void CTriangle::Draw()
{

}