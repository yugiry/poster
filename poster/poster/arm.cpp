#pragma once
#include "arm.h"
#include "function.h"

CArm::CArm(Point p)
{
	pos = p;
	ImgWidth = 16;
	ImgHeight = 32;

	vec.y = ImgHeight;
}

int CArm::Action(vector<unique_ptr<BaseVector>>& base)
{
	return 0;
}

void CArm::Draw()
{
	FreeDrawBox(pos, vec, ImgWidth, ImgHeight);
}