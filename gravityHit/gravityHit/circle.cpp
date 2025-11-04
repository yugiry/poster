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

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		pos.x = WINDOW_WIDTH / 2 + 5;
		pos.y = 50;

		vec = { 0,0 };
	}

	if (pos.y + vec.y > WINDOW_HEIGHT - radius)
	{
		vec.y = (WINDOW_HEIGHT - radius - pos.y - vec.y) * bound;
		vec.x = vec.x * bound;
	}
	if (pos.x + vec.x > WINDOW_WIDTH - radius)
	{
		vec.x = (WINDOW_WIDTH - radius - pos.x - vec.x) * bound;
	}
	if (pos.x + vec.x < radius)
	{
		vec.x = (radius - pos.x - vec.x) * bound;
	}

	for (int i = 0; i < base.size(); i++)
	{
		//â~Ç∆â~ÇÃìñÇΩÇËîªíË
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

		//â~Ç∆éläpå`ÇÃìñÇΩÇËîªíË
		if (base[i]->ID == B2)
		{
			Point P = pos;
			Point A = base[i]->pos;
			Point B{ base[i]->pos.x + base[i]->VW.x,base[i]->pos.y + base[i]->VW.y };
			Point C{ base[i]->pos.x + base[i]->VH.x,base[i]->pos.y + base[i]->VH.y };
			Point D{ B.x + base[i]->VH.x,B.y + base[i]->VH.y };
			//élï”ÇªÇÍÇºÇÍÇÃì_Ç©ÇÁàÍî‘ãﬂÇ¢ãóó£ÇãÅÇﬂÇÈ
			line[0] = Near_Point_Line(P, A, B);
			line[1] = Near_Point_Line(P, A, C);
			line[2] = Near_Point_Line(P, D, B);
			line[3] = Near_Point_Line(P, D, C);
			//élï”Ç∆ÇÃìñÇΩÇËîªíË
			for (int j = 0; j < 4; j++)
			{
				Vector v{ pos.x - line[j].x,pos.y - line[j].y };
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
	for (int i = 0; i < 4; i++)
		DrawLine(pos.x, pos.y, line[i].x, line[i].y, GetColor(255, 0, 0), true);
}