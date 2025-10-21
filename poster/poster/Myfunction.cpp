#pragma once
#include "Myfunction.h"
#include "2D_function.h"

//�p�x��������������
//(���W�A���̌X���A�����A�c��)
void FreeDrawBox(Point p, Vector vh, int w, int h)
{
	Vector vw{ -vh.y,vh.x };
	vw = Vector_SetLength(vw, w / 2);

	DrawLine(p.x - vw.x, p.y - vw.y, p.x - vw.x, p.y - vw.y + vh.y, GetColor(0, 0, 255), true);
	DrawLine(p.x + vw.x, p.y + vw.y, p.x + vw.x, p.y + vw.y + vh.y, GetColor(0, 0, 255), true);
	DrawLine(p.x - vw.x, p.y - vw.y, p.x + vw.x, p.y - vw.y, GetColor(0, 0, 255), true);
	DrawLine(p.x - vw.x, p.y - vw.y + vh.y, p.x + vw.x, p.y + vw.y + vh.y, GetColor(0, 0, 255), true);
}
