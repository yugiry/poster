#pragma once
#include "hitobj.h"
#include "function.h"

CHitobj::CHitobj(Point p, Vector v, int w, int h, int atime, int _ID)
{
	pos = p;
	vec = v;

	ImgWidth = w;
	ImgHeight = h;

	alive_time = atime;

	ID = _ID;
}

int CHitobj::Action(vector<unique_ptr<BaseVector>>& base)
{
	//�A�[���̓����蔻��
	if (ID == ARM)
	{
		for (auto i = base.begin(); i != base.end(); i++)
		{
			//�R����S�~
			if ((*i)->ID == BURNABLE)
			{
				if ((*i)->radius == -1)
				{
					if (HitCheck_box(this, (*i).get()))
					{
						(*i)->vec = vec;
						(*i)->vec.y -= g;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						(*i)->vec = vec;
						(*i)->vec.y -= g;
					}
				}
			}
			//�S����
			if ((*i)->ID == CRUMB)
			{
				if ((*i)->radius == -1)
				{
					if (HitCheck_box(this, (*i).get()))
					{
						(*i)->vec = vec;
						(*i)->vec.y -= g;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						(*i)->vec = vec;
						(*i)->vec.y -= g;
					}
				}
			}
			//�v���X�e�B�b�N
			if ((*i)->ID == PLASTIC)
			{
				if ((*i)->radius == -1)
				{
					if (HitCheck_box(this, (*i).get()))
					{
						(*i)->vec = vec;
						(*i)->vec.y -= g;
					}
				}
				else if ((*i)->radius > 0)
				{
					if (HitCheck_Box_CircleB((*i).get(), this, (*i)->radius))
					{
						(*i)->vec = vec;
						(*i)->vec.y -= g;
					}
				}
			}
		}
	}

	if (ID == GDELETE)
	{
		for (auto i = base.begin(); i != base.end(); i++)
		{
			if ((*i)->ID == BURNABLE || (*i)->ID == CRUMB || (*i)->ID == PLASTIC)
			{
				(*i)->FLAG = false;
			}
		}
	}

	if (alive_time == 0)
		FLAG = false;
	if (alive_time > 0)
		alive_time--;

	return 0;
}

void CHitobj::Draw()
{
	DrawBox(pos.x, pos.y, pos.x + ImgWidth, pos.y + ImgHeight, GetColor(255, 255, 0), true);
}